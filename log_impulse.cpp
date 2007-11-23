
#include "log.h"
#include "impulse.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID LOG12::Push ( LPSTR _sFile, DWORD _dwLine, CODE _nLevel, CODE _nClass, CODE _nNumber, LPVOID _pClass, LPVOID _pData, LPSTR _pComment )
{
	pStack = new IMPULSE12( pStack, _sFile, _dwLine, _nLevel, _nClass, _nNumber, _pClass, _pData, _pComment );

	nLevel = _nLevel;

	OnImpulse( _sFile, _dwLine, _nLevel, _nClass, _nNumber, _pClass, _pData, _pComment );
}

IMPULSE12* LOG12::Pop ( )
{
	if ( pStack )
	{
		IMPULSE12* pImpulse = pStack;

		pStack = pStack->pParent;

		return pImpulse;
	}
	else
	{
		return NULL;
	}
}



VOID LOG12::Clear ( )
{
	while ( pStack )
	{
		IMPULSE12* pImpulse = pStack;

		pStack = pStack->pParent;

		delete pImpulse;
	}
}



VOID LOG12::Report ( )
{
	IMPULSE12* pImpulse = pStack;

	while ( pImpulse )
	{
		pImpulse->Report( this );

		pImpulse = pImpulse->pParent;
	}

	OnReport();
}



CODE LOG12::Level ( )
{
	return nLevel;
}
