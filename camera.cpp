
#include "render.h"
#include "camera.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



CAMERA12::CAMERA12 ( RENDER12* _pRender ) : ENTITY12( _pRender->iCamera, _pRender->pEngine )
{
	pAnchor	= NULL;
	pTarget	= NULL;

	fFOV	= D3DX_PI * 0.5f;
	fRatio	= 4.0f / 3.0f;

	fAngle	= fFOV / 3.0f;
	fZoom	= 1.0f;

	fZNearPlane = 1.000f;
	fZFarPlane = 1999.999f;

	vCenter.x = 0.0f;
	vCenter.y = 0.0f;
	vCenter.z = 0.0f;

	vAngle.x = D3DX_PI * 0.5f;
	vAngle.y = 0.0f;
	vAngle.z = 0.0f;

	vDir.x = 0.0f;
	vDir.y = 0.0f;
	vDir.z = 1.0f;

	nWidth = 640;
	nHeight = 480;

	pHitbox = new HITBOX12( _pRender, this );
	pHitbox->SetMin( -1.0f, -1.0f, -1.0f );
	pHitbox->SetMax( 1.0f, 1.0f, 1.0f );

	bMatrix = FALSE;
}



VOID CAMERA12::SetCenter ( FLOAT _x, FLOAT _y, FLOAT _z )
{
	vCenter = D3DXVECTOR3(_x, _y, _z);

	bMatrix = FALSE;
}

VOID CAMERA12::SetCenter ( D3DXVECTOR3 _vCenter )
{
	vCenter = _vCenter;

	bMatrix = FALSE;
}



VOID CAMERA12::SetAngle ( FLOAT _x, FLOAT _y, FLOAT _z )
{
	vAngle = D3DXVECTOR3(_x, _y, _z);

	bMatrix = FALSE;
}

VOID CAMERA12::SetAngle ( D3DXVECTOR3 _vAngle )
{
	vAngle = _vAngle;

	bMatrix = FALSE;
}



VOID CAMERA12::Move ( FLOAT _x, FLOAT _y, FLOAT _z )
{
	vCenter.x += _x;
	vCenter.y += _y;
	vCenter.z += _z;

	bMatrix = FALSE;
}



VOID CAMERA12::Rotate ( FLOAT _x, FLOAT _y, FLOAT _z )
{
	vAngle.x -= _x;
	vAngle.y -= _y;
	vAngle.z -= _z;

	if ( vAngle.x < 0.0f ) vAngle.x += D3DX_PI * 2.0f;
	if ( vAngle.x > D3DX_PI * 2.0f ) vAngle.x -= D3DX_PI * 2.0f;
	if ( vAngle.y < -D3DX_PI * 0.5f + 0.001f ) vAngle.y = -D3DX_PI * 0.5f + 0.001f;
	if ( vAngle.y > D3DX_PI * 0.5f - 0.001f ) vAngle.y = D3DX_PI * 0.5f - 0.001f;

	vDir.x = cosf(vAngle.x) * cosf(vAngle.y);
	vDir.y = sinf(vAngle.y);
	vDir.z = sinf(vAngle.x) * cosf(vAngle.y);

	bMatrix = FALSE;
}



VOID CAMERA12::MoveForward ( FLOAT _k )
{
	vCenter.x += _k * vDir.x;
	vCenter.y += _k * vDir.y;
	vCenter.z += _k * vDir.z;

	bMatrix = FALSE;
}



VOID CAMERA12::MoveBackward ( FLOAT _k )
{
	vCenter.x -= _k * vDir.x;
	vCenter.y -= _k * vDir.y;
	vCenter.z -= _k * vDir.z;

	bMatrix = FALSE;
}



VOID CAMERA12::MoveLeft ( FLOAT _k )
{
	vCenter.x -= _k * vDir.z;
	vCenter.z += _k * vDir.x;

	bMatrix = FALSE;
}



VOID CAMERA12::MoveRight ( FLOAT _k )
{
	vCenter.x += _k * vDir.z;
	vCenter.z -= _k * vDir.x;

	bMatrix = FALSE;
}



VOID CAMERA12::SetHitbox ( FLOAT _fWidth, FLOAT _fHeight, FLOAT _fLength )
{
	pHitbox->SetMin( -0.5f * _fWidth, -0.5f * _fHeight, -0.5f * _fLength );
	pHitbox->SetMax( +0.5f * _fWidth, +0.5f * _fHeight, +0.5f * _fLength );
}



VOID CAMERA12::UpdateMatrix ( )
{
	D3DXVECTOR3 vTarget = vCenter + 4999.999f * vDir;
	D3DXVECTOR3 vNormal = D3DXVECTOR3( vDir.x, 0.0f, vDir.y );

	D3DXMATRIX matUp;
	D3DXMatrixRotationAxis( &matUp, &vNormal, vAngle.z );
	
	D3DXVECTOR3 vLookUp = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
	D3DXVec3TransformCoord( &vLookUp, &vLookUp, &matUp );
	D3DXVECTOR3 vLookFrom = pAnchor ? vCenter + pAnchor->AbsoluteCenter() : vCenter;
	D3DXVECTOR3 vLookAt = pTarget ? pTarget->AbsoluteCenter() : vTarget;

	D3DXMatrixLookAtLH( &matView, &vLookFrom, &vLookAt, &vLookUp );

	D3DXMatrixInverse( &matInvView, NULL, &matView );

	D3DXMatrixPerspectiveFovLH( &matProj, fFOV, fRatio, fZNearPlane, fZFarPlane );

	D3DXMatrixInverse( &matInvProj, NULL, &matProj );

	matCamera = matView * matProj;

	bMatrix = TRUE;
}

D3DXMATRIX CAMERA12::Matrix ( )
{
	if ( !bMatrix ) UpdateMatrix();

	return matCamera;
}

D3DXMATRIX CAMERA12::ViewMatrix ( )
{
	if ( !bMatrix ) UpdateMatrix();

	return matView;
}

D3DXMATRIX CAMERA12::ProjMatrix ( )
{
	if ( !bMatrix ) UpdateMatrix();

	return matProj;
}

D3DXMATRIX CAMERA12::InvViewMatrix ( )
{
	if ( !bMatrix ) UpdateMatrix();

	return matInvView;
}

D3DXMATRIX CAMERA12::InvProjMatrix ( )
{
	if ( !bMatrix ) UpdateMatrix();

	return matInvProj;
}



VOID CAMERA12::AutoRatio ( RENDER12* _pRender )
{
	nWidth = _pRender->nWidth;
	nHeight = _pRender->nHeight;

	fRatio = (FLOAT)nWidth / (FLOAT)nHeight;
}



VOID CAMERA12::SetAnchor ( OBJECT12* _pAnchor )
{
	pAnchor = _pAnchor;
}

OBJECT12* CAMERA12::GetAnchor ( )
{
	return pAnchor;
}



VOID CAMERA12::SetTarget ( OBJECT12* _pTarget )
{
	pTarget = _pTarget;
}

OBJECT12* CAMERA12::GetTarget ( )
{
	return pTarget;
}
