
#include "engine.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID ENGINE12::Wait ( DWORD dwTime )
{
	WaitForSingleObject( hEvent, dwTime );
}



VOID ENGINE12::UpdateTime ( )
{
	nMarkCount++;

	DOUBLE fTime = GetTime();
	fDelta = fTime - fFrameTime;
	fFrameTime = fTime;

	if ( fFrameTime - fMarkTime >= 1.0 )
	{
		nTotalCount += nMarkCount;

		fAverageFramerate = (DOUBLE)nTotalCount / (fFrameTime - fBeginTime);
		fCurrentFramerate = (DOUBLE)nMarkCount / (fFrameTime - fMarkTime);

		fMarkTime = fFrameTime;
		nMarkCount = 0L;
	}
}



DOUBLE ENGINE12::GetTime ( )
{
	LONGLONG nCounter, nFrequency;
	QueryPerformanceCounter( (LARGE_INTEGER*)&nCounter );
	QueryPerformanceFrequency( (LARGE_INTEGER*)&nFrequency );
	return (DOUBLE)nCounter / (DOUBLE)nFrequency;
}

DOUBLE ENGINE12::GetDelta ( )
{
	return fDelta;
}



DOUBLE ENGINE12::GetCurrentFramerate ( )
{
	return fCurrentFramerate;
}

DOUBLE ENGINE12::GetAverageFramerate ( )
{
	return fAverageFramerate;
}
