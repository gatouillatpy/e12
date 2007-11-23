
#include "window.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID WINDOW12::RegisterCharCallback ( LPCHARCALLBACK _pCallback, LPVOID _pData )
{
	mChar->AddCallback( _pCallback, _pData );
}

VOID WINDOW12::UnregisterCharCallback ( LPCHARCALLBACK _pCallback )
{
	mChar->DelCallback( _pCallback );
}



VOID WINDOW12::RegisterShowCallback ( LPSHOWCALLBACK _pCallback, LPVOID _pData )
{
	mShow->AddCallback( _pCallback, _pData );
}

VOID WINDOW12::UnregisterShowCallback ( LPSHOWCALLBACK _pCallback )
{
	mShow->DelCallback( _pCallback );
}

VOID WINDOW12::RegisterHideCallback ( LPHIDECALLBACK _pCallback, LPVOID _pData )
{
	mHide->AddCallback( _pCallback, _pData );
}

VOID WINDOW12::UnregisterHideCallback ( LPHIDECALLBACK _pCallback )
{
	mHide->DelCallback( _pCallback );
}



VOID WINDOW12::RegisterKeyUpCallback ( LPKEYUPCALLBACK _pCallback, LPVOID _pData )
{
	mKeyUp->AddCallback( _pCallback, _pData );
}

VOID WINDOW12::UnregisterKeyUpCallback ( LPKEYUPCALLBACK _pCallback )
{
	mKeyUp->DelCallback( _pCallback );
}

VOID WINDOW12::RegisterKeyDownCallback ( LPKEYDOWNCALLBACK _pCallback, LPVOID _pData )
{
	mKeyDown->AddCallback( _pCallback, _pData );
}

VOID WINDOW12::UnregisterKeyDownCallback ( LPKEYDOWNCALLBACK _pCallback )
{
	mKeyDown->DelCallback( _pCallback );
}



VOID WINDOW12::RegisterMouseMoveCallback ( LPMOUSEMOVECALLBACK _pCallback, LPVOID _pData )
{
	mMouseMove->AddCallback( _pCallback, _pData );
}

VOID WINDOW12::UnregisterMouseMoveCallback ( LPMOUSEMOVECALLBACK _pCallback )
{
	mMouseMove->DelCallback( _pCallback );
}

VOID WINDOW12::RegisterMouseUpCallback ( LPMOUSEUPCALLBACK _pCallback, LPVOID _pData )
{
	mMouseUp->AddCallback( _pCallback, _pData );
}

VOID WINDOW12::UnregisterMouseUpCallback ( LPMOUSEUPCALLBACK _pCallback )
{
	mMouseUp->DelCallback( _pCallback );
}

VOID WINDOW12::RegisterMouseDownCallback ( LPMOUSEDOWNCALLBACK _pCallback, LPVOID _pData )
{
	mMouseDown->AddCallback( _pCallback, _pData );
}

VOID WINDOW12::UnregisterMouseDownCallback ( LPMOUSEDOWNCALLBACK _pCallback )
{
	mMouseDown->DelCallback( _pCallback );
}



VOID WINDOW12::RegisterMaximizeCallback ( LPMAXIMIZECALLBACK _pCallback, LPVOID _pData )
{
	mMaximize->AddCallback( _pCallback, _pData );
}

VOID WINDOW12::UnregisterMaximizeCallback ( LPMAXIMIZECALLBACK _pCallback )
{
	mMaximize->DelCallback( _pCallback );
}

VOID WINDOW12::RegisterMinimizeCallback ( LPMINIMIZECALLBACK _pCallback, LPVOID _pData )
{
	mMinimize->AddCallback( _pCallback, _pData );
}

VOID WINDOW12::UnregisterMinimizeCallback ( LPMINIMIZECALLBACK _pCallback )
{
	mMinimize->DelCallback( _pCallback );
}



VOID WINDOW12::RegisterResizeCallback ( LPRESIZECALLBACK _pCallback, LPVOID _pData )
{
	mResize->AddCallback( _pCallback, _pData );
}

VOID WINDOW12::UnregisterResizeCallback ( LPRESIZECALLBACK _pCallback )
{
	mResize->DelCallback( _pCallback );
}



VOID WINDOW12::RegisterCloseCallback ( LPCLOSECALLBACK _pCallback, LPVOID _pData )
{
	mClose->AddCallback( _pCallback, _pData );
}

VOID WINDOW12::UnregisterCloseCallback ( LPCLOSECALLBACK _pCallback )
{
	mClose->DelCallback( _pCallback );
}
