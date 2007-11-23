
#include "impulse.h"
#include "manager.h"
#include "log.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



RESOURCE12* MANAGER12::Set ( ENTITY12* _pEntity, LPSTR _sFile )
{
	RESOURCE12* pResource = Get( _pEntity );
	
	if ( pResource )
	{
		pResource->DelEntity( _pEntity );
	}

	pResource = Get( _sFile );
	
	if ( pResource )
	{
		pResource->AddEntity( _pEntity );
	}
	else
	{
		pResource = new RESOURCE12( _sFile );

		pResource->AddEntity( _pEntity );
		
		AddResource ( pResourceRoot, pResource );
		AddEntity ( pEntityRoot, pResource, _pEntity );
		AddFile ( pFileRoot, pResource );
	}

	return pResource;
}
