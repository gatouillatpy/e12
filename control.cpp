
#include "control_effect.h"
#include "control.h"
#include "interface.h"
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



CONTROL12::CONTROL12 ( RENDER12* _pRender ) : ENTITY12( _pRender->iControl, _pRender->pEngine )
{
	pRender = _pRender;

	pWindow = _pRender->lpWindow;

	mKeyUp = new REGISTER12;
	mKeyDown = new REGISTER12;

	mMouseMove = new REGISTER12;
	mMouseUp = new REGISTER12;
	mMouseDown	= new REGISTER12;

	pWindow->RegisterKeyUpCallback( KeyUpCallback, this );
	pWindow->RegisterKeyDownCallback( KeyDownCallback, this );

	pWindow->RegisterMouseMoveCallback( MouseMoveCallback, this );
	pWindow->RegisterMouseUpCallback( MouseUpCallback, this );
	pWindow->RegisterMouseDownCallback( MouseDownCallback, this );

	pInterface = NULL;

	pEffect = NULL;

	fLeft = 0.2f;
	fTop = 0.2f;

	fWidth = 0.4f;
	fHeight = 0.3f;

	fAngle  = 0.0f;

	bVisible = TRUE;
}

CONTROL12::~CONTROL12 ( )
{
	delete mKeyUp;
	delete mKeyDown;

	delete mMouseMove;
	delete mMouseUp;
	delete mMouseDown;
}



VOID CONTROL12::Update ( )
{
	if ( pEffect )
		pEffect->Update();
}

VOID CONTROL12::Render ( )
{
}
