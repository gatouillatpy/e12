
#include "button.h"
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID BUTTON12::Render ( )
{
	if ( bVisible == FALSE ) return;

	RenderBack();

	RenderCaption();

	if ( tStyle == STYLE_WIN9X )
	{
		if ( tState == STATE_DOWN )
			tBorderStyle = BS_WIN9X_BACK;
		else
			tBorderStyle = BS_WIN9X_FRONT;
	}

	RenderBorder();
}
