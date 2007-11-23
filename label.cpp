
#include "label.h"
#include "interface.h"
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



LABEL12::LABEL12 ( RENDER12* _pRender ) : FRAME12( _pRender )
{
	pCaption = NULL;
	sCaption = NULL;

	pFont = NULL;

	fFontSize = 0.72f;

	vFontColor.x = 1.0f; vFontColor.y = 1.0f; vFontColor.z = 1.0f; vFontColor.w = 1.0f;

	bBorder = TRUE;

	pFontBlendState = NULL;

	tStyle = STYLE_WIN9X;

	fMaxWidth = 1.0f;
	fMaxHeight = 1.0f;

	fOffsetX = 0.0f;
	fOffsetY = 0.0f;

	bAutoSize = FALSE;
	bAutoWrap = FALSE;
	bAutoOffset = FALSE;

	fLineSpacing = 1.0f;

	InitializeCriticalSection( &cs );
}

LABEL12::~LABEL12 ( )
{
	if ( sCaption )
		delete [] sCaption;

	DeleteCriticalSection( &cs );
}
