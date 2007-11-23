
#include "input.h"
#include "engine.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID INPUT12::Update ( )
{
	if ( pKeyboardProfile )
		pKeyboardProfile->Update( lpDIKeyboard, bKey );

	if ( pMouseProfile )
		pMouseProfile->Update( lpDIMouse, bButton, X, Y, Z );
}
