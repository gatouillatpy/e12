
#include "button.h"
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID BUTTON12::RegisterClickCallback ( LPCLICKCALLBACK _pCallback, LPVOID _pData )
{
	mClick->AddCallback( _pCallback, _pData );
}

VOID BUTTON12::UnregisterClickCallback ( LPCLICKCALLBACK _pCallback )
{
	mClick->DelCallback( _pCallback );
}
