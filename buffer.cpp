
#include "buffer.h"
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



BUFFER12::BUFFER12 ( RENDER12* _pRender ) : TEXTURE12( _pRender )
{
	lpD3DBackup = NULL;

	lpD3DSurface = NULL;
	lpD3DBuffer = NULL;
}

BUFFER12::~BUFFER12 ( )
{
	if ( lpD3DSurface )
		lpD3DSurface->Release();

	if ( lpD3DBuffer )
		lpD3DBuffer->Release();
}



// ça peut planter, dans texture aussi je ne sais pas trop, je copie direct un locked rect
// de la texture sans passer par sa surface, à mon avis ça crash...
BUFFER12* BUFFER12::Copy( BOOLEAN bCopyPixelData )
{
	/* creation de la texture */
	BUFFER12* pTexture = new BUFFER12( pRender );

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



BOOLEAN BUFFER12::Generate ( UINT _nWidth, UINT _nHeight )
{
	nWidth = _nWidth;
	nHeight = _nHeight;

	if ( lpD3DTexture )
		lpD3DTexture->Release();

	D3DXCreateTexture( pRender->lpD3DDevice, _nWidth, _nHeight, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT, (LPDIRECT3DTEXTURE9*)&lpD3DTexture );

	if ( lpD3DBuffer )
		lpD3DBuffer->Release();

	((LPDIRECT3DTEXTURE9)lpD3DTexture)->GetSurfaceLevel( 0, &lpD3DBuffer );

	return 1;
}
