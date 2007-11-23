
#include "input.h"
#include "engine.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



KEYBOARD12* INPUT12::AddKeyboardProfile ( )
{
	return new KEYBOARD12( this );
}



MOUSE12* INPUT12::AddMouseProfile ( )
{
	return new MOUSE12( this );
}
