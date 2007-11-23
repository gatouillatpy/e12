
#include "object.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID OBJECT12::ProcessCommand ( LPSTR sCommand )
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
	else if ( StringCompareLc( sObject, "move" ) == 0 )
	{
		StringJump( sCommand );
		FLOAT x = StringToFloat( sCommand, " ,;", 0.0f );

		StringJump( sCommand );
		FLOAT y = StringToFloat( sCommand, " ,;", 4.0f );

		StringJump( sCommand );
		FLOAT z = StringToFloat( sCommand, " ,;)\n", 0.0f );

		Move( x, y, z );
	}
}



VOID OBJECT12::ProcessHelp ( )
{
	pLog->WriteLn( "Aide - Object :\n" );
	pLog->Report();
}
