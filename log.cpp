
#include "log.h"
#include "impulse.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



LOG12::LOG12 ( )
{
	pStack = NULL;

	mImpulse = new REGISTER12;
	mReport = new REGISTER12;

	dwCount = 0;

	pLine = NULL;

	nLevel = LOG_LEVEL_NULL;
}

LOG12::~LOG12 ( )
{
	delete mImpulse;
	delete mReport;

	while ( pStack )
	{
		IMPULSE12* pMessage = pStack;

		pStack = pStack->pParent;

		delete pMessage;
	}

	if ( pLine )
	{
		for ( DWORD k = 0 ; k < dwCount ; k++ )
			delete [] pLine[k];

		free(pLine);
	}
}
