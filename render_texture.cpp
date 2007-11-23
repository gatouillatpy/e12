
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID RENDER12::DrawTexture ( D3DXVECTOR2 & _vPA, D3DXVECTOR2 & _vPB, D3DXVECTOR2 & _vTA, D3DXVECTOR2 & _vTB, D3DXVECTOR2 & _vMin, D3DXVECTOR2 & _vMax, TEXTURE12* _pTexture, D3DXVECTOR4 & _vMaskColor, D3DXVECTOR4 & _vTestColor )
{
	lpD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CW );
	lpD3DDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );

	struct VERTEX2 { FLOAT x, y, z; FLOAT u, v; };

	VERTEX2 pVertex[4] = { _vPA.x, _vPA.y, 0.0f, _vTA.x, _vTA.y,
						   _vPB.x, _vPA.y, 0.0f, _vTB.x, _vTA.y,
						   _vPA.x, _vPB.y, 0.0f, _vTA.x, _vTB.y,
						   _vPB.x, _vPB.y, 0.0f, _vTB.x, _vTB.y };

	WORD pIndex[6] = { 2, 1, 0, 1, 2, 3 };

	lpD3DDevice->SetTexture( 0, _pTexture->lpD3DTexture );

	pCharShader->SetPSVector( "vMaskColor", &_vMaskColor );
	pCharShader->SetPSVector( "vTestColor", &_vTestColor );

	pCharShader->SetPSVector( "vMin", &_vMin );
	pCharShader->SetPSVector( "vMax", &_vMax );

	lpD3DDevice->SetVertexShader( pTextureShader->lpVertexShader );
	lpD3DDevice->SetPixelShader( pTextureShader->lpPixelShader );

	lpD3DDevice->SetFVF( D3DFVF_XYZ | D3DFVF_TEX1 );

	lpD3DDevice->DrawIndexedPrimitiveUP( D3DPT_TRIANGLELIST, 0, 4, 2, pIndex, D3DFMT_INDEX16, pVertex, sizeof(VERTEX2) );
}
