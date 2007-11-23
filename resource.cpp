
#include "resource.h"
#include "engine.h"
#include "indexer.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



RESOURCE12::RESOURCE12 ( LPSTR _sFile )
{
	dwEntity = 0;
	ppEntity = NULL;

	assert(_sFile);

	DWORD dwLength = StringLength( _sFile ) + 1;

	sFile = new CHAR[dwLength];

	StringCopy( sFile, dwLength, _sFile );
}

RESOURCE12::~RESOURCE12 ( )
{
	if ( sFile )
		delete [] sFile;

	if ( ppEntity )
		delete [] ppEntity;
}



DWORD RESOURCE12::Count ( )
{
	return dwEntity;
}



VOID RESOURCE12::AddEntity ( ENTITY12* _pEntity )
{
	ppEntity = (ENTITY12**) realloc( ppEntity, ++dwEntity * sizeof(ENTITY12*) );

	ppEntity[dwEntity-1] = _pEntity;
}

VOID RESOURCE12::DelEntity ( ENTITY12* _pEntity )
{
	for ( DWORD k = 0 ; k < dwEntity ; k++ )
	{
		if ( ppEntity[k] == _pEntity )
		{
			ppEntity[k] = ppEntity[--dwEntity];

			break;
		}
	}
}



ENTITY12* RESOURCE12::operator[] ( DWORD k )
{
	if ( k >= dwEntity ) return NULL;

	return ppEntity[k];
}



LPSTR RESOURCE12::File ( )
{
	return sFile;
}



ENTITY12* RESOURCE12::Entity ( )
{
	if ( dwEntity == 0 ) return NULL;

	return ppEntity[0];
}
