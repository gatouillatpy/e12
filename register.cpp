
#include "register.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



REGISTER12::REGISTER12 ( )
{
	pHead = NULL;
	pQueue = NULL;
}

REGISTER12::~REGISTER12 ( )
{
	while ( pHead )
	{
		CALLBACK12* pTemp = pHead;

		pHead = pHead->pNext;

		delete pTemp;
	}
}



VOID REGISTER12::AddCallback ( LPVOID _pCallback, LPVOID _pData )
{
	if ( pHead == NULL )
	{
		pHead = new CALLBACK12;

		pHead->lpCallback = _pCallback;
		pHead->lpData = _pData;
		pHead->pPrev = NULL;
		pHead->pNext = NULL;

		pQueue = pHead;
	}
	else
	{
		CALLBACK12* pTemp = new CALLBACK12;

		pTemp->lpCallback = _pCallback;
		pTemp->lpData = _pData;
		pTemp->pPrev = pQueue;
		pTemp->pNext = NULL;

		pQueue->pNext = pTemp;

		pQueue = pTemp;
	}
}

VOID REGISTER12::DelCallback ( LPVOID _pCallback )
{
	CALLBACK12* pTemp = pHead;

	while ( pTemp )
	{
		if ( pTemp->lpCallback == _pCallback )
			break;

		pTemp = pTemp->pNext;
	}

	if ( pTemp != NULL )
	{
		if ( pTemp == pHead )
			pHead = pTemp->pNext;
		else
			pTemp->pPrev->pNext = pTemp->pNext;

		if ( pTemp == pQueue )
			pQueue = pTemp->pPrev;
		else
			pTemp->pNext->pPrev = pTemp->pPrev;

		delete pTemp;
	}
}
