
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID RENDER12::DrawChar ( D3DXVECTOR2 & _vOffset, D3DXVECTOR2 & _vScale, D3DXVECTOR2 & _vMin, D3DXVECTOR2 & _vMax, FONT12* _pFont, D3DXVECTOR4 & _vMaskColor, D3DXVECTOR4 & _vTestColor, UCHAR _c )
{
	lpD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CW );
	lpD3DDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );

	D3DXVECTOR2 tOffset = _pFont->pOffset[_c];
	D3DXVECTOR2 tScale = _pFont->pScale[_c];

	D3DXVECTOR2 _vBound;
	_vBound.x = _vOffset.x + _vScale.x * tScale.x;
	_vBound.y = _vOffset.y + _vScale.y * tScale.y;

	FLOAT ax, ay, bx, by, au, av, bu, bv;

	ax = _vOffset.x;
	bx = _vBound.x;
	au = tOffset.x;
	bu = tOffset.x + tScale.x;

	ay = _vOffset.y;
	by = _vBound.y;
	av = tOffset.y;
	bv = tOffset.y + tScale.y;

	struct VERTEX2 { FLOAT x, y, z; FLOAT u, v; };

	VERTEX2 pVertex[4] = { ax, ay, 0.0f, au, av,
						   bx, ay, 0.0f, bu, av,
						   ax, by, 0.0f, au, bv,
						   bx, by, 0.0f, bu, bv };

	WORD pIndex[6] = { 2, 1, 0, 1, 2, 3 };

	lpD3DDevice->SetTexture( 0, _pFont->lpTexture );

	pCharShader->SetPSVector( "vMaskColor", &_vMaskColor );
	pCharShader->SetPSVector( "vTestColor", &_vTestColor );

	pCharShader->SetPSVector( "vMin", &_vMin );
	pCharShader->SetPSVector( "vMax", &_vMax );

	lpD3DDevice->SetVertexShader( pCharShader->lpVertexShader );
	lpD3DDevice->SetPixelShader( pCharShader->lpPixelShader );

	lpD3DDevice->SetFVF( D3DFVF_XYZ | D3DFVF_TEX1 );

	lpD3DDevice->DrawIndexedPrimitiveUP( D3DPT_TRIANGLELIST, 0, 4, 2, pIndex, D3DFMT_INDEX16, pVertex, sizeof(VERTEX2) );

	_vOffset.x = _vBound.x;
}
