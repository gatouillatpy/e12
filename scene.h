
#pragma once

#include "object.h"
#include "hitbox.h"

#include "util.h"



class DLL SCENE12 : public ENTITY12
{

	friend class RENDER12;
	friend class OBJECT12;

private:

	INDEXER12* iChild ;

	RENDER12* pRender ;

	SCENE12* pParent ;

	INDEXER12* iObject ;

	D3DXVECTOR3 vCenter ;
	D3DXVECTOR3 vAngle ;
	D3DXVECTOR3 vSize ;

	HITBOX12* pHitbox ;

	D3DXMATRIX matCenter ;
	D3DXMATRIX matAngle ;
	D3DXMATRIX matSize ;
	D3DXMATRIX matScene ;

	BOOLEAN bHitbox ;
	BOOLEAN bMatrix ;

	DWORD dwPass ;

	BOOLEAN bVisible ;

public:

	SCENE12 ( RENDER12* _pRender ) ;
	virtual ~SCENE12 ( ) ;

	_inline VOID Show ( ) { bVisible = TRUE; } ;
	_inline VOID Hide ( ) { bVisible = FALSE; } ;

	VOID AddChild ( SCENE12* _pChild ) ;
	VOID DelChild ( SCENE12* _pChild ) ;

	INDEXER12* ChildIndexer ( ) ;

	VOID SetParent ( SCENE12* _pParent ) { pParent = _pParent; } ;
	SCENE12* GetParent ( ) { return pParent; } ;

	VOID AddObject ( OBJECT12* _pObject ) ;
	VOID DelObject ( OBJECT12* _pObject ) ;

	INDEXER12* ObjectIndexer ( ) ;

	VOID Move ( FLOAT _x, FLOAT _y, FLOAT _z ) ;
	VOID Rotate ( FLOAT _x, FLOAT _y, FLOAT _z ) ;
	VOID Grow ( FLOAT _x, FLOAT _y, FLOAT _z ) ;
	VOID Shrink ( FLOAT _x, FLOAT _y, FLOAT _z ) ;

	VOID SetCenter ( FLOAT _x, FLOAT _y, FLOAT _z ) ;
	VOID SetCenter ( D3DXVECTOR3 & _vCenter ) ;
	_inline D3DXVECTOR3 GetCenter ( ) { return vCenter; } ;

	VOID SetAngle ( FLOAT _x, FLOAT _y, FLOAT _z ) ;
	VOID SetAngle ( D3DXVECTOR3 & _vAngle ) ;
	_inline D3DXVECTOR3 GetAngle ( ) { return vAngle; } ;

	VOID SetSize ( FLOAT _x, FLOAT _y, FLOAT _z ) ;
	VOID SetSize ( D3DXVECTOR3 & _vSize ) ;
	_inline D3DXVECTOR3 GetSize ( ) { return vSize; } ;

	_inline FLOAT width ( ) { return vSize.x; } ;
	_inline FLOAT height ( ) { return vSize.y; } ;
	_inline FLOAT length ( ) { return vSize.z; } ;

	_inline FLOAT pitch ( ) { return vAngle.x; } ;
	_inline FLOAT yaw ( ) { return vAngle.y; } ;
	_inline FLOAT roll ( ) { return vAngle.z;  } ;

	_inline FLOAT x ( ) { return vCenter.x; } ;
	_inline FLOAT y ( ) { return vCenter.y; } ;
	_inline FLOAT z ( ) { return vCenter.z; } ;

	virtual BOOLEAN	Intersect ( D3DXVECTOR3 & _vRayPos, D3DXVECTOR3 & _vRayDir ) ;

	VOID UpdateHitbox ( ) ;
	HITBOX12* Hitbox ( ) ;

	VOID UpdateMatrix ( ) ;
	D3DXMATRIX Matrix ( ) ;

	VOID Update ( ) ;
	VOID Render ( CAMERA12* _pCamera ) ;
	VOID Render ( CAMERA12* _pCamera, DWORD _dwPass ) ;
	VOID Draft ( CAMERA12* _pCamera, DWORD _dwPass ) ;

	VOID Reset ( ) { dwPass = RANDOM; } ;

	virtual VOID ProcessCommand ( LPSTR sCommand ) ;
	virtual VOID ProcessHelp ( ) ;

};