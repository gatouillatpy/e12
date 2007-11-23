
#include "impulse.h"
#include "log.h"
#include "entity.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



IMPULSE12::IMPULSE12 ( IMPULSE12* _pParent, LPSTR _sFile, DWORD _nLine, CODE _nType, CODE _nClass, CODE _nNumber, LPVOID _pClass, LPVOID _pData, LPSTR _pComment )
{
	pParent = _pParent;

	sFile = _sFile;
	nLine = _nLine;

	nCode = _nType | _nClass | _nNumber;

	pClass = _pClass;

	pData = _pData;

	if ( _pComment != NULL )
	{
		DWORD dwLength = StringLength( _pComment ) + 1;

		pComment = new CHAR[dwLength];

		StringCopy( pComment, dwLength, _pComment );
	}
	else
	{
		pComment = NULL;
	}
}

IMPULSE12::~IMPULSE12 ( )
{
	if ( pComment )
		delete [] pComment;
}



VOID IMPULSE12::Report ( LOG12* _pLog )
{
	CODE nType = nCode & 0xF0000000;

	if ( nType == CODE_INFO )
		_pLog->WriteLn( "E12 Info >> " );
	else if ( nType == CODE_WARNING )
		_pLog->WriteLn( "E12 Warning >> " );
	else if ( nType == CODE_ERROR )
		_pLog->WriteLn( "E12 Error >> " );
	else if ( nType == CODE_CRASH )
		_pLog->WriteLn( "E12 Crash >> " );

	CODE nClass = nCode & 0x0FFF0000;

	if ( nClass == CODE_INDEXER12 )
	{
		_pLog->Write( "INDEXER12 @%p >> ", pClass );
	}
	else if ( nClass == CODE_DOCUMENT12 )
	{
		_pLog->Write( "DOCUMENT12 @%p >> ", pClass );
	}
	else
	{
		if ( nClass == CODE_INPUT12 )
			_pLog->Write( "INPUT12 " );
		else if ( nClass == CODE_RENDER12 )
			_pLog->Write( "RENDER12 " );
		else if ( nClass == CODE_OBJECT12 )
			_pLog->Write( "OBJECT12 " );
		else if ( nClass == CODE_COMPLEX12 )
			_pLog->Write( "COMPLEX12 " );
		else if ( nClass == CODE_FONT12 )
			_pLog->Write( "FONT12 " );
		else if ( nClass == CODE_SHADER12 )
			_pLog->Write( "SHADER12 " );
		else if ( nClass == CODE_ANIMATION12 )
			_pLog->Write( "ANIMATION12 " );
		else if ( nClass == CODE_VOLUME12 )
			_pLog->Write( "VOLUME12 " );
		else if ( nClass == CODE_TEXTURE12 )
			_pLog->Write( "TEXTURE12 " );
		else if ( nClass == CODE_MESH12 )
			_pLog->Write( "MESH12 " );
		else if ( nClass == CODE_GEOMETRY12 )
			_pLog->Write( "GEOMETRY12 " );

		ENTITY12* pEntity = (ENTITY12*)pClass;
		if ( pEntity->GetName() != NULL )
			_pLog->Write( "%s >> ", pEntity->GetName() );
		else if ( pEntity->GetIndex() != -1 )
			_pLog->Write( "#%d >> ", pEntity->GetIndex() );
		else
			_pLog->Write( "@%p >> ", pEntity );
	}

	CODE nNumber = nCode & 0x0000FFFF;

	if ( nClass == CODE_INDEXER12 )
	{
		if ( nNumber == 0x0001 )
			_pLog->Write( "Impossible de définir l'indice #%d, l'indexeur local contient déjà une entité ayant cet indice.", (DWORD)pData );
		else if ( nNumber == 0x0002 )
			_pLog->Write( "Impossible de définir le nom %s, l'indexeur local contient déjà une entité portant ce nom.", pComment );
		else if ( nNumber == 0x0003 )
			_pLog->Write( "Impossible de définir un nom, celui-ci n'a pas été spécifié." );
		else if ( nNumber == 0x0004 )
			_pLog->Write( "Impossible de définir le nom %s, celui-ci n'est pas alphanumérique.", pComment );
	}
	else if ( nClass == CODE_DOCUMENT12 )
	{
		if ( nNumber == 0x0001 )
			_pLog->Write( "Impossible de charger ce document, le fichier %s est introuvable.", pComment );
	}
	else if ( nClass == CODE_INPUT12 )
	{
		if ( nNumber == 0x0001 )
			_pLog->Write( "Impossible d'initialiser DirectInput, la fenêtre @%p est invalide.", pData );
	}
	else if ( nClass == CODE_RENDER12 )
	{
		if ( nNumber == 0x0001 )
			_pLog->Write( "Impossible d'initialiser Direct3D, la fenêtre @%p est invalide.", pData );
		else if ( nNumber == 0x0002 )
			_pLog->Write( "Impossible d'initialiser Direct3D, erreur système." );
		else if ( nNumber == 0x0003 )
			_pLog->Write( "Impossible de créer un Depth/Stencil Buffer au format %s, matériel incompatible.", pComment );
		else if ( nNumber == 0x0004 )
			_pLog->Write( "Impossible d'utiliser les Vertex Shader %s, matériel incompatible.", pComment );
		else if ( nNumber == 0x0005 )
			_pLog->Write( "Impossible d'utiliser les Pixel Shader %s, matériel incompatible.", pComment );
	}
	else if ( nClass == CODE_OBJECT12 )
	{
		/*
		if ( nNumber == 0x0001 )
			_pLog->Write( "Risque de rendu incorrect, la texture @%p n'est pas valide.", pData );
		else if ( nNumber == 0x0002 )
			_pLog->Write( "Risque de rendu incorrect, le matériau @%p n'est pas valide.", pData );
		else if ( nNumber == 0x0003 )
			_pLog->Write( "Risque de rendu incorrect, la technique de coloration %d est inconnue.", (DWORD)pData );
		*/
	}
	else if ( nClass == CODE_COMPLEX12 )
	{
		if ( nNumber == 0x0001 )
			_pLog->Write( "Impossible d'effectuer cette union, la structure de l'arbre est corrompue." );
		else if ( nNumber == 0x0002 )
			_pLog->Write( "Impossible d'effectuer cette soustraction, il n'y a pas d'opérande gauche." );
		else if ( nNumber == 0x0003 )
			_pLog->Write( "Impossible d'effectuer cette soustraction, la structure de l'arbre est corrompue." );
		else if ( nNumber == 0x0004 )
			_pLog->Write( "Impossible d'effectuer cette intersection, il n'y a pas d'opérande gauche." );
		else if ( nNumber == 0x0005 )
			_pLog->Write( "Impossible d'effectuer cette intersection, la structure de l'arbre est corrompue." );
	}
	else if ( nClass == CODE_FONT12 )
	{
		if ( nNumber == 0x0001 )
			_pLog->Write( "Impossible de charger la police, aucun fichier n'a été spécifié." );
		else if ( nNumber == 0x0002 )
			_pLog->Write( "Impossible de charger la police, le fichier %s est introuvable.", pComment );
		else if ( nNumber == 0x0003 )
			_pLog->Write( "Impossible de charger la police, erreur interne à Direct3D : ", DXGetErrorString((HRESULT)pData) );
	}
	else if ( nClass == CODE_SHADER12 )
	{
		if ( nNumber == 0x0001 )
			_pLog->Write( "Impossible de charger le shader, aucun fichier n'a été spécifié." );
		else if ( nNumber == 0x0002 )
			_pLog->Write( "Impossible de charger le shader, le fichier %s est introuvable.", pComment );
	}
	else if ( nClass == CODE_ANIMATION12 )
	{
		if ( nNumber == 0x0001 )
			_pLog->Write( "Impossible de charger la texture animée, aucun fichier n'a été spécifié." );
		else if ( nNumber == 0x0002 )
			_pLog->Write( "Impossible de charger la texture animée, le fichier %s est introuvable.", pComment );
	}
	else if ( nClass == CODE_VOLUME12 )
	{
		if ( nNumber == 0x0001 )
			_pLog->Write( "Impossible de charger la texture volumique, aucun fichier n'a été spécifié." );
		else if ( nNumber == 0x0002 )
			_pLog->Write( "Impossible de charger la texture volumique, le fichier %s est introuvable.", pComment );
	}
	else if ( nClass == CODE_TEXTURE12 )
	{
		if ( nNumber == 0x0001 )
			_pLog->Write( "Impossible de charger la texture, aucun fichier n'a été spécifié." );
		else if ( nNumber == 0x0002 )
			_pLog->Write( "Impossible de charger la texture, le fichier %s est introuvable.", pComment );
	}
	else if ( nClass == CODE_MESH12 )
	{
		if ( nNumber == 0x0001 )
			_pLog->Write( "Impossible d'importer le mesh au format X, aucun fichier n'a été spécifié." );
		else if ( nNumber == 0x0002 )
			_pLog->Write( "Impossible d'importer le mesh au format X, le fichier %s est introuvable.", pComment );
		else if ( nNumber == 0x0003 )
			_pLog->Write( "Impossible d'importer le mesh au format 3DS, aucun fichier n'a été spécifié." );
		else if ( nNumber == 0x0004 )
			_pLog->Write( "Impossible d'importer le mesh au format 3DS, le fichier %s est introuvable.", pComment );
	}
	else if ( nClass == CODE_GEOMETRY12 )
	{
		if ( nNumber == 0x0001 )
			_pLog->Write( "Impossible de charger la géométrie, aucun fichier n'a été spécifié." );
		else if ( nNumber == 0x0002 )
			_pLog->Write( "Impossible de charger la géométrie, le fichier %s est introuvable.", pComment );
	}
}
