
#include "textbox.h"
#include "interface.h"
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



TEXTBOX12::TEXTBOX12 ( RENDER12* _pRender ) : LABEL12( _pRender )
{
	mChar = new REGISTER12;

	mChange = new REGISTER12;

	pWindow->RegisterCharCallback( CharCallback, this );

	sText = new CHAR[2048];
	ZeroMemory( sText, 2048 );

	nCursor = 0;
}

TEXTBOX12::~TEXTBOX12 ( )
{
	delete mChar;

	delete mChange;

	delete [] sText;
}
