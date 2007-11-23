
#include "input.h"
#include "engine.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID INPUT12::WriteSettings ( LPSTR _sSection, LPSTR _sFile )
{
	CHAR sData[256];

	StringPrint( sData, 256, "%d", dwKeyboardBufferSize );
	WritePrivateProfileString( _sSection, "KeyboardBufferSize", sData, _sFile );

	StringPrint( sData, 256, "%d", dwMouseBufferSize );
	WritePrivateProfileString( _sSection, "MouseBufferSize", sData, _sFile );
}

VOID INPUT12::ReadSettings ( LPSTR _sSection, LPSTR _sFile )
{
	CHAR sData[256];

	GetPrivateProfileString( _sSection, "KeyboardBufferSize", "", sData, 256, _sFile );
	StringScan( sData, "%d", &dwKeyboardBufferSize );

	GetPrivateProfileString( _sSection, "MouseBufferSize", "", sData, 256, _sFile );
	StringScan( sData, "%d", &dwMouseBufferSize );
}
