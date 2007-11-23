
#include "buffer.h"
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID BUFFER12::Fill ( DWORD _dwColor )
{
	pRender->lpD3DDevice->ColorFill( lpD3DBuffer, NULL, _dwColor );
}

VOID BUFFER12::Fill ( FLOAT _r, FLOAT _g, FLOAT _b, FLOAT _a )
{
	pRender->lpD3DDevice->ColorFill( lpD3DBuffer, NULL, D3DCOLOR_COLORVALUE(_r, _g, _b, _a) );
}

VOID BUFFER12::Fill ( SHORT _nLeft, SHORT _nTop, SHORT _nWidth, SHORT _nHeight, DWORD _dwColor )
{
	RECT tRect;
	tRect.left = _nLeft;
	tRect.top = _nTop;
	tRect.right = _nLeft + _nWidth;
	tRect.bottom = _nTop + _nHeight;

	pRender->lpD3DDevice->ColorFill( lpD3DBuffer, NULL, _dwColor );
}

VOID BUFFER12::Fill ( SHORT _nLeft, SHORT _nTop, SHORT _nWidth, SHORT _nHeight, FLOAT _r, FLOAT _g, FLOAT _b, FLOAT _a )
{
	RECT tRect;
	tRect.left = _nLeft;
	tRect.top = _nTop;
	tRect.right = _nLeft + _nWidth;
	tRect.bottom = _nTop + _nHeight;

	pRender->lpD3DDevice->ColorFill( lpD3DBuffer, NULL, D3DCOLOR_COLORVALUE(_r, _g, _b, _a) );
}

VOID BUFFER12::Fill ( FLOAT _fLeft, FLOAT _fTop, FLOAT _fWidth, FLOAT _fHeight, DWORD _dwColor )
{
	SHORT _nLeft = (SHORT)(_fLeft * (FLOAT)nWidth);
	SHORT _nTop = (SHORT)(_fTop * (FLOAT)nHeight);
	SHORT _nWidth = (SHORT)(_fWidth * (FLOAT)nWidth);
	SHORT _nHeight = (SHORT)(_fHeight * (FLOAT)nHeight);

	Fill( _nLeft, _nTop, _nWidth, _nHeight, _dwColor );
}

VOID BUFFER12::Fill ( FLOAT _fLeft, FLOAT _fTop, FLOAT _fWidth, FLOAT _fHeight, FLOAT _r, FLOAT _g, FLOAT _b, FLOAT _a )
{
	SHORT _nLeft = (SHORT)(_fLeft * (FLOAT)nWidth);
	SHORT _nTop = (SHORT)(_fTop * (FLOAT)nHeight);
	SHORT _nWidth = (SHORT)(_fWidth * (FLOAT)nWidth);
	SHORT _nHeight = (SHORT)(_fHeight * (FLOAT)nHeight);

	Fill( _nLeft, _nTop, _nWidth, _nHeight, _r, _g, _b, _a );
}
