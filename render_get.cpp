
#include "render.h"
#include "engine.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



CAMERA12* RENDER12::GetCamera ( DWORD _dwIndex )
{
	return (CAMERA12*)iCamera->Get( _dwIndex );
}

CAMERA12* RENDER12::GetCamera ( LPSTR _sName )
{
	return (CAMERA12*)iCamera->Get( _sName );
}



CONTROL12* RENDER12::GetControl ( DWORD _dwIndex )
{
	return (CONTROL12*)iControl->Get( _dwIndex );
}

CONTROL12* RENDER12::GetControl ( LPSTR _sName )
{
	return (CONTROL12*)iControl->Get( _sName );
}



INTERFACE12* RENDER12::GetInterface ( DWORD _dwIndex )
{
	return (INTERFACE12*)iInterface->Get( _dwIndex );
}

INTERFACE12* RENDER12::GetInterface ( LPSTR _sName )
{
	return (INTERFACE12*)iInterface->Get( _sName );
}



OBJECT12* RENDER12::GetObject ( DWORD _dwIndex )
{
	return (OBJECT12*)iObject->Get( _dwIndex );
}

OBJECT12* RENDER12::GetObject ( LPSTR _sName )
{
	return (OBJECT12*)iObject->Get( _sName );
}



SCENE12* RENDER12::GetScene ( DWORD _dwIndex )
{
	return (SCENE12*)iScene->Get( _dwIndex );
}

SCENE12* RENDER12::GetScene ( LPSTR _sName )
{
	return (SCENE12*)iScene->Get( _sName );
}



GEOMETRY12* RENDER12::GetGeometry ( DWORD _dwIndex )
{
	return (GEOMETRY12*)iGeometry->Get( _dwIndex );
}

GEOMETRY12* RENDER12::GetGeometry ( LPSTR _sName )
{
	return (GEOMETRY12*)iGeometry->Get( _sName );
}



HITBOX12* RENDER12::GetHitbox ( DWORD _dwIndex )
{
	return (HITBOX12*)iHitbox->Get( _dwIndex );
}

HITBOX12* RENDER12::GetHitbox ( LPSTR _sName )
{
	return (HITBOX12*)iHitbox->Get( _sName );
}



TEXTURE12* RENDER12::GetTexture ( DWORD _dwIndex )
{
	return (TEXTURE12*)iTexture->Get( _dwIndex );
}

TEXTURE12* RENDER12::GetTexture ( LPSTR _sName )
{
	return (TEXTURE12*)iTexture->Get( _sName );
}



FONT12* RENDER12::GetFont ( DWORD _dwIndex )
{
	return (FONT12*)iFont->Get( _dwIndex );
}

FONT12* RENDER12::GetFont ( LPSTR _sName )
{
	return (FONT12*)iFont->Get( _sName );
}



SHADER12* RENDER12::GetShader ( DWORD _dwIndex )
{
	return (SHADER12*)iShader->Get( _dwIndex );
}

SHADER12* RENDER12::GetShader ( LPSTR _sName )
{
	return (SHADER12*)iShader->Get( _sName );
}
