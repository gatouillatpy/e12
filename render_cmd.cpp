
#include "render.h"
#include "indexer.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID RENDER12::ProcessCommand ( LPSTR sCommand )
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
	else if ( StringCompareLc( sObject, "addscene" ) == 0 )
	{
		StringJump( sCommand );

		CHAR sName[256]; StringToString( sName, sCommand, " .),;\n" );

		if ( _IsStringEmpty( sName ) == 0 )
			if ( _IsStringValidName( sName ) == 1 )
				AddScene()->SetName( sName );
			else
				pLog->WriteLn( ">> La méthode addscene a échoué car le nom passé en paramètre n'est pas au format alphanumérique." );
		else
			pLog->WriteLn( ">> La méthode addscene a échoué car aucun nom n'a été passé en paramètre." );
	}
	else if ( StringCompareLc( sObject, "addbox" ) == 0 )
	{
		StringJump( sCommand );

		CHAR sName[256]; StringToString( sName, sCommand, " .),;\n" );

		if ( _IsStringEmpty( sName ) == 0 )
			if ( _IsStringValidName( sName ) == 1 )
				AddBox()->SetName( sName );
			else
				pLog->WriteLn( ">> La méthode addbox a échoué car le nom passé en paramètre n'est pas au format alphanumérique." );
		else
			pLog->WriteLn( ">> La méthode addbox a échoué car aucun nom n'a été passé en paramètre." );
	}
	else if ( (pEntity = iScene->Get(sObject)) != NULL )
	{
		SCENE12* pScene = (SCENE12*)pEntity;
		pScene->ProcessCommand( sCommand );
	}
	else if ( (pEntity = iObject->Get(sObject)) != NULL )
	{
		OBJECT12* pObject = (OBJECT12*)pEntity;
		pObject->ProcessCommand( sCommand );
	}
	else if ( (pEntity = iInterface->Get(sObject)) != NULL )
	{
		INTERFACE12* pInterface = (INTERFACE12*)pEntity;
		pInterface->ProcessCommand( sCommand );
	}
	else if ( (pEntity = iControl->Get(sObject)) != NULL )
	{
		CONTROL12* pControl = (CONTROL12*)pEntity;
		pControl->ProcessCommand( sCommand );
	}
	else if ( (pEntity = iCamera->Get(sObject)) != NULL )
	{
		CAMERA12* pCamera = (CAMERA12*)pEntity;
		pCamera->ProcessCommand( sCommand );
	}
	else if ( (pEntity = iGeometry->Get(sObject)) != NULL )
	{
		GEOMETRY12* pGeometry = (GEOMETRY12*)pEntity;
		pGeometry->ProcessCommand( sCommand );
	}
	else if ( (pEntity = iHitbox->Get(sObject)) != NULL )
	{
		HITBOX12* pHitbox = (HITBOX12*)pEntity;
		pHitbox->ProcessCommand( sCommand );
	}
	else if ( (pEntity = iTexture->Get(sObject)) != NULL )
	{
		TEXTURE12* pTexture = (TEXTURE12*)pEntity;
		pTexture->ProcessCommand( sCommand );
	}
	else if ( (pEntity = iFont->Get(sObject)) != NULL )
	{
		FONT12* pFont = (FONT12*)pEntity;
		pFont->ProcessCommand( sCommand );
	}
	else if ( (pEntity = iShader->Get(sObject)) != NULL )
	{
		SHADER12* pShader = (SHADER12*)pEntity;
		pShader->ProcessCommand( sCommand );
	}
}



VOID RENDER12::ProcessHelp ( )
{
	pLog->WriteLn( "Aide - Render :\n" );
	pLog->WriteLn( "    Le moteur de rendu gère l'affichage de controles ou d'objets." );
	pLog->WriteLn( "\n  Méthodes :" );
	pLog->WriteLn( "    addscene scenename" );
	pLog->WriteLn( "    addbox objectname" );
	pLog->Report();
}
