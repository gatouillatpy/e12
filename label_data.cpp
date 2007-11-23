
#include "label.h"
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID LABEL12::SetCaption ( LPSTR _sCaption )
{
	EnterCriticalSection( &cs );

	pCaption = _sCaption;

	if ( sCaption )
		delete [] sCaption;

	sCaption = NULL;

	if ( _sCaption != NULL )
	{
		DWORD dwLength = StringLength( _sCaption ) + 1;

		sCaption = new CHAR[dwLength];

		StringCopy( sCaption, dwLength, _sCaption );

		if ( bAutoWrap ) AutoWrap();
		if ( bAutoSize ) AutoSize();
		if ( bAutoOffset ) AutoOffset();
	}

	LeaveCriticalSection( &cs );
}

LPSTR LABEL12::GetCaption ( )
{
	return pCaption;
}



D3DXVECTOR4 LABEL12::GetFontColor ( )
{
	return vFontColor;
}

VOID LABEL12::SetFontColor ( D3DXVECTOR4 & _vColor )
{
	vFontColor = _vColor;
}

VOID LABEL12::SetFontColor ( DWORD _dwColor )
{
	FLOAT _a = (FLOAT)((_dwColor & 0xFF000000) >> 24) / 255.0f;
	FLOAT _r = (FLOAT)((_dwColor & 0x00FF0000) >> 16) / 255.0f;
	FLOAT _g = (FLOAT)((_dwColor & 0x0000FF00) >> 8) / 255.0f;
	FLOAT _b = (FLOAT)(_dwColor & 0x000000FF) / 255.0f;

	vFontColor.x = _r;
	vFontColor.y = _g;
	vFontColor.z = _b;
	vFontColor.w = _a;
}

VOID LABEL12::SetFontColor ( FLOAT _r, FLOAT _g, FLOAT _b, FLOAT _a )
{
	vFontColor.x = _r;
	vFontColor.y = _g;
	vFontColor.z = _b;
	vFontColor.w = _a;
}



FLOAT LABEL12::GetFontSize ( )
{
	return fFontSize;
}

VOID LABEL12::SetFontSize ( FLOAT _fFontSize )
{
	fFontSize = _fFontSize;
}



VOID LABEL12::SetFont ( FONT12* _pFont )
{
	pFont = _pFont;
}

FONT12* LABEL12::GetFont ( )
{
	return pFont;
}



VOID LABEL12::SetFontBlendState ( BLENDSTATE12* _pFontBlendState )
{
	pFontBlendState = _pFontBlendState;
}

BLENDSTATE12* LABEL12::GetFontBlendState ( )
{
	return pFontBlendState;
}



VOID LABEL12::SetAutoSize ( BOOLEAN _bAutoSize )
{
	bAutoSize = _bAutoSize;

	if ( _bAutoSize ) AutoSize();
}

BOOLEAN LABEL12::GetAutoSize ( )
{
	return bAutoSize;
}

VOID LABEL12::SetAutoWrap ( BOOLEAN _bAutoWrap )
{
	bAutoWrap = _bAutoWrap;

	fMaxWidth = fWidth;
	fMaxHeight = fHeight;

	if ( _bAutoWrap ) AutoWrap();
}

BOOLEAN LABEL12::GetAutoWrap ( )
{
	return bAutoWrap;
}

VOID LABEL12::SetAutoOffset ( BOOLEAN _bAutoOffset )
{
	bAutoOffset = _bAutoOffset;

	if ( _bAutoOffset ) AutoOffset();
}

BOOLEAN LABEL12::GetAutoOffset ( )
{
	return bAutoOffset;
}



VOID LABEL12::SetStyle ( STYLE _tStyle )
{
	tStyle = _tStyle;

	if ( _tStyle == STYLE_WIN9X )
		tBorderStyle = BS_WIN9X_BACK;
}

FRAME12::STYLE LABEL12::GetStyle ( )
{
	return tStyle;
}



VOID LABEL12::SetWidth ( FLOAT _fWidth )
{
	fWidth = _fWidth;
	fMaxWidth = _fWidth;
}

FLOAT LABEL12::GetWidth ( )
{
	return fWidth;
}

VOID LABEL12::SetHeight ( FLOAT _fHeight )
{
	fHeight = _fHeight;
	fMaxHeight = _fHeight;
}

FLOAT LABEL12::GetHeight ( )
{
	return fHeight;
}



VOID LABEL12::SetLineSpacing ( FLOAT _fLineSpacing )
{
	fLineSpacing = _fLineSpacing;
}

FLOAT LABEL12::GetLineSpacing ( )
{
	return fLineSpacing;
}



VOID LABEL12::SetOffsetX ( FLOAT _fOffsetX )
{
	fOffsetX = _fOffsetX;
}

FLOAT LABEL12::GetOffsetX ( )
{
	return fOffsetX;
}

VOID LABEL12::SetOffsetY ( FLOAT _fOffsetY )
{
	fOffsetY = _fOffsetY;
}

FLOAT LABEL12::GetOffsetY ( )
{
	return fOffsetY;
}
