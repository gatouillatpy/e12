
#include "frame.h"
#include "interface.h"
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



FRAME12::FRAME12 ( RENDER12* _pRender ) : CONTROL12( _pRender )
{
	vBackColor.x = 0.0f; vBackColor.y = 0.0f; vBackColor.z = 0.0f; vBackColor.w = 1.0f;
	vBorderColor.x = 1.0f; vBorderColor.y = 1.0f; vBorderColor.z = 1.0f; vBorderColor.w = 1.0f;

	bBorder = TRUE;

	pBackBlendState = NULL;
	pBorderBlendState = NULL;

	tBorderStyle = BS_WIN9X_BACK;
}
