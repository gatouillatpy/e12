
#pragma once



#include "util.h"

#include "entity.h"



class DLL FONT12 : public ENTITY12
{

	friend class RENDER12;
	friend class LABEL12;
	friend class BUTTON12;
	friend class BUFFER12;
	friend class TEXTBOX12;
	friend class ALABEL12;

private:

	RENDER12* pRender ;

	LPDIRECT3DTEXTURE9 lpTexture ;
	LPDIRECT3DSURFACE9 lpBuffer ;
	LPDIRECT3DSURFACE9 lpSurface ;

	RECT rChar[256];

	D3DXVECTOR2 pOffset[256];
	D3DXVECTOR2 pScale[256];

	FLOAT fU, fV;

	UINT lWidth ;
	UINT lHeight ;

	SHORT nSmooth ;
	LPSTR sFont ;
	BOOLEAN bBold ;
	BOOLEAN bItalic ;
	BOOLEAN bUnderline ;

public:

	FONT12 ( RENDER12* _pRender ) ;
	virtual ~FONT12 ( ) ;

	VOID SetSmooth ( SHORT _nSmooth ) { nSmooth = _nSmooth; } ;
	SHORT GetSmooth ( ) { return nSmooth; } ;
	VOID SetFont ( LPSTR _sFont ) { StringCopy( sFont, 256, _sFont ); } ;
	LPSTR GetFont ( ) { return sFont; } ;
	VOID SetBold ( BOOLEAN _bBold ) { bBold = _bBold; } ;
	BOOLEAN GetBold ( ) { return bBold; } ;
	VOID SetItalic ( BOOLEAN _bItalic ) { bItalic = _bItalic; } ;
	BOOLEAN GetItalic ( ) { return bItalic; } ;
	VOID SetUnderline ( BOOLEAN _bUnderline ) { bUnderline = _bUnderline; } ;
	BOOLEAN GetUnderline ( ) { return bUnderline; } ;

	BOOLEAN Generate ( UINT _nSize ) ;

	BOOLEAN Load ( LPSTR _sFile ) ;

	virtual VOID ProcessCommand ( LPSTR sCommand ) ;
	virtual VOID ProcessHelp ( ) ;

};