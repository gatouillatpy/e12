
#include "render.h"
#include "engine.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID WINDOW12::WriteSettings ( LPSTR _sSection, LPSTR _sFile )
{
	CHAR sData[256];

	WritePrivateProfileString( _sSection, "Name", sName, _sFile );

	WritePrivateProfileString( _sSection, "Title", sTitle, _sFile );

	StringPrint( sData, 256, "%d", bVisible );
	WritePrivateProfileString( _sSection, "Visible", sData, _sFile );

	StringPrint( sData, 256, "%d", wcState );
	WritePrivateProfileString( _sSection, "State", sData, _sFile );

	StringPrint( sData, 256, "%d", nLeft );
	WritePrivateProfileString( _sSection, "Left", sData, _sFile );

	StringPrint( sData, 256, "%d", nTop );
	WritePrivateProfileString( _sSection, "Top", sData, _sFile );

	StringPrint( sData, 256, "%d", nWidth );
	WritePrivateProfileString( _sSection, "Width", sData, _sFile );

	StringPrint( sData, 256, "%d", nHeight );
	WritePrivateProfileString( _sSection, "Height", sData, _sFile );
}

VOID WINDOW12::ReadSettings ( LPSTR _sSection, LPSTR _sFile )
{
	CHAR sData[256];

	GetPrivateProfileString( _sSection, "Name", "", sData, 256, _sFile );
	SetName( sData );

	GetPrivateProfileString( _sSection, "Title", "", sData, 256, _sFile );
	SetTitle( sData );

	GetPrivateProfileString( _sSection, "Visible", "", sData, 256, _sFile );
	StringScan( sData, "%d", &bVisible );

	GetPrivateProfileString( _sSection, "State", "", sData, 256, _sFile );
	StringScan( sData, "%d", &wcState );

	GetPrivateProfileString( _sSection, "Left", "", sData, 256, _sFile );
	StringScan( sData, "%d", &nLeft );

	GetPrivateProfileString( _sSection, "Top", "", sData, 256, _sFile );
	StringScan( sData, "%d", &nTop );

	GetPrivateProfileString( _sSection, "Width", "", sData, 256, _sFile );
	StringScan( sData, "%d", &nWidth );

	GetPrivateProfileString( _sSection, "Height", "", sData, 256, _sFile );
	StringScan( sData, "%d", &nHeight );
}
