
#include "engine.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID ENGINE12::DelResource ( LPSTR _sFile )
{
	RESOURCE12* pResource = iResource->Get( _sFile );

	if ( pResource )
		iResource->Del( pResource );
}



VOID ENGINE12::DelWindow ( WINDOW12* _pWindow )
{
	_pWindow->Release();
}



VOID ENGINE12::DelInput ( INPUT12* _pInput )
{
	_pInput->Release();
}



VOID ENGINE12::DelRender ( RENDER12* _pRender )
{
	_pRender->Release();
}



VOID ENGINE12::DelTimer ( TIMER12* _pTimer )
{
	_pTimer->Release();
}
