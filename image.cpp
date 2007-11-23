
#include "image.h"
#include "interface.h"
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



IMAGE12::IMAGE12 ( RENDER12* _pRender ) : FRAME12( _pRender )
{
	pTexture = NULL;

	fOffsetU = 0.0f;
	fOffsetV = 0.0f;

	fFactorU = 1.0f;
	fFactorV = 1.0f;
}
