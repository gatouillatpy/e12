
#include "box.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID BOX12::ProcessCommand ( LPSTR sCommand )
{
	OBJECT12::ProcessCommand( sCommand );

	static CHAR sObject[256];
	ZeroMemory( sObject, 256 );

	/* on saute les espaces et tabulations éventuellement devant */
	StringJump( sCommand );

	/* on recopie le nom de l'objet théoriquement en début de commande */
	StringToString( sObject, sCommand, " .(\n" );

	ENTITY12* pEntity = NULL;

	if ( StringCompareLc( sObject, "create" ) == 0 )
	{
		this->Create( 10.0f, 10.0f, 10.0f );
	}
}



VOID BOX12::ProcessHelp ( )
{
	OBJECT12::ProcessHelp();

	pLog->WriteLn( "Aide - Box :\n" );
	pLog->Report();
}
