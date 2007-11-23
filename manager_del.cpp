
#include "impulse.h"
#include "manager.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



BOOLEAN MANAGER12::DelResource( NODE12* & _pNode, RESOURCE12* _pResource )
{
	if ( _pNode )
	{
		if ( _pResource < _pNode->pResource )
		{
			if ( DelResource( _pNode->pA, _pResource ) == FALSE )
				return 0;

			Evaluate( _pNode );
		}
		else if ( _pResource > _pNode->pResource )
		{
			if ( DelResource( _pNode->pB, _pResource ) == FALSE )
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

BOOLEAN MANAGER12::DelEntity( NODE12* & _pNode, RESOURCE12* _pResource )
{
	if ( _pNode )
	{
		LONG nDiff = _pNode->pResource - _pResource;
		if ( nDiff > 0 )
		{
			if ( DelEntity( _pNode->pA, _pResource ) == FALSE )
				return 0;

			Evaluate( _pNode );
		}
		else if ( nDiff < 0 )
		{
			if ( DelEntity( _pNode->pB, _pResource ) == FALSE )
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

BOOLEAN MANAGER12::DelFile( NODE12* & _pNode, RESOURCE12* _pResource )
{
	if ( _pNode )
	{
		LONG nDiff = StringCompare( _pResource->sFile, _pNode->pResource->sFile );
		if ( nDiff > 0 )
		{
			if ( DelFile( _pNode->pA, _pResource ) == FALSE )
				return 0;

			Evaluate( _pNode );
		}
		else if ( nDiff < 0 )
		{
			if ( DelFile( _pNode->pB, _pResource ) == FALSE )
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



VOID MANAGER12::Del ( RESOURCE12* _pResource )
{
	if ( _pResource == NULL )
		return;

	DelResource( pResourceRoot, _pResource );
	DelEntity( pEntityRoot, _pResource );
	DelFile( pFileRoot, _pResource );
}
