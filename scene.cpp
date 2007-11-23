
#include "scene.h"
#include "render.h"
#include "indexer.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



SCENE12::SCENE12 ( RENDER12* _pRender ) : ENTITY12( _pRender->iScene, _pRender->pEngine )
{
	iChild = new INDEXER12(pLog);
	iObject = new INDEXER12(pLog);

	pParent = NULL;

	pRender = _pRender;

	pHitbox = new HITBOX12( pRender, this );

	vCenter = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	vAngle = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	vSize = D3DXVECTOR3( 1.0f, 1.0f, 1.0f );

	D3DXMatrixIdentity( &matCenter );
	D3DXMatrixIdentity( &matAngle );
	D3DXMatrixIdentity( &matSize );
	D3DXMatrixIdentity( &matScene );

	bHitbox = FALSE;
	bMatrix = FALSE;

	bVisible = TRUE;
}

SCENE12::~SCENE12 ( )
{
	delete iChild;
	delete iObject;
}



VOID SCENE12::AddChild ( SCENE12* _pChild )
{
	_pChild->SetParent( this );

	iChild->Add( _pChild );

	bHitbox = FALSE;
}

VOID SCENE12::DelChild ( SCENE12* _pChild )
{
	_pChild->SetParent( NULL );

	iChild->Del( _pChild );

	bHitbox = FALSE;
}



VOID SCENE12::AddObject ( OBJECT12* _pObject )
{
	_pObject->SetScene( this );

	iObject->Add( _pObject );

	bHitbox = FALSE;
}

VOID SCENE12::DelObject ( OBJECT12* _pObject )
{
	_pObject->SetScene( NULL );

	iObject->Del( _pObject );

	bHitbox = FALSE;
}



VOID SCENE12::SetCenter ( FLOAT _x, FLOAT _y, FLOAT _z )
{
	vCenter = D3DXVECTOR3(_x, _y, _z);
	
	bMatrix = FALSE;
	bHitbox = FALSE;
}

VOID SCENE12::SetCenter ( D3DXVECTOR3 & _vCenter )
{
	vCenter = _vCenter;
	
	bMatrix = FALSE;
	bHitbox = FALSE;
}



VOID SCENE12::SetAngle ( FLOAT _x, FLOAT _y, FLOAT _z )
{
	vAngle = D3DXVECTOR3(_x, _y, _z);
	
	bMatrix = FALSE;
	bHitbox = FALSE;
}

VOID SCENE12::SetAngle ( D3DXVECTOR3 & _vAngle )
{
	vAngle = _vAngle;
	
	bMatrix = FALSE;
	bHitbox = FALSE;
}



VOID SCENE12::SetSize ( FLOAT _x, FLOAT _y, FLOAT _z )
{
	vSize = D3DXVECTOR3(_x, _y, _z);

	bMatrix = FALSE;
	bHitbox = FALSE;
}

VOID SCENE12::SetSize ( D3DXVECTOR3 & _vSize )
{
	vSize = _vSize;

	bMatrix = FALSE;
	bHitbox = FALSE;
}



VOID SCENE12::Move ( FLOAT _x, FLOAT _y, FLOAT _z )
{
	vCenter.x += _x;
	vCenter.y += _y;
	vCenter.z += _z;

	bMatrix = FALSE;
	bHitbox = FALSE;
}

VOID SCENE12::Rotate ( FLOAT _x, FLOAT _y, FLOAT _z )
{
	vAngle.x += _x;
	vAngle.y += _y;
	vAngle.z += _z;

	bMatrix = FALSE;
	bHitbox = FALSE;
}

VOID SCENE12::Grow ( FLOAT _x, FLOAT _y, FLOAT _z )
{
	vSize.x *= _x;
	vSize.y *= _y;
	vSize.z *= _z;

	bMatrix = FALSE;
	bHitbox = FALSE;
}

VOID SCENE12::Shrink ( FLOAT _x, FLOAT _y, FLOAT _z )
{
	if ( _x != 0.0f ) vSize.x /= _x;
	if ( _y != 0.0f ) vSize.y /= _y;
	if ( _z != 0.0f ) vSize.z /= _z;

	bMatrix = FALSE;
	bHitbox = FALSE;
}



BOOLEAN	SCENE12::Intersect ( D3DXVECTOR3 & _vRayPos, D3DXVECTOR3 & _vRayDir )
{
	return pHitbox->Intersect( _vRayPos, _vRayDir );
}



VOID SCENE12::UpdateHitbox ( )
{
	pHitbox->Reset();

	ENTITY12 **ppEntity, **ppEnd;

	iObject->Vector( ppEntity, ppEnd );
	while ( ppEntity < ppEnd )
	{
		OBJECT12* pObject = (OBJECT12*)*ppEntity;
		pHitbox->Merge( pObject->Hitbox(), Matrix() );
		ppEntity++;
	}

	iChild->Vector( ppEntity, ppEnd );
	while ( ppEntity < ppEnd )
	{
		SCENE12* pChild = (SCENE12*)*ppEntity;
		pHitbox->Merge( pChild->Hitbox() );
		ppEntity++;
	}

	bHitbox = TRUE;
}



