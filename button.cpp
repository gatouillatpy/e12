
#include "button.h"
#include "interface.h"
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



BUTTON12::BUTTON12 ( RENDER12* _pRender ) : LABEL12( _pRender )
{
	mClick = new REGISTER12;

	tState = STATE_UP;
}

BUTTON12::~BUTTON12 ( )
{
	delete mClick;
}
