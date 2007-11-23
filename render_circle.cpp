
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID RENDER12::DrawCircle ( D3DXVECTOR2 & _vPC, FLOAT _fRadius, D3DXVECTOR4 & _vColor )
{
	SHORT nCount = (SHORT)(0.125f * D3DX_PI * _fRadius * (FLOAT)nWidth) + 1;

	VERTEX* pVertex = new VERTEX[nCount];

	FLOAT t = 2.0f * D3DX_PI / (FLOAT)(nCount - 1);
	FLOAT k = 0.0f;

	FLOAT f = (FLOAT)nWidth / (FLOAT)nHeight;

	FLOAT cx = (_vPC.x * 2.0f) - 1.0f;
	FLOAT cy = 1.0f - (_vPC.y * 2.0f);
	FLOAT r = 2.0f * _fRadius;

	for ( SHORT n = 0 ; n < nCount ; n++ )
	{
		pVertex[n].x = cx + r * cos(k);
		pVertex[n].y = cy + r * sin(k) * f;
		pVertex[n].z = 0.0f;

		k += t;
	}

	pColorShader->SetPSVector( "vColor", &_vColor );

	lpD3DDevice->SetVertexShader( pColorShader->lpVertexShader );
	lpD3DDevice->SetPixelShader( pColorShader->lpPixelShader );

	lpD3DDevice->SetFVF( D3DFVF_XYZ );

	lpD3DDevice->DrawPrimitiveUP( D3DPT_LINESTRIP, nCount - 1, pVertex, sizeof(VERTEX) );

	delete [] pVertex;
}

VOID RENDER12::DrawCircle ( D3DXVECTOR2 & _vPC, FLOAT _fRadius, FLOAT _r, FLOAT _g, FLOAT _b, FLOAT _a )
{
	DrawCircle( _vPC, _fRadius, D3DXVECTOR4( _r, _g, _b, _a ) );
}

VOID RENDER12::DrawCircle ( D3DXVECTOR2 & _vPC, FLOAT _fRadius, DWORD _dwColor )
{
	FLOAT _a = (FLOAT)((_dwColor & 0xFF000000) >> 24) / 255.0f;
	FLOAT _r = (FLOAT)((_dwColor & 0x00FF0000) >> 16) / 255.0f;
	FLOAT _g = (FLOAT)((_dwColor & 0x0000FF00) >> 8) / 255.0f;
	FLOAT _b = (FLOAT)(_dwColor & 0x000000FF) / 255.0f;

	DrawCircle( _vPC, _fRadius, D3DXVECTOR4( _r, _g, _b, _a ) );
}



VOID RENDER12::DrawCircle ( FLOAT _xC, FLOAT _yC, FLOAT _fRadius, D3DXVECTOR4 & _vColor )
{
	DrawCircle( D3DXVECTOR2( _xC, _yC ), _fRadius, _vColor );
}

VOID RENDER12::DrawCircle ( FLOAT _xC, FLOAT _yC, FLOAT _fRadius, FLOAT _r, FLOAT _g, FLOAT _b, FLOAT _a )
{
	DrawCircle( D3DXVECTOR2( _xC, _yC ), _fRadius, D3DXVECTOR4( _r, _g, _b, _a ) );
}

VOID RENDER12::DrawCircle ( FLOAT _xC, FLOAT _yC, FLOAT _fRadius, DWORD _dwColor )
{
	FLOAT _a = (FLOAT)((_dwColor & 0xFF000000) >> 24) / 255.0f;
	FLOAT _r = (FLOAT)((_dwColor & 0x00FF0000) >> 16) / 255.0f;
	FLOAT _g = (FLOAT)((_dwColor & 0x0000FF00) >> 8) / 255.0f;
	FLOAT _b = (FLOAT)(_dwColor & 0x000000FF) / 255.0f;

	DrawCircle( D3DXVECTOR2( _xC, _yC ), _fRadius, D3DXVECTOR4( _r, _g, _b, _a ) );
}



VOID RENDER12::DrawCircle ( SHORT _nxC, SHORT _nyC, SHORT _nRadius, D3DXVECTOR4 & _vColor )
{
	FLOAT _xC = (FLOAT)_nxC / (FLOAT)nWidth;
	FLOAT _yC = (FLOAT)_nyC / (FLOAT)nHeight;
	
	FLOAT _fRadius = (FLOAT)_nRadius / (FLOAT)nWidth;

	DrawCircle( D3DXVECTOR2( _xC, _yC ), _fRadius, _vColor );
}

VOID RENDER12::DrawCircle ( SHORT _nxC, SHORT _nyC, SHORT _nRadius, FLOAT _r, FLOAT _g, FLOAT _b, FLOAT _a )
{
	FLOAT _xC = (FLOAT)_nxC / (FLOAT)nWidth;
	FLOAT _yC = (FLOAT)_nyC / (FLOAT)nHeight;

	FLOAT _fRadius = (FLOAT)_nRadius / (FLOAT)nWidth;

	DrawCircle( D3DXVECTOR2( _xC, _yC ), _fRadius, D3DXVECTOR4( _r, _g, _b, _a ) );
}

VOID RENDER12::DrawCircle ( SHORT _nxC, SHORT _nyC, SHORT _nRadius, DWORD _dwColor )
{
	FLOAT _xC = (FLOAT)_nxC / (FLOAT)nWidth;
	FLOAT _yC = (FLOAT)_nyC / (FLOAT)nHeight;

	FLOAT _fRadius = (FLOAT)_nRadius / (FLOAT)nWidth;

	FLOAT _a = (FLOAT)((_dwColor & 0xFF000000) >> 24) / 255.0f;
	FLOAT _r = (FLOAT)((_dwColor & 0x00FF0000) >> 16) / 255.0f;
	FLOAT _g = (FLOAT)((_dwColor & 0x0000FF00) >> 8) / 255.0f;
	FLOAT _b = (FLOAT)(_dwColor & 0x000000FF) / 255.0f;

	DrawCircle( D3DXVECTOR2( _xC, _yC ), _fRadius, D3DXVECTOR4( _r, _g, _b, _a ) );
}
