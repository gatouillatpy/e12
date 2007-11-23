
#include "window.h"
#include "engine.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



DWORD WINAPI WindowThread( LPVOID lpParam )
{
	WINDOW12* pWindow = (WINDOW12*)lpParam;

	WNDCLASSEX wc;
	ZeroMemory( &wc, sizeof(WNDCLASSEX) );

	wc.cbSize			= sizeof(WNDCLASSEX); 
    wc.style			= CS_CLASSDC;
    wc.lpfnWndProc		= WindowProc;
    wc.cbClsExtra		= 0L;
    wc.cbWndExtra		= 0L;
    wc.hInstance		= GetModuleHandle( NULL );
    wc.hIcon			= NULL;
	BYTE nAndMask = 0; BYTE nXorMask = 255;
    wc.hCursor			= CreateCursor( GetModuleHandle( NULL ), 0, 0, 1, 1, &nAndMask, &nXorMask );
    wc.hbrBackground	= NULL;
    wc.lpszMenuName		= NULL;
    wc.lpszClassName	= pWindow->sName;
    wc.hIconSm			= NULL;
    RegisterClassEx( &wc );

	pWindow->hWnd = CreateWindow
	(
		pWindow->sName,
		pWindow->sTitle,
        WS_OVERLAPPEDWINDOW,
		pWindow->nLeft,
		pWindow->nTop,
		pWindow->nWidth,
		pWindow->nHeight,
        NULL,
		NULL,
		wc.hInstance,
		NULL
	);

	SetWindowLong( pWindow->hWnd, GWL_USERDATA, (LONG)pWindow );

    ShowWindow( pWindow->hWnd, SW_SHOWDEFAULT );
    UpdateWindow( pWindow->hWnd );

	MSG msg = {0}; 
    while( pWindow->bEnabled == TRUE )
    {
		GetMessage( &msg, pWindow->hWnd, 0, 0 );

		TranslateMessage( &msg );
		DispatchMessage( &msg );
	}

	UnregisterClass( pWindow->sName, wc.hInstance );

	*pWindow->pThread = NULL;

	return 0;
}
