
#include "buffer.h"
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID BUFFER12::BeginDraw ( )
{
	LPDIRECT3DDEVICE9 lpD3DDevice = pRender->lpD3DDevice;

	lpD3DDevice->GetRenderTarget( 0, &lpD3DBackup );

	lpD3DDevice->SetRenderTarget( 0, lpD3DBuffer );
	lpD3DDevice->SetDepthStencilSurface( NULL );

	lpD3DDevice->BeginScene();
}

VOID BUFFER12::EndDraw ( )
{
	LPDIRECT3DDEVICE9 lpD3DDevice = pRender->lpD3DDevice;

	lpD3DDevice->EndScene();

	lpD3DDevice->SetRenderTarget( 0, lpD3DBackup );
	lpD3DDevice->SetDepthStencilSurface( pRender->lpDepthBuffer );

	lpD3DBackup->Release();
}
