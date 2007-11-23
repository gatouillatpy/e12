
#include "control.h"
#include "interface.h"
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID CONTROL12::RegisterKeyUpCallback ( LPKEYUPCALLBACK _pCallback, LPVOID _pData )
{
	mKeyUp->AddCallback( _pCallback, _pData );
}

VOID CONTROL12::UnregisterKeyUpCallback ( LPKEYUPCALLBACK _pCallback )
{
	mKeyUp->DelCallback( _pCallback );
}

VOID CONTROL12::RegisterKeyDownCallback ( LPKEYDOWNCALLBACK _pCallback, LPVOID _pData )
{
	mKeyDown->AddCallback( _pCallback, _pData );
}

VOID CONTROL12::UnregisterKeyDownCallback ( LPKEYDOWNCALLBACK _pCallback )
{
	mKeyDown->DelCallback( _pCallback );
}



VOID CONTROL12::RegisterMouseMoveCallback ( LPMOUSEMOVECALLBACK _pCallback, LPVOID _pData )
{
	mMouseMove->AddCallback( _pCallback, _pData );
}

VOID CONTROL12::UnregisterMouseMoveCallback ( LPMOUSEMOVECALLBACK _pCallback )
{
	mMouseMove->DelCallback( _pCallback );
}

VOID CONTROL12::RegisterMouseUpCallback ( LPMOUSEUPCALLBACK _pCallback, LPVOID _pData )
{
	mMouseUp->AddCallback( _pCallback, _pData );
}

VOID CONTROL12::UnregisterMouseUpCallback ( LPMOUSEUPCALLBACK _pCallback )
{
	mMouseUp->DelCallback( _pCallback );
}

VOID CONTROL12::RegisterMouseDownCallback ( LPMOUSEDOWNCALLBACK _pCallback, LPVOID _pData )
{
	mMouseDown->AddCallback( _pCallback, _pData );
}

VOID CONTROL12::UnregisterMouseDownCallback ( LPMOUSEDOWNCALLBACK _pCallback )
{
	mMouseDown->DelCallback( _pCallback );
}