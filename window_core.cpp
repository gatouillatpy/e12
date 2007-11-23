
#include "window.h"
#include "engine.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID WINDOW12::Create( )
{
	if ( sName == NULL )
	{
		// pLog.PUSH
		return;
	}

	bEnabled = TRUE;

	pThread = pEngine->RegisterThread( WindowThread, (LPVOID)this );

	HANDLE hEvent = CreateEvent( NULL, FALSE, FALSE, NULL );
	while ( !hWnd ) { WaitForSingleObject( hEvent, 40 ); }
	CloseHandle( hEvent );

	RECT tRect;
	GetClientRect( hWnd, &tRect );
	nClientWidth = (SHORT)(tRect.right - tRect.left);
	nClientHeight = (SHORT)(tRect.bottom - tRect.top);
}

VOID WINDOW12::Create( LPSTR _sName, LPSTR _sTitle, UINT _nLeft, UINT _nTop, UINT _nWidth, UINT _nHeight )
{
	if ( sName == NULL )
	{
		// pLog.PUSH
		return;
	}

	SetName( _sName );
	
	SetTitle( _sTitle );

	nLeft = _nLeft;
	nTop = _nTop;
	nWidth = _nWidth;
	nHeight	= _nHeight;

	Create();
}

VOID WINDOW12::Destroy ( )
{
	bEnabled = FALSE;
}
