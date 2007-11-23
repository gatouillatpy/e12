
#include "font.h"
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



FONT12::FONT12 ( RENDER12* _pRender ) : ENTITY12( _pRender->iFont, _pRender->pEngine )
{
	pRender = _pRender;

	lpTexture = NULL;
	lpBuffer = NULL;
	lpSurface = NULL;

	nSmooth = 0;
	bBold = FALSE;
	bItalic = FALSE;
	bUnderline = FALSE;
	sFont = new CHAR[12];
	StringCopy( sFont, 12, "Courier New" );
}

FONT12::~FONT12 ( )
{
	if ( lpTexture )
		lpTexture->Release();

	if ( lpBuffer )
		lpBuffer->Release();

	if ( lpSurface )
		lpSurface->Release();

	delete [] sFont;
}



BOOLEAN FONT12::Load ( LPSTR _sFile )
{
	HRESULT hr;

	if ( _sFile == NULL )
	{
		pLog->Push( __FILE__, __LINE__, CODE_ERROR, CODE_FONT12, 0x0001, this, NULL, NULL ); return 0;
	}
	else if ( CheckFile( _sFile ) == 0 ) 
	{
		pLog->Push( __FILE__, __LINE__, CODE_ERROR, CODE_FONT12, 0x0002, this, NULL, _sFile ); return 0;
	}

	if ( FAILED ( hr = D3DXCreateTextureFromFile( pRender->lpD3DDevice, _sFile, (LPDIRECT3DTEXTURE9*)&lpTexture ) ) )
	{
		pLog->Push( __FILE__, __LINE__, CODE_ERROR, CODE_FONT12, 0x0003, this, (LPVOID)hr, NULL ); return 0;
	}

	return 1;
}



