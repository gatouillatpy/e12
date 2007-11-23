
#include "shader.h"
#include "render.h"
#include "engine.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



SHADER12::SHADER12 ( RENDER12* _pRender ) : ENTITY12( _pRender->iShader, _pRender->pEngine )
{
	pRender = _pRender;

	pResource = NULL;

	lpVertexShader = NULL;
	lpPixelShader = NULL;

	lpVSCode = NULL;
	lpPSCode = NULL;

	lpError = NULL;

	lpVSData = NULL;
	lpPSData = NULL;

	lpSetupCallback = NULL;
	lpSetupData = NULL;
}

SHADER12::~SHADER12 ( )
{
	if ( pResource )
		pResource->DelEntity( this );

	if ( lpVertexShader )
		lpVertexShader->Release();

	if ( lpPixelShader )
		lpPixelShader->Release();

	if( lpVSCode )
		lpVSCode->Release(); 

	if( lpPSCode )
		lpPSCode->Release(); 

	if( lpVSData )
		lpVSData->Release(); 

	if( lpPSData )
		lpPSData->Release(); 
}
