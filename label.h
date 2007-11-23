
#pragma once

#include "font.h"
#include "frame.h"

#include "util.h"



class DLL LABEL12 : public FRAME12
{

protected:

	CRITICAL_SECTION cs;

	LPSTR pCaption ;
	LPSTR sCaption ;

	D3DXVECTOR4 vFontColor ;

	FONT12* pFont ;

	FLOAT fFontSize ;

	BLENDSTATE12* pFontBlendState ;

	FLOAT fOffsetX ;
	FLOAT fOffsetY ;

	FLOAT fMaxWidth ;
	FLOAT fMaxHeight ;

	BOOLEAN bAutoSize ;
	BOOLEAN bAutoWrap ;
	BOOLEAN bAutoOffset ;

	FLOAT fLineSpacing ;

	virtual VOID RenderCaption ( ) ;

	VOID TextSize ( FLOAT & ax, FLOAT & ay, FLOAT & mx, FLOAT & my, FLOAT & fLineHeight, FONT12* pFont, FLOAT fFontSize, LPSTR sText ) ;
	VOID TextWrap ( FLOAT & ax, FLOAT & mx, CHAR* & pWordSpace, FLOAT & fWordSize, FLOAT & fGroupSize, FONT12* pFont, FLOAT fFontSize, LPSTR sText ) ;

	virtual VOID AutoSize ( ) ;
	virtual VOID AutoWrap ( ) ;
	virtual VOID AutoOffset ( ) ;

public:

	LABEL12 ( RENDER12* _pRender ) ;
	virtual ~LABEL12 ( ) ;

	D3DXVECTOR4 GetFontColor ( ) ;
	VOID SetFontColor ( D3DXVECTOR4 & _vColor ) ;
	VOID SetFontColor ( DWORD _dwColor ) ;
	VOID SetFontColor ( FLOAT _r, FLOAT _g, FLOAT _b, FLOAT _a ) ;

	FLOAT GetFontSize ( ) ;
	VOID SetFontSize ( FLOAT _fFontSize ) ;

	VOID SetFontBlendState ( BLENDSTATE12* _pFontBlendState ) ;
	BLENDSTATE12* GetFontBlendState ( ) ;

	VOID SetFont ( FONT12* _pFont ) ;
	FONT12* GetFont ( ) ;

	virtual VOID SetCaption ( LPSTR _sCaption ) ;
	virtual LPSTR GetCaption ( ) ;

	VOID SetAutoSize ( BOOLEAN _bAutoSize ) ;
	BOOLEAN GetAutoSize ( ) ;

	VOID SetAutoWrap ( BOOLEAN _bAutoWrap ) ;
	BOOLEAN GetAutoWrap ( ) ;

	VOID SetAutoOffset ( BOOLEAN _bAutoOffset ) ;
	BOOLEAN GetAutoOffset ( ) ;

	virtual VOID SetStyle ( STYLE _tStyle ) ;
	virtual STYLE GetStyle ( ) ;

	virtual VOID SetWidth ( FLOAT _fWidth ) ;
	virtual FLOAT GetWidth ( ) ;
	virtual VOID SetHeight ( FLOAT _fHeight ) ;
	virtual FLOAT GetHeight ( ) ;

	virtual VOID SetLineSpacing ( FLOAT _fLineSpacing ) ;
	virtual FLOAT GetLineSpacing ( ) ;

	virtual VOID SetOffsetX ( FLOAT _fOffsetX ) ;
	virtual FLOAT GetOffsetX ( ) ;
	virtual VOID SetOffsetY ( FLOAT _fOffsetY ) ;
	virtual FLOAT GetOffsetY ( ) ;

	virtual VOID Render ( ) ;

};