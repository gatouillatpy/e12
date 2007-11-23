
#include "textbox.h"
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID TEXTBOX12::SetText ( LPSTR _sText )
{
	if ( _sText )
		StringCopy( sText, 2048, _sText );
	else
		ZeroMemory( sText, 2048 );

	OnChange();

	LABEL12::SetCaption( _sText );
}

LPSTR TEXTBOX12::GetText ( )
{
	return pCaption;
}



VOID TEXTBOX12::SetCaption ( LPSTR _sCaption )
{
	if ( _sCaption )
		StringCopy( sText, 2048, _sCaption );
	else
		ZeroMemory( sText, 2048 );

	OnChange();

	LABEL12::SetCaption( _sCaption );
}

LPSTR TEXTBOX12::GetCaption ( )
{
	return pCaption;
}



D3DXVECTOR4 TEXTBOX12::GetCursorColor ( )
{
	return vCursorColor;
}

VOID TEXTBOX12::SetCursorColor ( D3DXVECTOR4 & _vColor )
{
	vCursorColor = _vColor;
}

VOID TEXTBOX12::SetCursorColor ( DWORD _dwColor )
{
	FLOAT _a = (FLOAT)((_dwColor & 0xFF000000) >> 24) / 255.0f;
	FLOAT _r = (FLOAT)((_dwColor & 0x00FF0000) >> 16) / 255.0f;
	FLOAT _g = (FLOAT)((_dwColor & 0x0000FF00) >> 8) / 255.0f;
	FLOAT _b = (FLOAT)(_dwColor & 0x000000FF) / 255.0f;

	vCursorColor.x = _r;
	vCursorColor.y = _g;
	vCursorColor.z = _b;
	vCursorColor.w = _a;
}

VOID TEXTBOX12::SetCursorColor ( FLOAT _r, FLOAT _g, FLOAT _b, FLOAT _a )
{
	vCursorColor.x = _r;
	vCursorColor.y = _g;
	vCursorColor.z = _b;
	vCursorColor.w = _a;
}



VOID TEXTBOX12::SetCursorBlendState ( BLENDSTATE12* _pCursorBlendState )
{
	pCursorBlendState = _pCursorBlendState;
}

BLENDSTATE12* TEXTBOX12::GetCursorBlendState ( )
{
	return pCursorBlendState;
}
