
#include "engine.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID ENGINE12::ProcessCommand ( LPSTR sCommand )
{
	static CHAR sObject[256];
	ZeroMemory( sObject, 256 );

	/* on saute les espaces et tabulations éventuellement devant */
	StringJump( sCommand );

	/* on recopie le nom de l'objet théoriquement en début de commande */
	StringToString( sObject, sCommand, " .(\n" );

	ENTITY12* pEntity = NULL;

	if ( StringCompareLc( sObject, "help" ) == 0 )
	{
		ProcessHelp();
	}
	else if ( (pEntity = iWindow->Get(sObject)) != NULL )
	{
		WINDOW12* pWindow = (WINDOW12*)pEntity;
		pWindow->ProcessCommand( sCommand );
	}
	else if ( (pEntity = iInput->Get(sObject)) != NULL )
	{
		INPUT12* pInput = (INPUT12*)pEntity;
		pInput->ProcessCommand( sCommand );
	}
	else if ( (pEntity = iRender->Get(sObject)) != NULL )
	{
		RENDER12* pRender = (RENDER12*)pEntity;
		pRender->ProcessCommand( sCommand );
	}
	else if ( (pEntity = iTimer->Get(sObject)) != NULL )
	{
		TIMER12* pTimer = (TIMER12*)pEntity;
		pTimer->ProcessCommand( sCommand );
	}
}



VOID ENGINE12::ProcessHelp ( )
{
	pLog->WriteLn( "Aide - Console :\n" );
	pLog->WriteLn( "    La console permet la gestion dynamique des entités nommés." );
	pLog->WriteLn( "\n  Utilisation :" );
	pLog->WriteLn( "    entityname[.subentityname].method [arg0, arg1, ..., argn]" );
	pLog->WriteLn( "    entityname[.subentityname] operator value" );
	pLog->WriteLn( "\n  Exemple :" );
	pLog->WriteLn( "    myrender.mycube.move 11, -4, 7" );
	pLog->WriteLn( "" );
	pLog->Report();
}