VOID SCENE12::UpdateMatrix ( )
{
	D3DXMatrixTranslation( &matCenter, vCenter.x, vCenter.y, vCenter.z );
	D3DXMatrixRotationYawPitchRoll( &matAngle, vAngle.y, vAngle.x, vAngle.z );
	D3DXMatrixScaling( &matSize, vSize.x, vSize.y, vSize.z );
	matScene = matSize * matAngle * matCenter;
	if ( pParent ) matScene *= pParent->Matrix();

	bMatrix = TRUE;
}



HITBOX12* SCENE12::Hitbox ( )
{
	if ( !bHitbox ) UpdateHitbox();

	return pHitbox;
}



D3DXMATRIX SCENE12::Matrix ( )
{
	if ( !bMatrix ) UpdateMatrix();

	return matScene;
}



VOID SCENE12::Update ( )
{
	if ( bVisible == FALSE ) return;

	if ( bHitbox == FALSE ) UpdateHitbox();
	if ( bMatrix == FALSE ) UpdateMatrix();

	ENTITY12 **ppEntity, **ppEnd;

	iObject->Vector( ppEntity, ppEnd );
	while ( ppEntity < ppEnd )
	{
		OBJECT12* pObject = (OBJECT12*)*ppEntity;
		pObject->Update();
		ppEntity++;
	}

	iChild->Vector( ppEntity, ppEnd );
	while ( ppEntity < ppEnd )
	{
		SCENE12* pChild = (SCENE12*)*ppEntity;
		pChild->Update();
		ppEntity++;
	}
}



VOID SCENE12::Render ( CAMERA12* _pCamera )
{
	if ( bVisible == FALSE ) return;

	ENTITY12 **ppEntity, **ppEnd;

	iObject->Vector( ppEntity, ppEnd );
	while ( ppEntity < ppEnd )
	{
		OBJECT12* pObject = (OBJECT12*)*ppEntity;
		pObject->Render( _pCamera );
		ppEntity++;
	}

	iChild->Vector( ppEntity, ppEnd );
	while ( ppEntity < ppEnd )
	{
		SCENE12* pChild = (SCENE12*)*ppEntity;
		pChild->Render( _pCamera );
		ppEntity++;
	}
}

VOID SCENE12::Render ( CAMERA12* _pCamera, DWORD _dwPass )
{
	if ( bVisible == FALSE ) return;

	ENTITY12 **ppEntity, **ppEnd;

	iObject->Vector( ppEntity, ppEnd );
	while ( ppEntity < ppEnd )
	{
		OBJECT12* pObject = (OBJECT12*)*ppEntity;
		if ( pObject->dwPass == _dwPass )
			pObject->Render( _pCamera, dwPass );
		ppEntity++;
	}

	iChild->Vector( ppEntity, ppEnd );
	while ( ppEntity < ppEnd )
	{
		SCENE12* pChild = (SCENE12*)*ppEntity;
		if ( pChild->dwPass == _dwPass )
			pChild->Render( _pCamera, dwPass );
		ppEntity++;
	}
}



VOID SCENE12::Draft ( CAMERA12* _pCamera, DWORD _dwPass )
{
	LPDIRECT3DQUERY9 lpQuery = pRender->lpDraftQuery;

	lpQuery->Issue( D3DISSUE_BEGIN );
	pRender->DrawHitbox( pHitbox, _pCamera );
	lpQuery->Issue( D3DISSUE_END );

	DWORD dwPixelCount = 0;
	while ( lpQuery->GetData( (LPVOID)&dwPixelCount, sizeof(DWORD), D3DGETDATA_FLUSH ) == S_FALSE );
	if( dwPixelCount > 0 )
	{
		dwPass = _dwPass;

		ENTITY12 **ppEntity, **ppEnd;

		iObject->Vector( ppEntity, ppEnd );
		while ( ppEntity < ppEnd )
		{
			OBJECT12* pObject = (OBJECT12*)*ppEntity;
			pObject->Draft( _pCamera, dwPass );
			ppEntity++;
		}

		iChild->Vector( ppEntity, ppEnd );
		while ( ppEntity < ppEnd )
		{
			SCENE12* pChild = (SCENE12*)*ppEntity;
			pChild->Draft( _pCamera, dwPass );
			ppEntity++;
		}
	}
}



INDEXER12* SCENE12::ObjectIndexer ( )
{
	return iObject;
}

INDEXER12* SCENE12::ChildIndexer ( )
{
	return iChild;
}
