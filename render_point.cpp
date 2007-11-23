
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID RENDER12::DrawPoint ( D3DXVECTOR2 & _vPoint, D3DXVECTOR4 & _vColor )
{
	VERTEX tVertex = { (_vPoint.x * 2.0f) - 1.0f, 1.0f - (_vPoint.y * 2.0f), 0.0f };

	pColorShader->SetPSVector( "vColor", &_vColor );

	lpD3DDevice->SetVertexShader( pColorShader->lpVertexShader );
	lpD3DDevice->SetPixelShader( pColorShader->lpPixelShader );

	lpD3DDevice->SetFVF( D3DFVF_XYZ );

	lpD3DDevice->DrawPrimitiveUP( D3DPT_POINTLIST, 1, &tVertex, sizeof(VERTEX) );
}

VOID RENDER12::DrawPoint ( D3DXVECTOR2 & _vPoint, FLOAT _r, FLOAT _g, FLOAT _b, FLOAT _a )
{
	DrawPoint( _vPoint, D3DXVECTOR4( _r, _g, _b, _a ) );
}

VOID RENDER12::DrawPoint ( D3DXVECTOR2 & _vPoint, DWORD _dwColor )
{
	FLOAT _a = (FLOAT)((_dwColor & 0xFF000000) >> 24) / 255.0f;
	FLOAT _r = (FLOAT)((_dwColor & 0x00FF0000) >> 16) / 255.0f;
	FLOAT _g = (FLOAT)((_dwColor & 0x0000FF00) >> 8) / 255.0f;
	FLOAT _b = (FLOAT)(_dwColor & 0x000000FF) / 255.0f;

	DrawPoint( _vPoint, D3DXVECTOR4( _r, _g, _b, _a ) );
}



VOID RENDER12::DrawPoint ( FLOAT _x, FLOAT _y, D3DXVECTOR4 & _vColor )
{
	DrawPoint( D3DXVECTOR2( _x, _y ), _vColor );
}

VOID RENDER12::DrawPoint ( FLOAT _x, FLOAT _y, FLOAT _r, FLOAT _g, FLOAT _b, FLOAT _a )
{
	DrawPoint( D3DXVECTOR2( _x, _y ), D3DXVECTOR4( _r, _g, _b, _a ) );
}

VOID RENDER12::DrawPoint ( FLOAT _x, FLOAT _y, DWORD _dwColor )
{
	FLOAT _a = (FLOAT)((_dwColor & 0xFF000000) >> 24) / 255.0f;
	FLOAT _r = (FLOAT)((_dwColor & 0x00FF0000) >> 16) / 255.0f;
	FLOAT _g = (FLOAT)((_dwColor & 0x0000FF00) >> 8) / 255.0f;
	FLOAT _b = (FLOAT)(_dwColor & 0x000000FF) / 255.0f;

	DrawPoint( D3DXVECTOR2( _x, _y ), D3DXVECTOR4( _r, _g, _b, _a ) );
}



VOID RENDER12::DrawPoint ( SHORT _nx, SHORT _ny, D3DXVECTOR4 & _vColor )
{
	FLOAT _x = (FLOAT)_nx / (FLOAT)nWidth;
	FLOAT _y = (FLOAT)_ny / (FLOAT)nHeight;

	DrawPoint( D3DXVECTOR2( _x, _y ), _vColor );
}

VOID RENDER12::DrawPoint ( SHORT _nx, SHORT _ny, FLOAT _r, FLOAT _g, FLOAT _b, FLOAT _a )
{
	FLOAT _x = (FLOAT)_nx / (FLOAT)nWidth;
	FLOAT _y = (FLOAT)_ny / (FLOAT)nHeight;

	DrawPoint( D3DXVECTOR2( _x, _y ), D3DXVECTOR4( _r, _g, _b, _a ) );
}

VOID RENDER12::DrawPoint ( SHORT _nx, SHORT _ny, DWORD _dwColor )
{
	FLOAT _x = (FLOAT)_nx / (FLOAT)nWidth;
	FLOAT _y = (FLOAT)_ny / (FLOAT)nHeight;

	FLOAT _a = (FLOAT)((_dwColor & 0xFF000000) >> 24) / 255.0f;
	FLOAT _r = (FLOAT)((_dwColor & 0x00FF0000) >> 16) / 255.0f;
	FLOAT _g = (FLOAT)((_dwColor & 0x0000FF00) >> 8) / 255.0f;
	FLOAT _b = (FLOAT)(_dwColor & 0x000000FF) / 255.0f;

	DrawPoint( D3DXVECTOR2( _x, _y ), D3DXVECTOR4( _r, _g, _b, _a ) );
}
