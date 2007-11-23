
#include "control.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID CALLBACK KeyUpCallback ( KEYCONTEXT _nKeyContext, BYTE _nKeyCode, LPVOID _lpData )
{
	CONTROL12* pControl = (CONTROL12*)_lpData;

	pControl->OnKeyUp( _nKeyContext, _nKeyCode );
}

VOID CALLBACK KeyDownCallback ( KEYCONTEXT _nKeyContext, BYTE _nKeyCode, LPVOID _lpData )
{
	CONTROL12* pControl = (CONTROL12*)_lpData;

	pControl->OnKeyDown( _nKeyContext, _nKeyCode );
}



VOID CALLBACK MouseMoveCallback ( KEYCONTEXT _nKeyContext, BUTTONCONTEXT _nButtonContext, SHORT _nX, SHORT _nY, LPVOID _lpData )
{
	CONTROL12* pControl = (CONTROL12*)_lpData;

	pControl->OnMouseMove( _nKeyContext, _nButtonContext, _nX, _nY );
}

VOID CALLBACK MouseUpCallback ( KEYCONTEXT _nKeyContext, BUTTONCONTEXT _nButtonContext, SHORT _nX, SHORT _nY, LPVOID _lpData )
{
	CONTROL12* pControl = (CONTROL12*)_lpData;

	pControl->OnMouseUp( _nKeyContext, _nButtonContext, _nX, _nY );
}

VOID CALLBACK MouseDownCallback ( KEYCONTEXT _nKeyContext, BUTTONCONTEXT _nButtonContext, SHORT _nX, SHORT _nY, LPVOID _lpData )
{
	CONTROL12* pControl = (CONTROL12*)_lpData;

	pControl->OnMouseDown( _nKeyContext, _nButtonContext, _nX, _nY );
}
