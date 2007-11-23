
#include "mouse.h"
#include "input.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



MOUSE12::MOUSE12 ( INPUT12* _pInput ) : ENTITY12( _pInput->iMouseProfile, _pInput->pEngine )
{
	dwBufferSize = _pInput->dwMouseBufferSize;

	lpMoveCallback = NULL;
	lpButtonUpCallback = NULL;
	lpButtonDownCallback = NULL;
	lpWheelUpCallback = NULL;
	lpWheelDownCallback = NULL;
}



VOID MOUSE12::SetMoveCallback ( LPMOVECALLBACK _lpCallback )
{
	lpMoveCallback = _lpCallback;
}

VOID MOUSE12::SetButtonUpCallback ( LPBUTTONUPCALLBACK _lpCallback )
{
	lpButtonUpCallback = _lpCallback;
}

VOID MOUSE12::SetButtonDownCallback ( LPBUTTONDOWNCALLBACK _lpCallback )
{
	lpButtonDownCallback = _lpCallback;
}

VOID MOUSE12::SetWheelUpCallback ( LPWHEELUPCALLBACK _lpCallback )
{
	lpWheelUpCallback = _lpCallback;
}

VOID MOUSE12::SetWheelDownCallback ( LPWHEELDOWNCALLBACK _lpCallback )
{
	lpWheelDownCallback = _lpCallback;
}



VOID MOUSE12::OnMove ( FLOAT _fX, FLOAT _fY )
{
	if ( lpMoveCallback )
		lpMoveCallback( _fX, _fY );
}

VOID MOUSE12::OnButtonUp ( BYTE _nButton )
{
	if ( lpButtonUpCallback )
		lpButtonUpCallback( _nButton );
}

VOID MOUSE12::OnButtonDown ( BYTE _nButton )
{
	if ( lpButtonDownCallback )
		lpButtonDownCallback( _nButton );
}

VOID MOUSE12::OnWheelUp ( FLOAT _fZ )
{
	if ( lpWheelUpCallback )
		lpWheelUpCallback( _fZ );
}

VOID MOUSE12::OnWheelDown ( FLOAT _fZ )
{
	if ( lpWheelDownCallback )
		lpWheelDownCallback( _fZ );
}



VOID MOUSE12::Update ( LPDIRECTINPUTDEVICE8 _lpDIMouse, BOOLEAN _bButton[], FLOAT & _fX, FLOAT & _fY, FLOAT & _fZ )
{
	if( _lpDIMouse == NULL ) return;

	LPDIDEVICEOBJECTDATA didod = new DIDEVICEOBJECTDATA[dwBufferSize];
	DWORD dwCount = dwBufferSize;

	if( _lpDIMouse->GetDeviceData( sizeof(DIDEVICEOBJECTDATA), didod, &dwCount, 0 ) )
	{
		while( _lpDIMouse->Acquire() == DIERR_INPUTLOST );
		delete [] didod;
		return; 
	}

	SHORT tX = 0L;
	SHORT tY = 0L;
	SHORT tZ = 0L;

	for( DWORD i = 0L ; i < dwCount ; i++ ) 
	{
		if ( didod[i].dwOfs > 0xFF ) continue;
		if( didod[i].dwData & 0x80 )
		{
			switch( didod[i].dwOfs )
			{
				case DIMOFS_BUTTON0: _bButton[0] = 1; OnButtonDown( 0L ); break;
				case DIMOFS_BUTTON1: _bButton[1] = 1; OnButtonDown( 1L ); break;
				case DIMOFS_BUTTON2: _bButton[2] = 1; OnButtonDown( 2L ); break;
				case DIMOFS_BUTTON3: _bButton[3] = 1; OnButtonDown( 3L ); break;
				case DIMOFS_BUTTON4: _bButton[4] = 1; OnButtonDown( 4L ); break;
				case DIMOFS_BUTTON5: _bButton[5] = 1; OnButtonDown( 5L ); break;
				case DIMOFS_BUTTON6: _bButton[6] = 1; OnButtonDown( 6L ); break;
				case DIMOFS_BUTTON7: _bButton[7] = 1; OnButtonDown( 7L ); break;
			}
		}
		else
		{
			switch( didod[i].dwOfs )
			{
				case DIMOFS_BUTTON0: _bButton[0] = 0; OnButtonUp( 0L ); break;
				case DIMOFS_BUTTON1: _bButton[1] = 0; OnButtonUp( 1L ); break;
				case DIMOFS_BUTTON2: _bButton[2] = 0; OnButtonUp( 2L ); break;
				case DIMOFS_BUTTON3: _bButton[3] = 0; OnButtonUp( 3L ); break;
				case DIMOFS_BUTTON4: _bButton[4] = 0; OnButtonUp( 4L ); break;
				case DIMOFS_BUTTON5: _bButton[5] = 0; OnButtonUp( 5L ); break;
				case DIMOFS_BUTTON6: _bButton[6] = 0; OnButtonUp( 6L ); break;
				case DIMOFS_BUTTON7: _bButton[7] = 0; OnButtonUp( 7L ); break;
			}
		}
		switch( didod[i].dwOfs )
		{
			case DIMOFS_X: tX += (SHORT)didod[i].dwData; break;
			case DIMOFS_Y: tY += (SHORT)didod[i].dwData; break;
			case DIMOFS_Z: tZ += (SHORT)didod[i].dwData; break;
		}
	}

	_fX = 0.001f * (FLOAT)tX;
	_fY = 0.001f * (FLOAT)tY;
	_fZ = 0.001f * (FLOAT)tZ;

	if ( tX != 0L || tY != 0L )	OnMove( _fX, _fY );

	if ( tZ > 0L ) OnWheelUp( _fZ );
	if ( tZ < 0L ) OnWheelDown( -_fZ );

	delete [] didod;
}
