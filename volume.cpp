
#include "volume.h"
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOLUME12::VOLUME12 ( RENDER12* _pRender ) : TEXTURE12( _pRender )
{
}



VOLUME12* VOLUME12::Copy( BOOLEAN bCopyPixelData )
{
	/* creation de la texture */
	VOLUME12* pTexture = new VOLUME12( pRender );

	if ( bCopyPixelData )
	{
		/* copie de la texture direct3d */
		if ( lpD3DTexture )
		{
			LPDIRECT3DVOLUMETEXTURE9 tSource = (LPDIRECT3DVOLUMETEXTURE9)lpD3DTexture;

			DWORD dwLevelCount = tSource->GetLevelCount();

			D3DVOLUME_DESC d3dvdInfo;
			tSource->GetLevelDesc( 0, &d3dvdInfo );

			DWORD dwSize = d3dvdInfo.Width * d3dvdInfo.Height * d3dvdInfo.Depth;

			D3DXCreateVolumeTexture( pRender->lpD3DDevice, d3dvdInfo.Width, d3dvdInfo.Height, d3dvdInfo.Depth, dwLevelCount, d3dvdInfo.Usage, d3dvdInfo.Format, d3dvdInfo.Pool, (LPDIRECT3DVOLUMETEXTURE9*)&pTexture->lpD3DTexture );
			LPDIRECT3DVOLUMETEXTURE9 tDestination = (LPDIRECT3DVOLUMETEXTURE9)pTexture->lpD3DTexture;

			for ( DWORD k = 0 ; k < dwLevelCount ; k++ )
			{
				D3DLOCKED_BOX* pBoxSrc = NULL;
				tSource->LockBox( k, pBoxSrc, NULL, 0 );

				DWORD* pDataSrc = (DWORD*)pBoxSrc->pBits;

				D3DLOCKED_BOX* pBoxDst = NULL;
				tDestination->LockBox( k, pBoxDst, NULL, 0 );

				DWORD* pDataDst = (DWORD*)pBoxDst->pBits;

				for ( DWORD n = 0 ; n < dwSize ; n++ )
					pDataDst[n] = pDataSrc[n];

				tDestination->UnlockBox(k);
				tSource->UnlockBox(k);
			}
		}
	}
	else
	{
		pTexture->lpD3DTexture = lpD3DTexture;
	}

	return pTexture;
}



BOOLEAN VOLUME12::Import ( LPSTR _sFile )
{
	// à faire

	return 1;
}

BOOLEAN VOLUME12::Import ( DWORD _dwLevelCount, ... )
{
	// à faire

	return 1;
}

BOOLEAN VOLUME12::ImportLevel ( DWORD _dwLevel, LPSTR _sFile )
{
	// à faire

	return 1;
}



BOOLEAN VOLUME12::Load ( LPSTR _sFile )
{
	if ( _sFile == NULL )
	{
		pLog->Push( __FILE__, __LINE__, CODE_ERROR, CODE_VOLUME12, 0x0001, this, NULL, NULL ); return 0;
	}
	else if ( CheckFile( _sFile ) == 0 ) 
	{
		pLog->Push( __FILE__, __LINE__, CODE_ERROR, CODE_VOLUME12, 0x0002, this, NULL, _sFile ); return 0;
	}

	// à faire

	return 1;
}
