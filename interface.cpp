
#include "interface.h"
#include "render.h"
#include "indexer.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



INTERFACE12::INTERFACE12 ( RENDER12* _pRender ) : ENTITY12( _pRender->iInterface, _pRender->pEngine )
{
	pRender = _pRender;

	pParent = NULL;

	pCursor = NULL;

	iChild = new INDEXER12(pLog);
	iControl = new INDEXER12(pLog);

	fLeft = 0.0f;
	fTop = 0.0f;

	fWidth = 1.0f;
	fHeight = 1.0f;

	bVisible = TRUE;
}

INTERFACE12::~INTERFACE12 ( )
{
	delete iChild;
	delete iControl;
}
