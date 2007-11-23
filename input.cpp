
#include "input.h"
#include "engine.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



INPUT12::INPUT12 ( ENGINE12* _pEngine ) : ENTITY12( _pEngine->iInput, _pEngine )
{
	dwKeyboardBufferSize = 16;
	dwMouseBufferSize = 64;

	iKeyboardProfile = new INDEXER12(pLog);
	pKeyboardProfile = NULL;

	iMouseProfile = new INDEXER12(pLog);
	pMouseProfile = NULL;

	lpDI = NULL;
	lpDIKeyboard = NULL;
	lpDIMouse = NULL;     

	for( DWORD k = 0 ; k < 256 ; k++ ) 
		bKey[k] = FALSE;

	for( DWORD k = 0 ; k < 8 ; k++ ) 
		bButton[k] = FALSE;

	X = 0.0f;
	Y = 0.0f;
	Z = 0.0f;
}

INPUT12::~INPUT12 ( )
{
	iKeyboardProfile->Free();
	iMouseProfile->Free();

	if ( lpDIKeyboard )
		lpDIKeyboard->Release();
	if ( lpDIMouse )
		lpDIMouse->Release();
	if ( lpDI )
		lpDI->Release();
}
