
#include "input.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID INPUT12::ProcessCommand ( LPSTR sCommand )
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



VOID INPUT12::ProcessHelp ( )
{
	pLog->WriteLn( "Aide - Input :\n" );
	pLog->Report();
}
