
#include "keyboard.h"
#include "input.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



KEYBOARD12::KEYBOARD12 ( INPUT12* _pInput ) : ENTITY12( _pInput->iKeyboardProfile, _pInput->pEngine )
{
	dwBufferSize = _pInput->dwKeyboardBufferSize;

	lpKeyUpCallback	   = NULL;
	lpKeyDownCallback  = NULL;
	lpKeyPressCallback = NULL;
}



VOID KEYBOARD12::SetKeyUpCallback ( LPKEYUPCALLBACK _lpCallback )
{
	lpKeyUpCallback = _lpCallback;
}

VOID KEYBOARD12::SetKeyDownCallback ( LPKEYDOWNCALLBACK _lpCallback )
{
	lpKeyDownCallback = _lpCallback;
}

VOID KEYBOARD12::SetKeyPressCallback ( LPKEYPRESSCALLBACK _lpCallback )
{
	lpKeyPressCallback = _lpCallback;
}



VOID KEYBOARD12::OnKeyUp ( DWORD _nKey )
{
	if ( lpKeyUpCallback )
		lpKeyUpCallback( _nKey );
}

VOID KEYBOARD12::OnKeyDown ( DWORD _nKey )
{
	if ( lpKeyDownCallback )
		lpKeyDownCallback( _nKey );
}

VOID KEYBOARD12::OnKeyPress ( DWORD _nKey )
{
	if ( lpKeyPressCallback )
		lpKeyPressCallback( _nKey );
}



VOID KEYBOARD12::Update ( LPDIRECTINPUTDEVICE8 _lpDIKeyboard, BOOLEAN _bKey[] )
{
	if( _lpDIKeyboard == NULL ) return;

	LPDIDEVICEOBJECTDATA didod	= new DIDEVICEOBJECTDATA[dwBufferSize];
	DWORD dwCount = dwBufferSize;

	if ( _lpDIKeyboard->GetDeviceData( sizeof(DIDEVICEOBJECTDATA), didod, &dwCount, 0 ) )
	{
		while( _lpDIKeyboard->Acquire() == DIERR_INPUTLOST );
		delete [] didod;
		return; 
	}

	for( DWORD i = 0L ; i < dwCount ; i++ ) 
	{
		if ( didod[i].dwOfs > 0xFF ) continue;

		if( didod[i].dwData & 0x80 )
		{
			_bKey[didod[i].dwOfs] = TRUE;
			OnKeyPress( didod[i].dwOfs );
		}
		else
		{
			_bKey[didod[i].dwOfs] = FALSE;
			OnKeyUp( didod[i].dwOfs );
		}
	}

	for( DWORD k = 0 ; k < 256 ; k++ ) 
		if ( _bKey[k] )	OnKeyDown( k );
		
	delete [] didod;
}
