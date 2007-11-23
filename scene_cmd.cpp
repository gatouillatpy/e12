
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

	/* on saute les espaces et tabulations �ventuellement devant */
	StringJump( sCommand );

	/* on recopie le nom de l'objet th�oriquement en d�but de commande */
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
					pLog->WriteLn( ">> La m�thode addobject a �chou� car aucun objet portant le nom pass� en param�tre n'a �t� trouv�." );
			else
				pLog->WriteLn( ">> La m�thode addobject a �chou� car le nom pass� en param�tre n'est pas au format alphanum�rique." );
		else
			pLog->WriteLn( ">> La m�thode addobject a �chou� car aucun nom n'a �t� pass� en param�tre." );
	}
}



VOID SCENE12::ProcessHelp ( )
{
	pLog->WriteLn( "Aide - Scene :\n" );
	pLog->WriteLn( "    La sc�ne est un conteneur d'objets." );
	pLog->Write( " Elle peut-�tre cach�e, d�plac�e, redimensionn�e ou pivot�e." );
	pLog->Write( " La sc�ne peut contenir des objets mais aussi d'autres sc�nes." );
	pLog->Write( " Les entit�s contenues h�ritent des transformations spatiales de leur sc�ne parente." );
	pLog->WriteLn( "\n  M�thodes :" );
	pLog->WriteLn( "    addobject objectname" );
	pLog->Report();
}
