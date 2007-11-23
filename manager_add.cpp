
#include "impulse.h"
#include "manager.h"
#include "log.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID MANAGER12::AddResource( NODE12* & _pNode, RESOURCE12* _pResource )
{
	if ( _pNode )
	{
		if ( _pResource < _pNode->pResource )
		{
			AddResource( _pNode->pA, _pResource );
			Evaluate( _pNode );
		}
		else if ( _pResource > _pNode->pResource )
		{
			AddResource( _pNode->pB, _pResource );
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
		_pNode->pResource = _pResource;
		_pNode->pEntity = NULL;
		_pNode->pA = NULL;
		_pNode->pB = NULL;
		_pNode->nHeight = 1;
		_pNode->nFactor = 0;
	}
}

VOID MANAGER12::AddEntity( NODE12* & _pNode, RESOURCE12* _pResource, ENTITY12* _pEntity )
{
	if ( _pNode )
	{
		LONG nDiff = _pNode->pEntity - _pEntity;
		if ( nDiff > 0 )
		{
			AddEntity( _pNode->pA, _pResource, _pEntity );
			Evaluate( _pNode );
		}
		else if ( nDiff < 0 )
		{
			AddEntity( _pNode->pB, _pResource, _pEntity );
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
		_pNode->pResource = _pResource;
		_pNode->pEntity = _pEntity;
		_pNode->pA = NULL;
		_pNode->pB = NULL;
		_pNode->nHeight = 1;
		_pNode->nFactor = 0;
	}
}

VOID MANAGER12::AddFile( NODE12* & _pNode, RESOURCE12* _pResource )
{
	if ( _pNode )
	{
		LONG nDiff = StringCompare( _pResource->sFile, _pNode->pResource->sFile );
		if ( nDiff > 0 )
		{
			AddFile( _pNode->pA, _pResource );
			Evaluate( _pNode );
		}
		else if ( nDiff < 0 )
		{
			AddFile( _pNode->pB, _pResource );
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
		_pNode->pResource = _pResource;
		_pNode->pEntity = NULL;
		_pNode->pA = NULL;
		_pNode->pB = NULL;
		_pNode->nHeight = 1;
		_pNode->nFactor = 0;
	}
}
