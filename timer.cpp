
#include "timer.h"
#include "engine.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



TIMER12::TIMER12( ENGINE12* _pEngine ) : ENTITY12( _pEngine->iTimer, _pEngine )
{
	nInterval = 1000;

	nLoop = 0;
	nCount = 1;

	pThread = NULL;

	mTimer = new REGISTER12;

	bEnabled = FALSE;
}

TIMER12::~TIMER12 ( )
{
	delete mTimer;
}



DWORD TIMER12::GetInterval ( )
{
	return nInterval;
}

VOID TIMER12::SetInterval ( DWORD _nInterval )
{
	nInterval = _nInterval;
}



DWORD TIMER12::GetCount ( )
{
	return nCount;
}

VOID TIMER12::SetCount ( DWORD _nCount )
{
	nCount = _nCount;
}



VOID TIMER12::Reset ( )
{
	nLoop = 0;
}



VOID TIMER12::Start ( )
{
	bEnabled = TRUE;

	pThread = pEngine->RegisterThread( TimerThread, (LPVOID)this );
}

VOID TIMER12::Stop ( )
{
	bEnabled = FALSE;
}



VOID TIMER12::RegisterTimerCallback ( LPTIMERCALLBACK _pCallback, LPVOID _pData )
{
	mTimer->AddCallback( _pCallback, _pData );
}

VOID TIMER12::UnregisterTimerCallback ( LPTIMERCALLBACK _pCallback )
{
	mTimer->DelCallback( _pCallback );
}



VOID TIMER12::OnTimer ( )
{
	CALLBACK12* pTemp = mTimer->pHead;

	while ( pTemp )
	{
		LPTIMERCALLBACK Callback = (LPTIMERCALLBACK)pTemp->lpCallback;

		Callback( pTemp->lpData );

		pTemp = pTemp->pNext;
	}
}
