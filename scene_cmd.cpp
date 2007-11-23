
#include "scene.h"
#include "render.h"
#include "indexer.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID SCENE12::ProcessCommand ( LPSTR sCommand )
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
	else if ( StringCompareLc( sObject, "addobject" ) == 0 )
	{
		StringJump( sCommand );

		CHAR sName[256]; StringToString( sName, sCommand, " .),;\n" );

		if ( _IsStringEmpty( sName ) == 0 )
			if ( _IsStringValidName( sName ) == 1 )
				if ( (pEntity = pRender->iObject->Get(sName)) != NULL )
					AddObject( (OBJECT12*)pEntity );
				else
					pLog->WriteLn( ">> La méthode addobject a échoué car aucun objet portant le nom passé en paramètre n'a été trouvé." );
			else
				pLog->WriteLn( ">> La méthode addobject a échoué car le nom passé en paramètre n'est pas au format alphanumérique." );
		else
			pLog->WriteLn( ">> La méthode addobject a échoué car aucun nom n'a été passé en paramètre." );
	}
}



VOID SCENE12::ProcessHelp ( )
{
	pLog->WriteLn( "Aide - Scene :\n" );
	pLog->WriteLn( "    La scène est un conteneur d'objets." );
	pLog->Write( " Elle peut-être cachée, déplacée, redimensionnée ou pivotée." );
	pLog->Write( " La scène peut contenir des objets mais aussi d'autres scènes." );
	pLog->Write( " Les entités contenues héritent des transformations spatiales de leur scène parente." );
	pLog->WriteLn( "\n  Méthodes :" );
	pLog->WriteLn( "    addobject objectname" );
	pLog->Report();
}
