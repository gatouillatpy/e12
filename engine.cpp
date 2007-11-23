
#include "engine.h"
#include "document.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



ENGINE12::ENGINE12 ( )
{
	nThreadCount = 0;
	ppThread = NULL;

	pLog = new LOG12;

	iResource = new MANAGER12(pLog);
	iWindow = new INDEXER12(pLog);
	iInput = new INDEXER12(pLog);
	iRender = new INDEXER12(pLog);
	iTimer = new INDEXER12(pLog);

	DOUBLE fTime = GetTime();
	fFrameTime = fTime;
	fMarkTime = fTime;
	fBeginTime = fTime;
	fDelta = 0.0;

	nMarkCount = 0L;
	nTotalCount = 0L;

	fCurrentFramerate = 0.0;
	fAverageFramerate = 0.0;

	hEvent = CreateEvent( NULL, FALSE, FALSE, NULL );
}

ENGINE12::~ENGINE12 ( )
{
	for ( DWORD k = 0 ; k < nThreadCount ; k++ )
		if ( ppThread[k] )
			TerminateThread( ppThread[k], 0 );

	delete [] ppThread;

	iInput->Free();
	iTimer->Free();
	iWindow->Free();
	iRender->Free();

	delete iResource;

	delete pLog;

	CloseHandle( hEvent );
}



HANDLE* ENGINE12::RegisterThread ( LPTHREAD_START_ROUTINE _pStartAddress, LPVOID _pParameter )
{
	DWORD k = nThreadCount;

	ppThread = (HANDLE*) realloc( ppThread, ++nThreadCount * sizeof(HANDLE) );
	ppThread[k] = CreateThread( NULL, 0, _pStartAddress, _pParameter, 0, NULL );

	return &ppThread[k];
}
