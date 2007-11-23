
#pragma once

#include "object.h"

#include "util.h"



class DLL CAMERA12 : public ENTITY12
{

	friend class RENDER12;

private:

	FLOAT fFOV ;
	FLOAT fRatio ;

	FLOAT fAngle ;

	FLOAT fZoom ;

	FLOAT fZNearPlane ;
	FLOAT fZFarPlane ;

	SHORT nWidth ;
	SHORT nHeight ;

	D3DXVECTOR3 vDir ;

	D3DXVECTOR3 vCenter ;
	D3DXVECTOR3 vAngle ;

	OBJECT12* pAnchor ;
	OBJECT12* pTarget ;

	D3DXMATRIX matCamera ;
	D3DXMATRIX matView ;
	D3DXMATRIX matProj ;
	D3DXMATRIX matInvView ;
	D3DXMATRIX matInvProj ;

	HITBOX12* pHitbox ;

	BOOLEAN bMatrix ;

public:
	
	CAMERA12 ( RENDER12* _pRender ) ;

	VOID MoveForward ( FLOAT _k ) ;
	VOID MoveBackward ( FLOAT _k ) ;
	VOID MoveLeft ( FLOAT _k ) ;
	VOID MoveRight ( FLOAT _k ) ;

	VOID Move ( FLOAT _x, FLOAT _y, FLOAT _z ) ;
	VOID Rotate ( FLOAT _x, FLOAT _y, FLOAT _z ) ;

	VOID SetCenter ( FLOAT _x, FLOAT _y, FLOAT _z ) ;
	VOID SetCenter ( D3DXVECTOR3 _vCenter ) ;
	D3DXVECTOR3 GetCenter ( ) { return vCenter; } ;

	VOID SetAngle ( FLOAT _x, FLOAT _y, FLOAT _z ) ;
	VOID SetAngle ( D3DXVECTOR3 _vAngle ) ;
	D3DXVECTOR3 GetAngle ( ) { return vAngle; } ;

	FLOAT FOV ( ) { return fFOV; } ;
	VOID SetFOV ( FLOAT _fFOV ) { fFOV = _fFOV; fAngle = _fFOV / 3.0f; } ;

	SHORT Width ( ) { return nWidth; } ;
	VOID SetWidth ( SHORT _nWidth ) { nWidth = _nWidth; } ;
	SHORT Height ( ) { return nHeight; } ;
	VOID SetHeight ( SHORT _nHeight ) { nHeight = _nHeight; } ;

	FLOAT Ratio ( ) { return fRatio; } ;
	VOID SetRatio ( FLOAT _fRatio ) { fRatio = _fRatio; } ;
	VOID AutoRatio ( RENDER12* _pRender ) ;

	FLOAT ZNearPlane ( ) { return fZNearPlane; } ;
	VOID SetZNearPlane ( FLOAT _fZNearPlane ) { fZNearPlane = _fZNearPlane; } ;
	FLOAT ZFarPlane ( ) { return fZFarPlane; } ;
	VOID SetZFarPlane ( FLOAT _ZFarPlane ) { fZFarPlane = _ZFarPlane; } ;

	FLOAT pitch ( ) { return vAngle.x; } ;
	FLOAT yaw ( ) { return vAngle.y; } ;
	FLOAT roll ( ) { return vAngle.z;  } ;

	FLOAT x ( ) { return vCenter.x; } ;
	FLOAT y ( ) { return vCenter.y; } ;
	FLOAT z ( ) { return vCenter.z; } ;

	FLOAT dx ( ) { return vDir.x; } ;
	FLOAT dy ( ) { return vDir.y; } ;
	FLOAT dz ( ) { return vDir.z; } ;

	VOID SetHitbox ( FLOAT _fWidth, FLOAT _fHeight, FLOAT _fLength ) ;
	HITBOX12* Hitbox ( ) { return pHitbox; } ;

	VOID SetAnchor ( OBJECT12* _pAnchor ) ;
	OBJECT12* GetAnchor ( ) ;

	VOID SetTarget ( OBJECT12* _pTarget ) ;
	OBJECT12* GetTarget ( ) ;

	VOID UpdateMatrix ( ) ;
	D3DXMATRIX Matrix ( ) ;
	D3DXMATRIX ViewMatrix ( ) ;
	D3DXMATRIX ProjMatrix ( ) ;
	D3DXMATRIX InvViewMatrix ( ) ;
	D3DXMATRIX InvProjMatrix ( ) ;

	virtual VOID ProcessCommand ( LPSTR sCommand ) ;
	virtual VOID ProcessHelp ( ) ;

};