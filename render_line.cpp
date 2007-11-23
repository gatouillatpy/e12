
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID RENDER12::DrawLineGrad ( D3DXVECTOR2 & _vPA, D3DXVECTOR4 & _vCA, D3DXVECTOR2 & _vPB, D3DXVECTOR4 & _vCB )
{
	LVERTEX pVertex[2] = { { (_vPA.x * 2.0f) - 1.0f, 1.0f - (_vPA.y * 2.0f), 0.0f, D3DCOLOR_COLORVALUE(_vCA.x, _vCA.y, _vCA.z, _vCA.w) },
						   { (_vPB.x * 2.0f) - 1.0f, 1.0f - (_vPB.y * 2.0f), 0.0f, D3DCOLOR_COLORVALUE(_vCB.x, _vCB.y, _vCB.z, _vCB.w) } };

	// ce ne sont pas les bons shaders !!
	//lpD3DDevice->SetVertexShader( pRender->pBufferShader->lpVertexShader );
	//lpD3DDevice->SetPixelShader( pRender->pBufferShader->lpPixelShader );

	lpD3DDevice->SetFVF( D3DFVF_XYZ );

	lpD3DDevice->DrawPrimitiveUP( D3DPT_LINELIST, 2, pVertex, sizeof(LVERTEX) );
}



VOID RENDER12::DrawLine ( D3DXVECTOR2 & _vPA, D3DXVECTOR2 & _vPB, D3DXVECTOR4 & _vColor )
{
	VERTEX pVertex[2] = { { (_vPA.x * 2.0f) - 1.0f, 1.0f - (_vPA.y * 2.0f), 0.0f },
						  { (_vPB.x * 2.0f) - 1.0f, 1.0f - (_vPB.y * 2.0f), 0.0f } };

	pColorShader->SetPSVector( "vColor", &_vColor );

	lpD3DDevice->SetVertexShader( pColorShader->lpVertexShader );
	lpD3DDevice->SetPixelShader( pColorShader->lpPixelShader );

	lpD3DDevice->SetFVF( D3DFVF_XYZ );

	lpD3DDevice->DrawPrimitiveUP( D3DPT_LINELIST, 1, pVertex, sizeof(VERTEX) );
}

VOID RENDER12::DrawLine ( D3DXVECTOR2 & _vPA, D3DXVECTOR2 & _vPB, FLOAT _r, FLOAT _g, FLOAT _b, FLOAT _a )
{
	DrawLine( _vPA, _vPB, D3DXVECTOR4( _r, _g, _b, _a ) );
}

VOID RENDER12::DrawLine ( D3DXVECTOR2 & _vPA, D3DXVECTOR2 & _vPB, DWORD _dwColor )
{
	FLOAT _a = (FLOAT)((_dwColor & 0xFF000000) >> 24) / 255.0f;
	FLOAT _r = (FLOAT)((_dwColor & 0x00FF0000) >> 16) / 255.0f;
	FLOAT _g = (FLOAT)((_dwColor & 0x0000FF00) >> 8) / 255.0f;
	FLOAT _b = (FLOAT)(_dwColor & 0x000000FF) / 255.0f;

	DrawLine( _vPA, _vPB, D3DXVECTOR4( _r, _g, _b, _a ) );
}



VOID RENDER12::DrawLine ( FLOAT _xA, FLOAT _yA, FLOAT _xB, FLOAT _yB, D3DXVECTOR4 & _vColor )
{
	DrawLine( D3DXVECTOR2( _xA, _yA ), D3DXVECTOR2( _xB, _yB ), _vColor );
}

VOID RENDER12::DrawLine ( FLOAT _xA, FLOAT _yA, FLOAT _xB, FLOAT _yB, FLOAT _r, FLOAT _g, FLOAT _b, FLOAT _a )
{
	DrawLine( D3DXVECTOR2( _xA, _yA ), D3DXVECTOR2( _xB, _yB ), D3DXVECTOR4( _r, _g, _b, _a ) );
}

VOID RENDER12::DrawLine ( FLOAT _xA, FLOAT _yA, FLOAT _xB, FLOAT _yB, DWORD _dwColor )
{
	FLOAT _a = (FLOAT)((_dwColor & 0xFF000000) >> 24) / 255.0f;
	FLOAT _r = (FLOAT)((_dwColor & 0x00FF0000) >> 16) / 255.0f;
	FLOAT _g = (FLOAT)((_dwColor & 0x0000FF00) >> 8) / 255.0f;
	FLOAT _b = (FLOAT)(_dwColor & 0x000000FF) / 255.0f;

	DrawLine( D3DXVECTOR2( _xA, _yA ), D3DXVECTOR2( _xB, _yB ), D3DXVECTOR4( _r, _g, _b, _a ) );
}



VOID RENDER12::DrawLine ( SHORT _nxA, SHORT _nyA, SHORT _nxB, SHORT _nyB, D3DXVECTOR4 & _vColor )
{
	FLOAT _xA = (FLOAT)_nxA / (FLOAT)nWidth;
	FLOAT _yA = (FLOAT)_nyA / (FLOAT)nHeight;
	FLOAT _xB = (FLOAT)_nxB / (FLOAT)nWidth;
	FLOAT _yB = (FLOAT)_nyB / (FLOAT)nHeight;

	DrawLine( D3DXVECTOR2( _xA, _yA ), D3DXVECTOR2( _xB, _yB ), _vColor );
}

VOID RENDER12::DrawLine ( SHORT _nxA, SHORT _nyA, SHORT _nxB, SHORT _nyB, FLOAT _r, FLOAT _g, FLOAT _b, FLOAT _a )
{
	FLOAT _xA = (FLOAT)_nxA / (FLOAT)nWidth;
	FLOAT _yA = (FLOAT)_nyA / (FLOAT)nHeight;
	FLOAT _xB = (FLOAT)_nxB / (FLOAT)nWidth;
	FLOAT _yB = (FLOAT)_nyB / (FLOAT)nHeight;

	DrawLine( D3DXVECTOR2( _xA, _yA ), D3DXVECTOR2( _xB, _yB ), D3DXVECTOR4( _r, _g, _b, _a ) );
}

VOID RENDER12::DrawLine ( SHORT _nxA, SHORT _nyA, SHORT _nxB, SHORT _nyB, DWORD _dwColor )
{
	FLOAT _xA = (FLOAT)_nxA / (FLOAT)nWidth;
	FLOAT _yA = (FLOAT)_nyA / (FLOAT)nHeight;
	FLOAT _xB = (FLOAT)_nxB / (FLOAT)nWidth;
	FLOAT _yB = (FLOAT)_nyB / (FLOAT)nHeight;

	FLOAT _a = (FLOAT)((_dwColor & 0xFF000000) >> 24) / 255.0f;
	FLOAT _r = (FLOAT)((_dwColor & 0x00FF0000) >> 16) / 255.0f;
	FLOAT _g = (FLOAT)((_dwColor & 0x0000FF00) >> 8) / 255.0f;
	FLOAT _b = (FLOAT)(_dwColor & 0x000000FF) / 255.0f;

	DrawLine( D3DXVECTOR2( _xA, _yA ), D3DXVECTOR2( _xB, _yB ), D3DXVECTOR4( _r, _g, _b, _a ) );
}
