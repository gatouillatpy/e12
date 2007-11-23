
#include "input.h"
#include "engine.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



KEYBOARD12* INPUT12::GetKeyboardProfile ( DWORD _dwIndex )
{
	return (KEYBOARD12*)iKeyboardProfile->Get( _dwIndex );
}

KEYBOARD12* INPUT12::GetKeyboardProfile ( LPSTR _sName )
{
	return (KEYBOARD12*)iKeyboardProfile->Get( _sName );
}



MOUSE12* INPUT12::GetMouseProfile ( DWORD _dwIndex )
{
	return (MOUSE12*)iMouseProfile->Get( _dwIndex );
}

MOUSE12* INPUT12::GetMouseProfile ( LPSTR _sName )
{
	return (MOUSE12*)iMouseProfile->Get( _sName );
}
