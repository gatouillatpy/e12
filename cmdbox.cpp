
#include "cmdbox.h"
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



CMDBOX12::CMDBOX12 ( RENDER12* _pRender ) : TEXTBOX12( _pRender )
{
	pEngine = _pRender->pEngine;
}
