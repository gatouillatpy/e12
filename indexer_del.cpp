
#include "impulse.h"
#include "indexer.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



BOOLEAN INDEXER12::DelEntity( NODE12* & _pNode, ENTITY12* _pEntity )
{
	if ( _pNode )
	{
		if ( _pEntity < _pNode->pEntity )
		{
			if ( DelEntity( _pNode->pA, _pEntity ) == FALSE )
				return 0;

			Evaluate( _pNode );
		}
		else if ( _pEntity > _pNode->pEntity )
		{
			if ( DelEntity( _pNode->pB, _pEntity ) == FALSE )
				return 0;

			Evaluate( _pNode );
		}
		else
		{
			if ( _pNode->pA )
			{
				/* extraction du plus petit élément du sous arbre droit */
				if ( _pNode->pB )
				{
					NODE12* tNode = Extract( _pNode->pB );
					tNode->pA = _pNode->pA;
					tNode->pB = _pNode->pB;

					delete _pNode;
					_pNode = tNode;
					Evaluate( _pNode );
				}
				else
				{
					NODE12* tNode = _pNode->pA;

					delete _pNode;
					_pNode = tNode;
				}
			}
			else
			{
				if ( _pNode->pB )
				{
					NODE12* tNode = _pNode->pB;

					delete _pNode;
					_pNode = tNode;
				}
				else
				{
					delete _pNode;
					_pNode = NULL;
				}
			}

			return 1;
		}

		/* rééquilibrage de l'arbre si nécessaire */
		Normalize( _pNode );
	}
	else
	{
		return 0;
	}

	return 1;
}

BOOLEAN INDEXER12::DelIndex( NODE12* & _pNode, ENTITY12* _pEntity )
{
	if ( _pNode )
	{
		LONG nDiff = _pNode->pEntity->dwIndex - _pEntity->dwIndex;
		if ( nDiff > 0 )
		{
			if ( DelIndex( _pNode->pA, _pEntity ) == FALSE )
				return 0;

			Evaluate( _pNode );
		}
		else if ( nDiff < 0 )
		{
			if ( DelIndex( _pNode->pB, _pEntity ) == FALSE )
				return 0;

			Evaluate( _pNode );
		}
		else
		{
			if ( _pNode->pA )
			{
				/* extraction du plus petit élément du sous arbre droit */
				if ( _pNode->pB )
				{
					NODE12* tNode = Extract( _pNode->pB );
					tNode->pA = _pNode->pA;
					tNode->pB = _pNode->pB;

					delete _pNode;
					_pNode = tNode;
					Evaluate( _pNode );
				}
				else
				{
					NODE12* tNode = _pNode->pA;

					delete _pNode;
					_pNode = tNode;
				}
			}
			else
			{
				if ( _pNode->pB )
				{
					NODE12* tNode = _pNode->pB;

					delete _pNode;
					_pNode = tNode;
				}
				else
				{
					delete _pNode;
					_pNode = NULL;
				}
			}

			return 1;
		}

		/* rééquilibrage de l'arbre si nécessaire */
		Normalize( _pNode );
	}
	else
	{
		return 0;
	}

	return 1;
}

BOOLEAN INDEXER12::DelName( NODE12* & _pNode, ENTITY12* _pEntity )
{
	if ( _pNode )
	{
		LONG nDiff = StringCompare( _pEntity->sName, _pNode->pEntity->sName );
		if ( nDiff > 0 )
		{
			if ( DelName( _pNode->pA, _pEntity ) == FALSE )
				return 0;

			Evaluate( _pNode );
		}
		else if ( nDiff < 0 )
		{
			if ( DelName( _pNode->pB, _pEntity ) == FALSE )
				return 0;

			Evaluate( _pNode );
		}
		else
		{
			if ( _pNode->pA )
			{
				/* extraction du plus petit élément du sous arbre droit */
				if ( _pNode->pB )
				{
					NODE12* tNode = Extract( _pNode->pB );
					tNode->pA = _pNode->pA;
					tNode->pB = _pNode->pB;

					delete _pNode;
					_pNode = tNode;

					Evaluate( _pNode );
				}
				else
				{
					NODE12* tNode = _pNode->pA;

					delete _pNode;
					_pNode = tNode;
				}
			}
			else
			{
				if ( _pNode->pB )
				{
					NODE12* tNode = _pNode->pB;

					delete _pNode;
					_pNode = tNode;
				}
				else
				{
					delete _pNode;
					_pNode = NULL;
				}
			}

			return 1;
		}

		/* rééquilibrage de l'arbre si nécessaire */
		Normalize( _pNode );
	}
	else
	{
		return 0;
	}

	return 1;
}

BOOLEAN INDEXER12::DelTick( NODE12* & _pNode, ENTITY12* _pEntity )
{
	if ( _pNode )
	{
		LONG nDiff = _pEntity->dwTick - _pNode->pEntity->dwTick;
		if ( nDiff > 0 )
		{
			if ( DelTick( _pNode->pA, _pEntity ) == FALSE )
				return 0;

			Evaluate( _pNode );
		}
		else if ( nDiff < 0 )
		{
			if ( DelTick( _pNode->pB, _pEntity ) == FALSE )
				return 0;

			Evaluate( _pNode );
		}
		else
		{
			if ( _pNode->pA )
			{
				/* extraction du plus petit élément du sous arbre droit */
				if ( _pNode->pB )
				{
					NODE12* tNode = Extract( _pNode->pB );
					tNode->pA = _pNode->pA;
					tNode->pB = _pNode->pB;

					delete _pNode;
					_pNode = tNode;

					Evaluate( _pNode );
				}
				else
				{
					NODE12* tNode = _pNode->pA;

					delete _pNode;
					_pNode = tNode;
				}
			}
			else
			{
				if ( _pNode->pB )
				{
					NODE12* tNode = _pNode->pB;

					delete _pNode;
					_pNode = tNode;
				}
				else
				{
					delete _pNode;
					_pNode = NULL;
				}
			}

			return 1;
		}

		/* rééquilibrage de l'arbre si nécessaire */
		Normalize( _pNode );
	}
	else
	{
		return 0;
	}

	return 1;
}



VOID INDEXER12::Del ( ENTITY12* _pEntity )
{
	/* vérification de la validité de l'entité à supprimer */
	if ( _pEntity == NULL )
		return;

	/* vérouillage */
	if ( bLock == TRUE )
		return;
	else
		bLock = TRUE;

	/* suppression de l'entité de l'arbre de recherche par référence */
	DelEntity( pEntityRoot, _pEntity );

	/* suppression de l'entité de l'arbre de recherche par indice si nécessaire */
	if ( _pEntity->dwIndex != -1 )
		DelIndex( pIndexRoot, _pEntity );

	/* suppression de l'entité de l'arbre de recherche par nom si nécessaire */
	if ( _pEntity->sName != NULL )
		DelName( pNameRoot, _pEntity );

	/* suppression de l'entité de l'arbre de recherche par position */
	DelTick( pTickRoot, _pEntity );

	/* décrémentation du compteur */
	dwCount--;

	/* dévérouillage */
	bLock = FALSE;

	bVector = FALSE;
}
