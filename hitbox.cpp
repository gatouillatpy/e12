
#include "hitbox.h"
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



HITBOX12::HITBOX12 ( RENDER12* _pRender, ENTITY12* _pOwner ) : ENTITY12( _pRender->iHitbox, _pRender->pEngine )
{
	fColor[3] = (FLOAT)(((DWORD)_pOwner >> 24) & 0xff) / 255.0f;
	fColor[0] = (FLOAT)(((DWORD)_pOwner >> 16) & 0xff) / 255.0f;
	fColor[1] = (FLOAT)(((DWORD)_pOwner >> 8) & 0xff) / 255.0f;
	fColor[2] = (FLOAT)(((DWORD)_pOwner) & 0xff) / 255.0f;

	vMin = D3DXVECTOR3( +999999.999f, +999999.999f, +999999.999f );
	vMax = D3DXVECTOR3( -999999.999f, -999999.999f, -999999.999f );

	D3DXMatrixIdentity( &matHitbox );

	bMatrix = FALSE;
}



VOID HITBOX12::Check ( D3DXVECTOR3 & _vecTemp, D3DXMATRIX & _matWorld )
{
	D3DXVec3TransformCoord( &_vecTemp, &_vecTemp, &_matWorld );

	if ( _vecTemp.x < vMin.x ) vMin.x = _vecTemp.x;
	if ( _vecTemp.y < vMin.y ) vMin.y = _vecTemp.y;
	if ( _vecTemp.z < vMin.z ) vMin.z = _vecTemp.z;
	if ( _vecTemp.x > vMax.x ) vMax.x = _vecTemp.x;
	if ( _vecTemp.y > vMax.y ) vMax.y = _vecTemp.y;
	if ( _vecTemp.z > vMax.z ) vMax.z = _vecTemp.z;
}

VOID HITBOX12::Check ( D3DXVECTOR3 & _vecTemp )
{
	if ( _vecTemp.x < vMin.x ) vMin.x = _vecTemp.x;
	if ( _vecTemp.y < vMin.y ) vMin.y = _vecTemp.y;
	if ( _vecTemp.z < vMin.z ) vMin.z = _vecTemp.z;
	if ( _vecTemp.x > vMax.x ) vMax.x = _vecTemp.x;
	if ( _vecTemp.y > vMax.y ) vMax.y = _vecTemp.y;
	if ( _vecTemp.z > vMax.z ) vMax.z = _vecTemp.z;
}



BOOLEAN	HITBOX12::Intersect ( D3DXVECTOR3 & _vRayPos, D3DXVECTOR3 & _vRayDir )
{
	return D3DXBoxBoundProbe( &vMin, &vMax, &_vRayPos, &_vRayDir );
}



VOID HITBOX12::Reset ( )
{
	vMin = D3DXVECTOR3( +999999.999f, +999999.999f, +999999.999f );
	vMax = D3DXVECTOR3( -999999.999f, -999999.999f, -999999.999f );

	bMatrix = FALSE;
}

VOID HITBOX12::Merge ( HITBOX12* _pHitbox, D3DXMATRIX & _matWorld )
{
	Check( D3DXVECTOR3( _pHitbox->vMin.x, _pHitbox->vMin.y, _pHitbox->vMin.z ), _matWorld );
	Check( D3DXVECTOR3( _pHitbox->vMin.x, _pHitbox->vMin.y, _pHitbox->vMax.z ), _matWorld );
	Check( D3DXVECTOR3( _pHitbox->vMin.x, _pHitbox->vMax.y, _pHitbox->vMin.z ), _matWorld );
	Check( D3DXVECTOR3( _pHitbox->vMin.x, _pHitbox->vMax.y, _pHitbox->vMax.z ), _matWorld );
	Check( D3DXVECTOR3( _pHitbox->vMax.x, _pHitbox->vMin.y, _pHitbox->vMin.z ), _matWorld );
	Check( D3DXVECTOR3( _pHitbox->vMax.x, _pHitbox->vMin.y, _pHitbox->vMax.z ), _matWorld );
	Check( D3DXVECTOR3( _pHitbox->vMax.x, _pHitbox->vMax.y, _pHitbox->vMin.z ), _matWorld );
	Check( D3DXVECTOR3( _pHitbox->vMax.x, _pHitbox->vMax.y, _pHitbox->vMax.z ), _matWorld );

	bMatrix = FALSE;
}

VOID HITBOX12::Merge ( HITBOX12* _pHitbox )
{
	Check( _pHitbox->vMin );
	Check( _pHitbox->vMax );

	bMatrix = FALSE;
}

VOID HITBOX12::Setup ( D3DXVECTOR3 & _vMin, D3DXVECTOR3 & _vMax, D3DXMATRIX & _matWorld )
{
	Check( D3DXVECTOR3( _vMin.x, _vMin.y, _vMin.z ), _matWorld );
	Check( D3DXVECTOR3( _vMin.x, _vMin.y, _vMax.z ), _matWorld );
	Check( D3DXVECTOR3( _vMin.x, _vMax.y, _vMin.z ), _matWorld );
	Check( D3DXVECTOR3( _vMin.x, _vMax.y, _vMax.z ), _matWorld );
	Check( D3DXVECTOR3( _vMax.x, _vMin.y, _vMin.z ), _matWorld );
	Check( D3DXVECTOR3( _vMax.x, _vMin.y, _vMax.z ), _matWorld );
	Check( D3DXVECTOR3( _vMax.x, _vMax.y, _vMin.z ), _matWorld );
	Check( D3DXVECTOR3( _vMax.x, _vMax.y, _vMax.z ), _matWorld );

	bMatrix = FALSE;
}

VOID HITBOX12::Setup ( D3DXVECTOR3 & _vMin, D3DXVECTOR3 & _vMax )
{
	Check( _vMin );
	Check( _vMax );

	bMatrix = FALSE;
}



VOID HITBOX12::SetMin ( D3DXVECTOR3 & _vMin )
{
	vMin = _vMin;

	bMatrix = FALSE;
}

VOID HITBOX12::SetMin ( FLOAT _x, FLOAT _y, FLOAT _z )
{
	vMin = D3DXVECTOR3(_x, _y, _z);

	bMatrix = FALSE;
}

VOID HITBOX12::SetMax ( D3DXVECTOR3 & _vMax )
{
	vMax = _vMax;

	bMatrix = FALSE;
}

VOID HITBOX12::SetMax ( FLOAT _x, FLOAT _y, FLOAT _z )
{
	vMax = D3DXVECTOR3(_x, _y, _z);

	bMatrix = FALSE;
}



VOID HITBOX12::UpdateMatrix ( )
{
	D3DXVECTOR3 vecSize = vMax - vMin;
	if ( vecSize.x < 0.001f ) vecSize.x = 0.001f;
	if ( vecSize.y < 0.001f ) vecSize.y = 0.001f;
	if ( vecSize.z < 0.001f ) vecSize.z = 0.001f;
	D3DXMATRIX matSize;
	D3DXMatrixScaling( &matSize, vecSize.x, vecSize.y, vecSize.z );

	D3DXVECTOR3 vecCenter = (vMin + vMax) * 0.5f;
	D3DXMATRIX matCenter;
	D3DXMatrixTranslation( &matCenter, vecCenter.x, vecCenter.y, vecCenter.z );

	matHitbox = matSize * matCenter;

	bMatrix = TRUE;
}

D3DXMATRIX HITBOX12::Matrix ( )
{
	if ( !bMatrix ) UpdateMatrix();

	return matHitbox;
}
