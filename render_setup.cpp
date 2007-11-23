
#include "render.h"
#include "engine.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID RENDER12::WriteSettings ( LPSTR _sSection, LPSTR _sFile )
{
	CHAR sData[256];

	StringPrint( sData, 256, "%d", bWindowMode );
	WritePrivateProfileString( _sSection, "WindowMode", sData, _sFile );

	StringPrint( sData, 256, "%d", nScreenWidth );
	WritePrivateProfileString( _sSection, "FullscreenWidth", sData, _sFile );

	StringPrint( sData, 256, "%d", nScreenHeight );
	WritePrivateProfileString( _sSection, "FullscreenHeight", sData, _sFile );

	StringPrint( sData, 256, "%d", bVSync );
	WritePrivateProfileString( _sSection, "VerticalSync", sData, _sFile );

	StringPrint( sData, 256, "%d", bHardware );
	WritePrivateProfileString( _sSection, "UseHardware", sData, _sFile );

	StringPrint( sData, 256, "%d", nDraftWidth );
	WritePrivateProfileString( _sSection, "DraftWidth", sData, _sFile );

	StringPrint( sData, 256, "%d", nDraftHeight );
	WritePrivateProfileString( _sSection, "DraftHeight", sData, _sFile );

	StringPrint( sData, 256, "%d", dwDraftFlags );
	WritePrivateProfileString( _sSection, "DraftFlags", sData, _sFile );

	StringPrint( sData, 256, "%d", bShowDraft );
	WritePrivateProfileString( _sSection, "ShowDraft", sData, _sFile );

	StringPrint( sData, 256, "%d", nMaxLightmapMemory );
	WritePrivateProfileString( _sSection, "MaxLightmapMemory", sData, _sFile );

	StringPrint( sData, 256, "%d", nMaxLightmapResolution );
	WritePrivateProfileString( _sSection, "MaxLightmapResolution", sData, _sFile );

	StringPrint( sData, 256, "%d", nMinLightmapResolution );
	WritePrivateProfileString( _sSection, "MinLightmapResolution", sData, _sFile );

	StringPrint( sData, 256, "%d", nMaxCubemapMemory );
	WritePrivateProfileString( _sSection, "MaxCubemapMemory", sData, _sFile );

	StringPrint( sData, 256, "%d", nMaxCubemapResolution );
	WritePrivateProfileString( _sSection, "MaxCubemapResolution", sData, _sFile );

	StringPrint( sData, 256, "%d", nMinCubemapResolution );
	WritePrivateProfileString( _sSection, "MinCubemapResolution", sData, _sFile );

	WritePrivateProfileString( _sSection, "ShaderPath", sShaderPath, _sFile );
}

VOID RENDER12::ReadSettings ( LPSTR _sSection, LPSTR _sFile )
{
	CHAR sData[256];

	GetPrivateProfileString( _sSection, "WindowMode", "", sData, 256, _sFile );
	StringScan( sData, "%d", &bWindowMode );

	GetPrivateProfileString( _sSection, "FullscreenWidth", "", sData, 256, _sFile );
	StringScan( sData, "%d", &nScreenWidth );

	GetPrivateProfileString( _sSection, "FullscreenHeight", "", sData, 256, _sFile );
	StringScan( sData, "%d", &nScreenHeight );

	GetPrivateProfileString( _sSection, "VerticalSync", "", sData, 256, _sFile );
	StringScan( sData, "%d", &bVSync );

	GetPrivateProfileString( _sSection, "UseHardware", "", sData, 256, _sFile );
	StringScan( sData, "%d", &bHardware );

	GetPrivateProfileString( _sSection, "DraftWidth", "", sData, 256, _sFile );
	StringScan( sData, "%d", &nDraftWidth );

	GetPrivateProfileString( _sSection, "DraftHeight", "", sData, 256, _sFile );
	StringScan( sData, "%d", &nDraftHeight );

	GetPrivateProfileString( _sSection, "DraftFlags", "", sData, 256, _sFile );
	StringScan( sData, "%d", &dwDraftFlags );

	GetPrivateProfileString( _sSection, "ShowDraft", "", sData, 256, _sFile );
	StringScan( sData, "%d", &bShowDraft );

	GetPrivateProfileString( _sSection, "MaxLightmapMemory", "", sData, 256, _sFile );
	StringScan( sData, "%d", &nMaxLightmapMemory );

	GetPrivateProfileString( _sSection, "MaxLightmapResolution", "", sData, 256, _sFile );
	StringScan( sData, "%d", &nMaxLightmapResolution );

	GetPrivateProfileString( _sSection, "MinLightmapResolution", "", sData, 256, _sFile );
	StringScan( sData, "%d", &nMinLightmapResolution );

	GetPrivateProfileString( _sSection, "MaxCubemapMemory", "", sData, 256, _sFile );
	StringScan( sData, "%d", &nMaxCubemapMemory );

	GetPrivateProfileString( _sSection, "MaxCubemapResolution", "", sData, 256, _sFile );
	StringScan( sData, "%d", &nMaxCubemapResolution );

	GetPrivateProfileString( _sSection, "MinCubemapResolution", "", sData, 256, _sFile );
	StringScan( sData, "%d", &nMinCubemapResolution );

	GetPrivateProfileString( _sSection, "ShaderPath", "", sShaderPath, 256, _sFile );
}
