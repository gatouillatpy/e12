
#include "interface.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID INTERFACE12::ProcessCommand ( LPSTR sCommand )
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
}



VOID INTERFACE12::ProcessHelp ( )
{
	pLog->WriteLn( "Aide - Interface :\n" );
	pLog->Report();
}
