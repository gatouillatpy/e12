
#pragma once



#include "entity.h"

#include "util.h"



class DLL HITBOX12 : public ENTITY12
{

	friend class RENDER12;

private:

	D3DXVECTOR3 vMin ;
	D3DXVECTOR3 vMax ;

	D3DXMATRIX	matHitbox ;

	BOOLEAN bMatrix ;

	FLOAT fColor[4] ;

	VOID Check ( D3DXVECTOR3 & _vTmp, D3DXMATRIX & _matWorld ) ;
	VOID Check ( D3DXVECTOR3 & _vTmp ) ;

public:
	
	HITBOX12 ( RENDER12* _pRender, ENTITY12* _pOwner ) ;

	_inline FLOAT* Color ( ) { return fColor; } ;

	_inline D3DXVECTOR3 GetMin ( ) { return vMin; } ;
	VOID SetMin ( D3DXVECTOR3 & _vMin ) ;
	VOID SetMin ( FLOAT _x, FLOAT _y, FLOAT _z ) ;
	_inline D3DXVECTOR3 GetMax ( ) { return vMax; } ;
	VOID SetMax ( D3DXVECTOR3 & _vMax ) ;
	VOID SetMax ( FLOAT _x, FLOAT _y, FLOAT _z ) ;

	BOOLEAN Intersect ( D3DXVECTOR3 & _vRayPos, D3DXVECTOR3 & _vRayDir ) ;

	VOID Reset ( ) ;
	VOID Merge ( HITBOX12* _pHitbox, D3DXMATRIX & _matWorld ) ;
	VOID Merge ( HITBOX12* _pHitbox ) ;
	VOID Setup ( D3DXVECTOR3 & _vMin, D3DXVECTOR3 & _vMax, D3DXMATRIX & _matWorld ) ;
	VOID Setup ( D3DXVECTOR3 & _vMin, D3DXVECTOR3 & _vMax ) ;

	VOID UpdateMatrix ( ) ;
	D3DXMATRIX Matrix ( ) ;

	virtual VOID ProcessCommand ( LPSTR sCommand ) ;
	virtual VOID ProcessHelp ( ) ;

};