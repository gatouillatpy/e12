
#include "document.h"
#include "impulse.h"
#include "log.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



BOOLEAN DOCUMENT12::Load ( LPSTR _sPath )
{
	assert( _sPath );

	LPSTR tPath = StringPath( GetDir(), _sPath );

	if ( CheckFile( tPath ) == 0 ) 
	{
		pLog->Push( __FILE__, __LINE__, CODE_ERROR, CODE_DOCUMENT12, 0x0001, this, NULL, _sPath ); return 0;
	}

	FILE* pFile = NULL;

	fopen_s( &pFile, tPath, "rb" );

	fseek( pFile, 0, SEEK_END );
	DWORD dwSize = ftell(pFile);

	fseek( pFile, 0, SEEK_SET );

	BYTE* pData = new BYTE[dwSize+1];
	fread( pData, sizeof(BYTE), dwSize, pFile );
	pData[dwSize] = 0;

	fclose( pFile );

	BYTE* _pData = pData;
	Parse( _pData );

	delete [] pData;

	SetPath( _sPath );

	return 1;
}

BOOLEAN DOCUMENT12::Save ( LPSTR _sPath )
{
	assert( _sPath );

	LPSTR tPath = StringPath( GetDir(), _sPath );

	BYTE* pData = new BYTE[65536];

	BYTE* _pData = pData;
	Build( _pData );

	DWORD dwSize =  _pData - pData;

	FILE* pFile = NULL;
	if ( fopen_s(&pFile, tPath, "wb") )
		return 0;

	fseek( pFile, 0, SEEK_SET );

	fwrite( pData, sizeof(BYTE), dwSize, pFile );

	fclose( pFile );

	delete [] pData;

	SetPath( _sPath );

	return 1;
}
