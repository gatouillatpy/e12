
#include "textbox.h"
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID CALLBACK CharCallback ( KEYCONTEXT _nKeyContext, BYTE _nCharCode, LPVOID _lpData )
{
	TEXTBOX12* pTextbox = (TEXTBOX12*)_lpData;

	pTextbox->OnChar( _nKeyContext, _nCharCode );
}
