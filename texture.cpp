
#include "texture.h"
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



TEXTURE12::TEXTURE12 ( RENDER12* _pRender ) : ENTITY12( _pRender->iTexture, _pRender->pEngine )
{
	pRender = _pRender;

	lpD3DTexture = NULL;

	vCenter = D3DXVECTOR2( 0.0f, 0.0f );
	vOffset = D3DXVECTOR2( 0.0f, 0.0f );
	fAngle = 0.0f;
	vZoom = D3DXVECTOR2( 1.0f, 1.0f );

	D3DXMatrixIdentity( &matTexture );

	bMatrix = FALSE;

	nWidth = 0;
	nHeight = 0;
}



TEXTURE12::~TEXTURE12 ( )
{
	if ( lpD3DTexture )
		lpD3DTexture->Release();
}



TEXTURE12* TEXTURE12::Copy( BOOLEAN bCopyPixelData )
{
	/* creation de la texture */
	TEXTURE12* pTexture = new TEXTURE12( pRender );

	if ( bCopyPixelData )
	{
		/* copie de la texture direct3d */
		if ( lpD3DTexture )
		{
			LPDIRECT3DTEXTURE9 tSource = (LPDIRECT3DTEXTURE9)lpD3DTexture;

			DWORD dwLevelCount = tSource->GetLevelCount();

			D3DSURFACE_DESC d3dsdInfo;
			tSource->GetLevelDesc( 0, &d3dsdInfo );

			DWORD dwSize = d3dsdInfo.Width * d3dsdInfo.Height;

			D3DXCreateTexture( pRender->lpD3DDevice, d3dsdInfo.Width, d3dsdInfo.Height, dwLevelCount, d3dsdInfo.Usage, d3dsdInfo.Format, d3dsdInfo.Pool, (LPDIRECT3DTEXTURE9*)&pTexture->lpD3DTexture );
			LPDIRECT3DTEXTURE9 tDestination = (LPDIRECT3DTEXTURE9)pTexture->lpD3DTexture;

			for ( DWORD k = 1 ; k < dwLevelCount ; k++ )
			{
				D3DLOCKED_RECT* pRectSrc = NULL;
				tSource->LockRect( k, pRectSrc, NULL, 0 );

				DWORD* pDataSrc = (DWORD*)pRectSrc->pBits;

				D3DLOCKED_RECT* pRectDst = NULL;
				tDestination->LockRect( k, pRectDst, NULL, 0 );

				DWORD* pDataDst = (DWORD*)pRectDst->pBits;

				for ( DWORD n = 0 ; n < dwSize ; n++ )
					pDataDst[n] = pDataSrc[n];

				tDestination->UnlockRect(k);
				tSource->UnlockRect(k);
			}
		}
	}
	else
	{
		pTexture->lpD3DTexture = lpD3DTexture;
	}

	return pTexture;
}
