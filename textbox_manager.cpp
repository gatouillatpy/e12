
#include "textbox.h"
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID TEXTBOX12::RegisterCharCallback ( LPCHARCALLBACK _pCallback, LPVOID _pData )
{
	mChar->AddCallback( _pCallback, _pData );
}

VOID TEXTBOX12::UnregisterCharCallback ( LPCHARCALLBACK _pCallback )
{
	mChar->DelCallback( _pCallback );
}



VOID TEXTBOX12::RegisterChangeCallback ( LPCHANGECALLBACK _pCallback, LPVOID _pData )
{
	mChange->AddCallback( _pCallback, _pData );
}

VOID TEXTBOX12::UnregisterChangeCallback ( LPCHANGECALLBACK _pCallback )
{
	mChange->DelCallback( _pCallback );
}
