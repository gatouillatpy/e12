
#include "window.h"
#include "engine.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



WINDOW12::WINDOW12( ENGINE12* _pEngine ) : ENTITY12( _pEngine->iWindow, _pEngine )
{
	mShow = new REGISTER12;
	mHide = new REGISTER12;

	mChar = new REGISTER12;

	mKeyUp = new REGISTER12;
	mKeyDown = new REGISTER12;

	mMouseMove = new REGISTER12;
	mMouseUp = new REGISTER12;
	mMouseDown	= new REGISTER12;

	mMinimize = new REGISTER12;
	mMaximize = new REGISTER12;

	mResize = new REGISTER12;

	mClose = new REGISTER12;

	CHAR tName[9] = {0};
	StringPrint( tName, 9, "E12_%d", IRANDOM(0, 10000) );
	SetName( tName );

	SetTitle( "E12 Default Window" );

	nLeft = 160;
	nTop = 120;
	nWidth = 640;
	nHeight = 480;

	hWnd = NULL;

	wcState = WC_NORMAL;

	kcState = KC_NONE;
	bcState = BC_NONE;
	
	bEnabled = FALSE;

	bVisible = TRUE;

	pThread = NULL;
}

WINDOW12::~WINDOW12 ( )
{
	delete mShow;
	delete mHide;

	delete mChar;

	delete mKeyUp;
	delete mKeyDown;

	delete mMouseMove;
	delete mMouseUp;
	delete mMouseDown;

	delete mMinimize;
	delete mMaximize;

	delete mResize;

	delete mClose;

	if ( sTitle )
		delete [] sTitle;
}
