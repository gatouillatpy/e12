
#include "impulse.h"
#include "entity.h"
#include "indexer.h"
#include "engine.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



ENTITY12::ENTITY12 ( INDEXER12* _iLocal, ENGINE12* _pEngine )
{
	pResource = NULL;

	iLocal = _iLocal;
	iLocal->Add( this );

	pEngine = _pEngine;

	pLog = _pEngine->pLog;

	dwIndex = -1;

	sName = NULL;

	dwRefCount = 1;
}

ENTITY12::~ENTITY12 ( )
{
	if ( pResource )
		pResource->DelEntity( this );

	iLocal->Del( this );

	if ( sName )
		delete [] sName;
}



DWORD ENTITY12::GetIndex ( )
{
	return dwIndex;
}

VOID ENTITY12::SetIndex ( DWORD _dwIndex )
{
	/* l'indexeur se charge de réattribuer le nouvel indice */
	iLocal->Set( this, _dwIndex );
}



LPSTR ENTITY12::GetName ( )
{
	return sName;
}

VOID ENTITY12::SetName ( LPSTR _sName )
{
	/* l'indexeur se charge de réattribuer le nouveau nom */
	iLocal->Set( this, _sName );
}



VOID ENTITY12::AddRef ( )
{
	dwRefCount++;
}



VOID ENTITY12::Release ( )
{
	dwRefCount--;

	if ( dwRefCount == 0 ) delete this;
}
