
#include "impulse.h"
#include "indexer.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



ENTITY12* INDEXER12::GetIndex( NODE12* & _pNode, DWORD _dwIndex )
{
	if ( _pNode )
	{
		LONG nDiff = _pNode->pEntity->dwIndex - _dwIndex;
		if ( nDiff > 0 )
		{
			return GetIndex( _pNode->pA, _dwIndex );
		}
		else if ( nDiff < 0 )
		{
			return GetIndex( _pNode->pB, _dwIndex );
		}
		else
		{
			return _pNode->pEntity;
		}
	}
	else
	{
		return NULL;
	}
}

ENTITY12* INDEXER12::GetName( NODE12* & _pNode, LPSTR _sName )
{
	if ( _pNode )
	{
		LONG nDiff = StringCompare( _sName, _pNode->pEntity->sName );
		if ( nDiff > 0 )
		{
			return GetName( _pNode->pA, _sName );
		}
		else if ( nDiff < 0 )
		{
			return GetName( _pNode->pB, _sName );
		}
		else
		{
			return _pNode->pEntity;
		}
	}
	else
	{
		return NULL;
	}
}



ENTITY12* INDEXER12::Get ( DWORD _dwIndex )
{
	return GetIndex( pIndexRoot, _dwIndex );
}

ENTITY12* INDEXER12::Get ( LPSTR _sName )
{
	return GetName( pNameRoot, _sName );
}
