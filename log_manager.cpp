
#include "log.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID LOG12::RegisterImpulseCallback ( LPIMPULSECALLBACK _pCallback, LPVOID _pData )
{
	mImpulse->AddCallback( _pCallback, _pData );
}

VOID LOG12::UnregisterImpulseCallback ( LPIMPULSECALLBACK _pCallback )
{
	mImpulse->DelCallback( _pCallback );
}



VOID LOG12::RegisterReportCallback ( LPREPORTCALLBACK _pCallback, LPVOID _pData )
{
	mReport->AddCallback( _pCallback, _pData );
}

VOID LOG12::UnregisterReportCallback ( LPREPORTCALLBACK _pCallback )
{
	mReport->DelCallback( _pCallback );
}