BOOLEAN FONT12::Generate ( UINT _nSize )
{
	lWidth = _nSize;
	lHeight = _nSize;

	if ( lpTexture )
		lpTexture->Release();

	if ( lpBuffer )
		lpBuffer->Release();

	if ( lpSurface )
		lpSurface->Release();

	pRender->lpD3DDevice->CreateTexture( lWidth, lHeight, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT,
		&lpTexture, NULL );

	lpTexture->GetSurfaceLevel( 0, &lpBuffer );

	pRender->lpD3DDevice->CreateOffscreenPlainSurface( lWidth, lHeight, D3DFMT_A8R8G8B8,
		D3DPOOL_SYSTEMMEM, &lpSurface, NULL );

	D3DLOCKED_RECT tLockedRect;
	lpSurface->LockRect( &tLockedRect, NULL, 0 );
	DWORD* pTexel = (DWORD*)tLockedRect.pBits;

	HDC hDC = CreateCompatibleDC( GetDC( pRender->lpWindow->hWnd ) );
	
	SHORT nFactor = 4096 / _nSize;
	SHORT nFontSize = -MulDiv( 144, GetDeviceCaps(hDC, LOGPIXELSY), 72 );
	DWORD nCharSize = _nSize / 16;

	HBITMAP hBitmap = CreateCompatibleBitmap( GetDC( pRender->lpWindow->hWnd ), 256, 256 );

	HFONT hFont = CreateFont( nFontSize, 0, 0, 0, bBold ? FW_BOLD : FW_DONTCARE, bItalic, bUnderline, FALSE,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, sFont );

	SelectObject( hDC, hFont );
	SetBkColor( hDC, 0x000000 );
	SetTextColor( hDC, 0xFFFFFF );

	BITMAPINFO bi;
	ZeroMemory( &bi, sizeof(BITMAPINFO) );
	bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biWidth = 256;
	bi.bmiHeader.biHeight = 256;
	bi.bmiHeader.biBitCount = 32;

	DWORD* pPixel = new DWORD[65536];

	for ( WORD n = 0 ; n < 256 ; n++ )
	{
		SelectObject( hDC, hBitmap );
		PatBlt( hDC, 0, 0, 256, 256, BLACKNESS );

		RECT rc = { 0, 0, 0, 0 };

		SelectObject( hDC, hFont );
		DrawText( hDC, (CHAR*)&n, 1, &rc, DT_CALCRECT | DT_LEFT | DT_TOP );
		rc.left = 128 - (rc.right - rc.left) / 2;
		rc.top = 128 - (rc.bottom - rc.top) / 2;
		rc.right += rc.left;
		rc.bottom += rc.top;
		DrawText( hDC, (CHAR*)&n, 1, &rc, DT_LEFT | DT_TOP );
		rc.left /= nFactor;
		rc.top /= nFactor;
		rc.right /= nFactor;
		rc.bottom /= nFactor;

		rChar[n] = rc;

		pOffset[n].x = (FLOAT)((n % 16) * nCharSize + rc.left) / (FLOAT)lWidth;
		pOffset[n].y = (FLOAT)((n / 16) * nCharSize + rc.top) / (FLOAT)lHeight;
		pScale[n].x = (FLOAT)(rc.right - rc.left) / (FLOAT)lWidth;
		pScale[n].y = (FLOAT)(rc.bottom - rc.top) / (FLOAT)lHeight;

		GetDIBits( hDC, hBitmap, 0, 256, pPixel, &bi, DIB_RGB_COLORS );

		// à faire faire par un pixel shader de blur
		/*if ( nSmooth > 0 )
		{
			DWORD* pTemp = new DWORD[65536];

			for ( WORD l = 0 ; l < nSmooth ; l++ )
			{
				for ( DWORD j = 0 ; j < 256 ; j++ )
				{
					for ( DWORD i = 0 ; i < 256 ; i++ )
					{
						DWORD k;
						WORD a, r, g, b;
						BYTE* pValue;

						k = j * 256 + i;
						pValue = (BYTE*)&pPixel[k];
						a = *pValue++ * 4; r = *pValue++ * 4; g = *pValue++ * 4; b = *pValue++ * 4;

						k = j * 256 + ((i-1) % 256);
						pValue = (BYTE*)&pPixel[k];
						a += *pValue++ * 2; r += *pValue++ * 2; g += *pValue++ * 2; b += *pValue++ * 2;

						k = j * 256 + ((i+1) % 256);
						pValue = (BYTE*)&pPixel[k];
						a += *pValue++ * 2; r += *pValue++ * 2; g += *pValue++ * 2; b += *pValue++ * 2;

						k = ((j-1) % 256) * 256 + i;
						pValue = (BYTE*)&pPixel[k];
						a += *pValue++ * 2; r += *pValue++ * 2; g += *pValue++ * 2; b += *pValue++ * 2;

						k = ((j+1) % 256) * 256 + i;
						pValue = (BYTE*)&pPixel[k];
						a += *pValue++ * 2; r += *pValue++ * 2; g += *pValue++ * 2; b += *pValue++ * 2;

						k = ((j-1) % 256) * 256 + ((i-1) % 256);
						pValue = (BYTE*)&pPixel[k];
						a += *pValue++ ; r += *pValue++; g += *pValue++; b += *pValue++;

						k = ((j-1) % 256) * 256 + ((i+1) % 256);
						pValue = (BYTE*)&pPixel[k];
						a += *pValue++ ; r += *pValue++; g += *pValue++; b += *pValue++;

						k = ((j+1) % 256) * 256 + ((i-1) % 256);
						pValue = (BYTE*)&pPixel[k];
						a += *pValue++ ; r += *pValue++; g += *pValue++; b += *pValue++;

						k = ((j+1) % 256) * 256 + ((i+1) % 256);
						pValue = (BYTE*)&pPixel[k];
						a += *pValue++ ; r += *pValue++; g += *pValue++; b += *pValue++;

						k = j * 256 + i;
						pValue = (BYTE*)&pTemp[k];
						*pValue++ = (BYTE)(a / 16);
						*pValue++ = (BYTE)(r / 16);
						*pValue++ = (BYTE)(g / 16);
						*pValue++ = (BYTE)(b / 16);
					}
				}

				CopyMemory( pPixel, pTemp, 65536 * sizeof(DWORD) );
			}

			delete [] pTemp;
		}*/

		for ( DWORD j = 0, q = (n / 16) * nCharSize ; j < nCharSize ; j++, q++ )
		{
			for ( DWORD i = 0, p = (n % 16) * nCharSize ; i < nCharSize ; i++, p++ )
			{
				WORD a = 0; WORD r = 0; WORD g = 0; WORD b = 0;
				for ( INT y = 0, v = j * nFactor ; y < nFactor ; y++, v++ )
				{
					for ( INT x = 0, u = i * nFactor ; x < nFactor ; x++, u++ )
					{
						BYTE* pValue = (BYTE*)&pPixel[(256-v-1)*256+u];
						a += *pValue++;
						r += *pValue++;
						g += *pValue++;
						b += *pValue++;
					}
				}
				WORD c = nFactor * nFactor;
				BYTE* pValue = (BYTE*)&pTexel[q*_nSize+p];
				*pValue++ = (BYTE)(a / c);
				*pValue++ = (BYTE)(r / c);
				*pValue++ = (BYTE)(g / c);
				*pValue++ = (BYTE)(b / c);
			}
		}
	}

	pOffset[10].x = 0.0f;
	pOffset[10].y = 0.0f;
	pScale[10].x = 0.0f;
	pScale[10].y = pScale[90].y;

	lpSurface->UnlockRect();
	pRender->lpD3DDevice->UpdateSurface( lpSurface, NULL, lpBuffer, NULL );

	DeleteObject( hFont );
	DeleteObject( hBitmap );
	DeleteDC( hDC );

	delete [] pPixel;

	return 1;
}
