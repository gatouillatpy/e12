
#include "input.h"
#include "engine.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



BOOLEAN INPUT12::Key ( BYTE _nKey )
{
	return bKey[_nKey];
}

BOOLEAN INPUT12::Button ( BYTE _nButton )
{
	return bButton[_nButton];
}



VOID INPUT12::SetKeyboardProfile ( KEYBOARD12* _pKeyboardProfile )
{
	pKeyboardProfile = _pKeyboardProfile;
}

KEYBOARD12* INPUT12::KeyboardProfile ( )
{
	return pKeyboardProfile;
}



VOID INPUT12::SetMouseProfile ( MOUSE12* _pMouseProfile )
{
	pMouseProfile = _pMouseProfile;
}

MOUSE12* INPUT12::MouseProfile ( )
{
	return pMouseProfile;
}
