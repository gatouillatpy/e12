
#include "buffer.h"
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



BYTE* BUFFER12::Lock ( )
{
	if ( lpD3DSurface )	Unlock();

	pRender->lpD3DDevice->CreateOffscreenPlainSurface( nWidth, nHeight, D3DFMT_A8R8G8B8, D3DPOOL_SYSTEMMEM,
		&lpD3DSurface, NULL );

	pRender->lpD3DDevice->GetRenderTargetData( lpD3DBuffer, lpD3DSurface );

	D3DLOCKED_RECT tLockedRect;
	lpD3DSurface->LockRect( &tLockedRect, NULL, 0 );

	return (BYTE*)tLockedRect.pBits;
}

BYTE* BUFFER12::Lock ( SHORT _nLeft, SHORT _nTop, SHORT _nWidth, SHORT _nHeight )
{
	if ( lpD3DSurface )	Unlock();

	pRender->lpD3DDevice->CreateOffscreenPlainSurface( nWidth, nHeight, D3DFMT_A8R8G8B8, D3DPOOL_SYSTEMMEM,
		&lpD3DSurface, NULL );

	pRender->lpD3DDevice->GetRenderTargetData( lpD3DBuffer, lpD3DSurface );

	RECT tRect;
	tRect.left = _nLeft;
	tRect.top = _nTop;
	tRect.right = _nLeft + _nWidth;
	tRect.bottom = _nTop + _nHeight;

	D3DLOCKED_RECT tLockedRect;
	lpD3DSurface->LockRect( &tLockedRect, &tRect, 0 );

	return (BYTE*)tLockedRect.pBits;
}

BYTE* BUFFER12::Lock ( FLOAT _fLeft, FLOAT _fTop, FLOAT _fWidth, FLOAT _fHeight )
{
	SHORT _nLeft = (SHORT)(_fLeft * (FLOAT)nWidth);
	SHORT _nTop = (SHORT)(_fTop * (FLOAT)nHeight);
	SHORT _nWidth = (SHORT)(_fWidth * (FLOAT)nWidth);
	SHORT _nHeight = (SHORT)(_fHeight * (FLOAT)nHeight);

	return Lock( _nLeft, _nTop, _nWidth, _nHeight );
}

VOID BUFFER12::Unlock ( )
{
	if ( lpD3DSurface )
	{
		lpD3DSurface->UnlockRect();

		pRender->lpD3DDevice->UpdateSurface( lpD3DSurface, NULL, lpD3DBuffer, NULL );

		lpD3DSurface->Release();
		lpD3DSurface = NULL;
	}
}
