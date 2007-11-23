
#include "timer.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



DWORD WINAPI TimerThread( LPVOID lpParam )
{
	TIMER12* pTimer = (TIMER12*)lpParam;
	
	HANDLE hEvent = CreateEvent( NULL, FALSE, FALSE, NULL );

	while ( (pTimer->nLoop < pTimer->nCount) && (pTimer->bEnabled == TRUE) )
	{
		WaitForSingleObject( hEvent, pTimer->nInterval );

		pTimer->OnTimer();

		pTimer->nLoop++;
	}

	CloseHandle( hEvent );

	*pTimer->pThread = NULL;

	return 0;
}
