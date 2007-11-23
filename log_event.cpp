
#include "log.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID LOG12::OnImpulse ( LPSTR _sFile, DWORD _dwLine, CODE _nLevel, CODE _nClass, CODE _nNumber, LPVOID _pClass, LPVOID _pData, LPSTR _pComment )
{
	CALLBACK12* pTemp = mImpulse->pHead;

	while ( pTemp )
	{
		LPIMPULSECALLBACK Callback = (LPIMPULSECALLBACK)pTemp->lpCallback;

		Callback( _sFile, _dwLine, _nLevel, _nClass, _nNumber, _pClass, _pData, _pComment, pTemp->lpData );

		pTemp = pTemp->pNext;
	}
}

VOID LOG12::OnReport ( )
{
	CALLBACK12* pTemp = mReport->pHead;

	while ( pTemp )
	{
		LPREPORTCALLBACK Callback = (LPREPORTCALLBACK)pTemp->lpCallback;

		Callback( pTemp->lpData );

		pTemp = pTemp->pNext;
	}
}
