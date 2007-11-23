
#include "impulse.h"
#include "indexer.h"
#include "log.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID INDEXER12::AddEntity( NODE12* & _pNode, ENTITY12* _pEntity )
{
	if ( _pNode )
	{
		if ( _pEntity < _pNode->pEntity )
		{
			AddEntity( _pNode->pA, _pEntity );
			Evaluate( _pNode );
		}
		else if ( _pEntity > _pNode->pEntity )
		{
			AddEntity( _pNode->pB, _pEntity );
			Evaluate( _pNode );
		}
		else
		{
			assert(0);
		}

		/* rééquilibrage de l'arbre si nécessaire */
		Normalize( _pNode );
	}
	else
	{
		_pNode = new NODE12;
		_pNode->pEntity = _pEntity;
		_pNode->pA = NULL;
		_pNode->pB = NULL;
		_pNode->nHeight = 1;
		_pNode->nFactor = 0;
	}
}

VOID INDEXER12::AddIndex( NODE12* & _pNode, ENTITY12* _pEntity )
{
	if ( _pNode )
	{
		LONG nDiff = _pNode->pEntity->dwIndex - _pEntity->dwIndex;
		if ( nDiff > 0 )
		{
			AddIndex( _pNode->pA, _pEntity );
			Evaluate( _pNode );
		}
		else if ( nDiff < 0 )
		{
			AddIndex( _pNode->pB, _pEntity );
			Evaluate( _pNode );
		}
		else
		{
			assert(0);
		}

		/* rééquilibrage de l'arbre si nécessaire */
		Normalize( _pNode );
	}
	else
	{
		_pNode = new NODE12;
		_pNode->pEntity = _pEntity;
		_pNode->pA = NULL;
		_pNode->pB = NULL;
		_pNode->nHeight = 1;
		_pNode->nFactor = 0;
	}
}

VOID INDEXER12::AddName( NODE12* & _pNode, ENTITY12* _pEntity )
{
	if ( _pNode )
	{
		LONG nDiff = StringCompare( _pEntity->sName, _pNode->pEntity->sName );
		if ( nDiff > 0 )
		{
			AddName( _pNode->pA, _pEntity );
			Evaluate( _pNode );
		}
		else if ( nDiff < 0 )
		{
			AddName( _pNode->pB, _pEntity );
			Evaluate( _pNode );
		}
		else
		{
			assert(0);
		}

		/* rééquilibrage de l'arbre si nécessaire */
		Normalize( _pNode );
	}
	else
	{
		_pNode = new NODE12;
		_pNode->pEntity = _pEntity;
		_pNode->pA = NULL;
		_pNode->pB = NULL;
		_pNode->nHeight = 1;
		_pNode->nFactor = 0;
	}
}

VOID INDEXER12::AddTick( NODE12* & _pNode, ENTITY12* _pEntity )
{
	if ( _pNode )
	{
		LONG nDiff = dwTick - _pNode->pEntity->dwTick;
		if ( nDiff > 0 )
		{
			AddTick( _pNode->pA, _pEntity );
			Evaluate( _pNode );
		}
		else if ( nDiff < 0 )
		{
			AddTick( _pNode->pB, _pEntity );
			Evaluate( _pNode );
		}
		else
		{
			assert(0);
		}

		/* rééquilibrage de l'arbre si nécessaire */
		Normalize( _pNode );
	}
	else
	{
		_pNode = new NODE12;
		_pNode->pEntity = _pEntity;
		_pNode->pA = NULL;
		_pNode->pB = NULL;
		_pNode->nHeight = 1;
		_pNode->nFactor = 0;
		_pNode->pEntity->dwTick = dwTick;
	}
}



VOID INDEXER12::Add ( ENTITY12* _pEntity )
{
	/* vérouillage */
	if ( bLock == TRUE )
		return;
	else
		bLock = TRUE;

	/* ajout de l'entité à l'arbre de recherche par référence */
	AddEntity( pEntityRoot, _pEntity );

	/* incrémentation du compteur de position */
	dwTick++;

	/* ajout de l'entité à l'arbre de recherche chronologique */
	AddTick( pTickRoot, _pEntity );

	/* incrémentation du compteur d'entités */
	dwCount++;

	/* dévérouillage */
	bLock = FALSE;

	bVector = FALSE;
}
