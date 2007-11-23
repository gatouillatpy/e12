
#pragma once



#include "util.h"

#include "entity.h"



class DLL TEXTURE12 : public ENTITY12
{

	friend class RENDER12;
	friend class ANIMATION12;
	friend class IMAGE12;
	friend class CURSOR12;
	friend class OBJECT12;
	friend class SPRITE12;
	friend class SHADER12;
	friend class BUFFER12;

protected:

	RENDER12* pRender ;

	LPDIRECT3DBASETEXTURE9 lpD3DTexture ;

	D3DXMATRIX matTexture ;

	BOOLEAN bMatrix ; // vrai si la matrice est à jour, faux sinon

	D3DXVECTOR2 vCenter ;
	D3DXVECTOR2 vOffset ;
	FLOAT fAngle ;
	D3DXVECTOR2 vZoom ;

	UINT nWidth ;
	UINT nHeight ;

public:

	TEXTURE12 ( RENDER12* _pRender ) ;
	virtual ~TEXTURE12 ( ) ;

	virtual TEXTURE12* Copy ( BOOLEAN bCopyPixelData = FALSE ) ;

	virtual BOOLEAN Import ( LPSTR _sFile ) ;

	virtual BOOLEAN Load ( LPSTR _sFile ) ;

	VOID Move ( FLOAT _u, FLOAT _v ) ;
	VOID Rotate ( FLOAT _alpha ) ;
	VOID Grow ( FLOAT _du, FLOAT _dv ) ;
	VOID Shrink ( FLOAT _du, FLOAT _dv ) ;

	VOID SetCenter ( FLOAT _u, FLOAT _v ) ;
	VOID SetCenter ( D3DXVECTOR2 & _vCenter ) ;
	_inline D3DXVECTOR2 GetCenter ( ) ;

	VOID SetOffset ( FLOAT _u, FLOAT _v ) ;
	VOID SetOffset ( D3DXVECTOR2 & _vOffset ) ;
	_inline D3DXVECTOR2 GetOffset ( ) ;

	VOID SetAngle ( FLOAT _alpha ) ;
	_inline FLOAT GetAngle ( ) ;

	VOID SetZoom ( FLOAT _du, FLOAT _dv ) ;
	VOID SetZoom ( D3DXVECTOR2 & _vZoom ) ;
	_inline D3DXVECTOR2 GetZoom ( ) ;

	_inline FLOAT du ( ) ;
	_inline FLOAT dv ( ) ;

	_inline FLOAT alpha ( ) ;

	_inline FLOAT u ( ) ;
	_inline FLOAT v ( ) ;

	_inline FLOAT cu ( ) ;
	_inline FLOAT cv ( ) ;

	VOID UpdateMatrix ( ) ;
	D3DXMATRIX Matrix ( ) ;

	virtual VOID ProcessCommand ( LPSTR sCommand ) ;
	virtual VOID ProcessHelp ( ) ;

};