
#include "input.h"
#include "engine.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



BOOLEAN INPUT12::Initialize ( WINDOW12* _pWindow )
{
	if ( _pWindow == NULL )
	{
		pLog->Push( __FILE__, __LINE__, CODE_CRASH, CODE_INPUT12, 0x0001, this, _pWindow, NULL ); return 0;
	}

	lpWindow = _pWindow;

	DirectInput8Create( GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&lpDI, NULL );
	
	DWORD dwCoopFlags = DISCL_NONEXCLUSIVE | DISCL_FOREGROUND;

	DIPROPDWORD dipdw;
	dipdw.diph.dwSize       = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj        = 0;
	dipdw.diph.dwHow        = DIPH_DEVICE;

	{
		dipdw.dwData = dwKeyboardBufferSize;

		lpDI->CreateDevice( GUID_SysKeyboard, &lpDIKeyboard, NULL );
		lpDIKeyboard->SetDataFormat( &c_dfDIKeyboard );
		lpDIKeyboard->SetCooperativeLevel( lpWindow->hWnd, dwCoopFlags );
		lpDIKeyboard->SetProperty( DIPROP_BUFFERSIZE, &dipdw.diph );

		lpDIKeyboard->Acquire();
	}

	{
		dipdw.dwData = dwMouseBufferSize;

		lpDI->CreateDevice( GUID_SysMouse, &lpDIMouse, NULL );
		lpDIMouse->SetDataFormat( &c_dfDIMouse2 );
		lpDIMouse->SetCooperativeLevel( lpWindow->hWnd, dwCoopFlags );
		lpDIMouse->SetProperty( DIPROP_BUFFERSIZE, &dipdw.diph );

		lpDIMouse->Acquire();
	}

	return 1;
}



VOID INPUT12::Terminate( )
{
}
