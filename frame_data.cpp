
#include "frame.h"
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



D3DXVECTOR4 FRAME12::GetBackColor ( )
{
	return vBackColor;
}

VOID FRAME12::SetBackColor ( D3DXVECTOR4 & _vColor )
{
	vBackColor = _vColor;
}

VOID FRAME12::SetBackColor ( DWORD _dwColor )
{
	FLOAT _a = (FLOAT)((_dwColor & 0xFF000000) >> 24) / 255.0f;
	FLOAT _r = (FLOAT)((_dwColor & 0x00FF0000) >> 16) / 255.0f;
	FLOAT _g = (FLOAT)((_dwColor & 0x0000FF00) >> 8) / 255.0f;
	FLOAT _b = (FLOAT)(_dwColor & 0x000000FF) / 255.0f;

	vBackColor.x = _r;
	vBackColor.y = _g;
	vBackColor.z = _b;
	vBackColor.w = _a;
}

VOID FRAME12::SetBackColor ( FLOAT _r, FLOAT _g, FLOAT _b, FLOAT _a )
{
	vBackColor.x = _r;
	vBackColor.y = _g;
	vBackColor.z = _b;
	vBackColor.w = _a;
}



D3DXVECTOR4 FRAME12::GetBorderColor ( )
{
	return vBorderColor;
}

VOID FRAME12::SetBorderColor ( D3DXVECTOR4 & _vColor )
{
	vBorderColor = _vColor;
}

VOID FRAME12::SetBorderColor ( DWORD _dwColor )
{
	FLOAT _a = (FLOAT)((_dwColor & 0xFF000000) >> 24) / 255.0f;
	FLOAT _r = (FLOAT)((_dwColor & 0x00FF0000) >> 16) / 255.0f;
	FLOAT _g = (FLOAT)((_dwColor & 0x0000FF00) >> 8) / 255.0f;
	FLOAT _b = (FLOAT)(_dwColor & 0x000000FF) / 255.0f;

	vBorderColor.x = _r;
	vBorderColor.y = _g;
	vBorderColor.z = _b;
	vBorderColor.w = _a;
}

VOID FRAME12::SetBorderColor ( FLOAT _r, FLOAT _g, FLOAT _b, FLOAT _a )
{
	vBorderColor.x = _r;
	vBorderColor.y = _g;
	vBorderColor.z = _b;
	vBorderColor.w = _a;
}



VOID FRAME12::ShowBorder ( )
{
	bBorder = TRUE;
}

VOID FRAME12::HideBorder ( )
{
	bBorder = FALSE;
}



VOID FRAME12::SetBackBlendState ( BLENDSTATE12* _pBackBlendState )
{
	pBackBlendState = _pBackBlendState;
}

BLENDSTATE12* FRAME12::GetBackBlendState ( )
{
	return pBackBlendState;
}



VOID FRAME12::SetBorderBlendState ( BLENDSTATE12* _pBorderBlendState )
{
	pBorderBlendState = _pBorderBlendState;
}

BLENDSTATE12* FRAME12::GetBorderBlendState ( )
{
	return pBorderBlendState;
}



VOID FRAME12::SetStyle ( STYLE _tStyle )
{
	tStyle = _tStyle;

	if ( _tStyle == STYLE_WIN9X )
		tBorderStyle = BS_WIN9X_BACK;
}

FRAME12::STYLE FRAME12::GetStyle ( )
{
	return tStyle;
}



VOID FRAME12::SetBorderStyle ( BORDERSTYLE _tBorderStyle )
{
	tBorderStyle = _tBorderStyle;
}

FRAME12::BORDERSTYLE FRAME12::GetBorderStyle ( )
{
	return tBorderStyle;
}
