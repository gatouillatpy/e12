
#include "impulse.h"
#include "indexer.h"
#include "log.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID INDEXER12::Set ( ENTITY12* _pEntity, DWORD _dwIndex )
{
	/* si l'indice existe déjà on renvoie une erreur */
	if ( Get( _dwIndex ) )
	{
		pLog->Push( __FILE__, __LINE__, CODE_ERROR, CODE_INDEXER12, 0x0001, this, (LPVOID)_dwIndex, NULL ); return;
	}

	/* suppression de l'entité de l'arbre de recherche par indice */
	DelIndex( pIndexRoot, _pEntity );

	/* attribution du nouvel indice */
	_pEntity->dwIndex = _dwIndex;

	/* ajout de l'entité à l'arbre de recherche par indice */
	AddIndex( pIndexRoot, _pEntity );
}

VOID INDEXER12::Set ( ENTITY12* _pEntity, LPSTR _sName )
{
	/* vérification de la validité du nom */
	if ( _sName == NULL )
	{
		pLog->Push( __FILE__, __LINE__, CODE_ERROR, CODE_INDEXER12, 0x0003, this, NULL, NULL ); return;
	}
	else if ( _IsStringValidName( _sName ) == FALSE )
	{
		pLog->Push( __FILE__, __LINE__, CODE_ERROR, CODE_INDEXER12, 0x0004, this, NULL, _sName ); return;
	}

	/* si le nom existe déjà on renvoie une erreur */
	if ( Get( _sName ) )
	{
		pLog->Push( __FILE__, __LINE__, CODE_ERROR, CODE_INDEXER12, 0x0002, this, NULL, _sName ); return;
	}

	/* suppression de l'entité de l'arbre de recherche par nom */
	if ( _pEntity->sName )
		DelName( pNameRoot, _pEntity );

	/* attribution du nom à l'entité */
	if ( _pEntity->sName )
		delete [] _pEntity->sName;
	DWORD dwLength = StringLength(_sName) + 1;
	_pEntity->sName = new CHAR[dwLength];
	StringCopy(_pEntity->sName, dwLength, _sName);

	/* ajout de l'entité à l'arbre de recherche par nom */
	AddName( pNameRoot, _pEntity );
}
