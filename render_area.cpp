
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID RENDER12::DrawArea ( D3DXVECTOR2 & _vPA, D3DXVECTOR2 & _vPB, D3DXVECTOR4 & _vColor )
{
	lpD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CW );
	lpD3DDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );

	VERTEX pVertex[4] = { (_vPA.x * 2.0f) - 1.0f, 1.0f - (_vPA.y * 2.0f), 0.0f,
						  (_vPB.x * 2.0f) - 1.0f, 1.0f - (_vPA.y * 2.0f), 0.0f,
						  (_vPA.x * 2.0f) - 1.0f, 1.0f - (_vPB.y * 2.0f), 0.0f,
						  (_vPB.x * 2.0f) - 1.0f, 1.0f - (_vPB.y * 2.0f), 0.0f };

	WORD pIndex[] = { 2, 1, 0, 1, 2, 3 };

	pColorShader->SetPSVector( "vColor", &_vColor );

	lpD3DDevice->SetVertexShader( pColorShader->lpVertexShader );
	lpD3DDevice->SetPixelShader( pColorShader->lpPixelShader );

	lpD3DDevice->SetFVF( D3DFVF_XYZ );

	lpD3DDevice->DrawIndexedPrimitiveUP( D3DPT_TRIANGLELIST, 0, 4, 2, pIndex, D3DFMT_INDEX16, pVertex, sizeof(VERTEX) );
}

VOID RENDER12::DrawArea ( D3DXVECTOR2 & _vPA, D3DXVECTOR2 & _vPB, FLOAT _r, FLOAT _g, FLOAT _b, FLOAT _a )
{
	DrawArea( _vPA, _vPB, D3DXVECTOR4( _r, _g, _b, _a ) );
}

VOID RENDER12::DrawArea ( D3DXVECTOR2 & _vPA, D3DXVECTOR2 & _vPB, DWORD _dwColor )
{
	FLOAT _a = (FLOAT)((_dwColor & 0xFF000000) >> 24) / 255.0f;
	FLOAT _r = (FLOAT)((_dwColor & 0x00FF0000) >> 16) / 255.0f;
	FLOAT _g = (FLOAT)((_dwColor & 0x0000FF00) >> 8) / 255.0f;
	FLOAT _b = (FLOAT)(_dwColor & 0x000000FF) / 255.0f;

	DrawArea( _vPA, _vPB, D3DXVECTOR4( _r, _g, _b, _a ) );
}



VOID RENDER12::DrawArea ( FLOAT _xA, FLOAT _yA, FLOAT _xB, FLOAT _yB, D3DXVECTOR4 & _vColor )
{
	DrawArea( D3DXVECTOR2( _xA, _yA ), D3DXVECTOR2( _xB, _yB ), _vColor );
}

VOID RENDER12::DrawArea ( FLOAT _xA, FLOAT _yA, FLOAT _xB, FLOAT _yB, FLOAT _r, FLOAT _g, FLOAT _b, FLOAT _a )
{
	DrawArea( D3DXVECTOR2( _xA, _yA ), D3DXVECTOR2( _xB, _yB ), D3DXVECTOR4( _r, _g, _b, _a ) );
}

VOID RENDER12::DrawArea ( FLOAT _xA, FLOAT _yA, FLOAT _xB, FLOAT _yB, DWORD _dwColor )
{
	FLOAT _a = (FLOAT)((_dwColor & 0xFF000000) >> 24) / 255.0f;
	FLOAT _r = (FLOAT)((_dwColor & 0x00FF0000) >> 16) / 255.0f;
	FLOAT _g = (FLOAT)((_dwColor & 0x0000FF00) >> 8) / 255.0f;
	FLOAT _b = (FLOAT)(_dwColor & 0x000000FF) / 255.0f;

	DrawArea( D3DXVECTOR2( _xA, _yA ), D3DXVECTOR2( _xB, _yB ), D3DXVECTOR4( _r, _g, _b, _a ) );
}



VOID RENDER12::DrawArea ( SHORT _nxA, SHORT _nyA, SHORT _nxB, SHORT _nyB, D3DXVECTOR4 & _vColor )
{
	FLOAT _xA = (FLOAT)_nxA / (FLOAT)nWidth;
	FLOAT _yA = (FLOAT)_nyA / (FLOAT)nHeight;
	FLOAT _xB = (FLOAT)_nxB / (FLOAT)nWidth;
	FLOAT _yB = (FLOAT)_nyB / (FLOAT)nHeight;

	DrawArea( D3DXVECTOR2( _xA, _yA ), D3DXVECTOR2( _xB, _yB ), _vColor );
}

VOID RENDER12::DrawArea ( SHORT _nxA, SHORT _nyA, SHORT _nxB, SHORT _nyB, FLOAT _r, FLOAT _g, FLOAT _b, FLOAT _a )
{
	FLOAT _xA = (FLOAT)_nxA / (FLOAT)nWidth;
	FLOAT _yA = (FLOAT)_nyA / (FLOAT)nHeight;
	FLOAT _xB = (FLOAT)_nxB / (FLOAT)nWidth;
	FLOAT _yB = (FLOAT)_nyB / (FLOAT)nHeight;

	DrawArea( D3DXVECTOR2( _xA, _yA ), D3DXVECTOR2( _xB, _yB ), D3DXVECTOR4( _r, _g, _b, _a ) );
}

VOID RENDER12::DrawArea ( SHORT _nxA, SHORT _nyA, SHORT _nxB, SHORT _nyB, DWORD _dwColor )
{
	FLOAT _xA = (FLOAT)_nxA / (FLOAT)nWidth;
	FLOAT _yA = (FLOAT)_nyA / (FLOAT)nHeight;
	FLOAT _xB = (FLOAT)_nxB / (FLOAT)nWidth;
	FLOAT _yB = (FLOAT)_nyB / (FLOAT)nHeight;

	FLOAT _a = (FLOAT)((_dwColor & 0xFF000000) >> 24) / 255.0f;
	FLOAT _r = (FLOAT)((_dwColor & 0x00FF0000) >> 16) / 255.0f;
	FLOAT _g = (FLOAT)((_dwColor & 0x0000FF00) >> 8) / 255.0f;
	FLOAT _b = (FLOAT)(_dwColor & 0x000000FF) / 255.0f;

	DrawArea( D3DXVECTOR2( _xA, _yA ), D3DXVECTOR2( _xB, _yB ), D3DXVECTOR4( _r, _g, _b, _a ) );
}
