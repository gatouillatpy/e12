
#include "impulse.h"
#include "manager.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



RESOURCE12* MANAGER12::GetEntity ( NODE12* & _pNode, ENTITY12* _pEntity )
{
	if ( _pNode )
	{
		LONG nDiff = _pNode->pEntity - _pEntity;
		if ( nDiff > 0 )
		{
			return GetEntity( _pNode->pA, _pEntity );
		}
		else if ( nDiff < 0 )
		{
			return GetEntity( _pNode->pB, _pEntity );
		}
		else
		{
			return _pNode->pResource;
		}
	}
	else
	{
		return NULL;
	}
}

RESOURCE12* MANAGER12::GetFile ( NODE12* & _pNode, LPSTR _sFile )
{
	if ( _pNode )
	{
		LONG nDiff = StringCompare( _sFile, _pNode->pResource->sFile );
		if ( nDiff > 0 )
		{
			return GetFile( _pNode->pA, _sFile );
		}
		else if ( nDiff < 0 )
		{
			return GetFile( _pNode->pB, _sFile );
		}
		else
		{
			return _pNode->pResource;
		}
	}
	else
	{
		return NULL;
	}
}



RESOURCE12* MANAGER12::Get ( ENTITY12* _pEntity )
{
	return GetEntity( pEntityRoot, _pEntity );
}

RESOURCE12* MANAGER12::Get ( LPSTR _sFile )
{
	return GetFile( pFileRoot, _sFile );
}
