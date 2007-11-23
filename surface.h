
#pragma once

#include "object.h"

#include "util.h"



CONST DWORD OBJECT_TYPE_SURFACE = 0x00010001 ;



VOID DLL UseSurface ( RENDER12* pRender ) ;



struct DLL NODE
{
	FLOAT x, y, z;
	FLOAT r, g, b, a;
	FLOAT u, v;
};



class DLL SURFACE12 : public OBJECT12
{

private:

	FLOAT fWidth ;
	FLOAT fHeight ;
	FLOAT fLength ;

	WORD wDX, wDY ;

	WORD wDU, wDV ;

	NODE* pNode ;

	BOOLEAN bSurface ;

	BOOLEAN bColor ;
	BOOLEAN bUVMap ;

	BOOLEAN bRaytrace ;

public:

	SURFACE12 ( RENDER12* _pRender ) ;
	virtual ~SURFACE12 ( ) ;

	virtual SURFACE12* Copy( BOOLEAN bCopyGeometry = FALSE, BOOLEAN bCopyTexture = FALSE ) ;

	VOID Create ( FLOAT _fWidth, FLOAT _fHeight, FLOAT _fLength, WORD _wDX, WORD _wDY ) ;

	VOID SetGridSize ( WORD _wDU, WORD _wDV ) ;
	VOID SetGridWidth ( WORD _wDU ) ;
	_inline DWORD GridWidth ( ) { return wDU; } ;
	VOID SetGridHeight ( WORD _wDV ) ;
	_inline DWORD GridHeight ( ) { return wDV; } ;

	VOID SetNodePoint ( WORD _p, WORD _q, FLOAT _x, FLOAT _y, FLOAT _z ) ;
	VOID SetNodeDepth ( WORD _p, WORD _q, FLOAT _z ) ;
	VOID SetNodeColor ( WORD _p, WORD _q, FLOAT _r, FLOAT _g, FLOAT _b, FLOAT _a ) ;
	VOID SetNodeUVMap ( WORD _p, WORD _q, FLOAT _u, FLOAT _v ) ;

	VOID UpdateSurface ( ) ;

	VOID Render ( CAMERA12* _pCamera ) ;
	VOID Raytrace ( CAMERA12* _pCamera ) ;

};