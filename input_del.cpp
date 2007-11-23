
#include "input.h"
#include "engine.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID INPUT12::DelKeyboardProfile ( KEYBOARD12* _pKeyboardProfile )
{
	_pKeyboardProfile->Release();
}



VOID INPUT12::DelMouseProfile ( MOUSE12* _pMouseProfile )
{
	_pMouseProfile->Release();
}
