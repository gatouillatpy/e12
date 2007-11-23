
#include "render.h"
#include "engine.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID RENDER12::DelCamera ( CAMERA12* _pCamera )
{
	_pCamera->Release();
}



VOID RENDER12::DelControl ( CONTROL12* _pControl )
{
	_pControl->Release();
}



VOID RENDER12::DelInterface ( INTERFACE12* _pInterface )
{
	_pInterface->Release();
}



VOID RENDER12::DelObject ( OBJECT12* _pObject )
{
	_pObject->Release();
}



VOID RENDER12::DelScene ( SCENE12* _pScene )
{
	_pScene->Release();
}



VOID RENDER12::DelGeometry ( GEOMETRY12* _pGeometry )
{
	_pGeometry->Release();
}



VOID RENDER12::DelHitbox ( HITBOX12* _pHitbox )
{
	_pHitbox->Release();
}



VOID RENDER12::DelTexture ( TEXTURE12* _pTexture )
{
	_pTexture->Release();
}



VOID RENDER12::DelFont ( FONT12* _pFont )
{
	_pFont->Release();
}



VOID RENDER12::DelShader ( SHADER12* _pShader )
{
	_pShader->Release();
}
