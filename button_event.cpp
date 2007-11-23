
#include "button.h"
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID BUTTON12::OnClick ( )
{
	CALLBACK12* pTemp = mClick->pHead;

	while ( pTemp )
	{
		LPCLICKCALLBACK Callback = (LPCLICKCALLBACK)pTemp->lpCallback;

		Callback( pTemp->lpData );

		pTemp = pTemp->pNext;
	}
}



VOID BUTTON12::OnMouseMove ( KEYCONTEXT _nKeyContext, BUTTONCONTEXT _nButtonContext, SHORT _nX, SHORT _nY )
{
	if ( bVisible == FALSE )
		return;

	SHORT x1 = (SHORT)(AbsoluteLeft() * (FLOAT)pWindow->nClientWidth);
	SHORT y1 = (SHORT)(AbsoluteTop() * (FLOAT)pWindow->nClientHeight);
	SHORT x2 = (SHORT)(AbsoluteWidth() * (FLOAT)pWindow->nClientWidth) + x1;
	SHORT y2 = (SHORT)(AbsoluteHeight() * (FLOAT)pWindow->nClientHeight) + y1;

	if ( _nX < x1 || _nX > x2 || _nY < y1 || _nY > y2 )
	{
		if ( tState == STATE_DOWN )
			tState = STATE_TEMP;

		return;
	}

	if ( _nButtonContext & BC_LEFT )
		if ( tState == STATE_TEMP )
			tState = STATE_DOWN;

	CALLBACK12* pTemp = mMouseMove->pHead;

	while ( pTemp )
	{
		LPMOUSEMOVECALLBACK Callback = (LPMOUSEMOVECALLBACK)pTemp->lpCallback;

		Callback( _nKeyContext, _nButtonContext, _nX, _nY, pTemp->lpData );

		pTemp = pTemp->pNext;
	}
}

VOID BUTTON12::OnMouseUp ( KEYCONTEXT _nKeyContext, BUTTONCONTEXT _nButtonContext, SHORT _nX, SHORT _nY )
{
	if ( bVisible == FALSE )
		return;

	SHORT x1 = (SHORT)(AbsoluteLeft() * (FLOAT)pWindow->nClientWidth);
	SHORT y1 = (SHORT)(AbsoluteTop() * (FLOAT)pWindow->nClientHeight);
	SHORT x2 = (SHORT)(AbsoluteWidth() * (FLOAT)pWindow->nClientWidth) + x1;
	SHORT y2 = (SHORT)(AbsoluteHeight() * (FLOAT)pWindow->nClientHeight) + y1;

	if ( _nX < x1 || _nX > x2 || _nY < y1 || _nY > y2 )
	{
		tState = STATE_UP;

		return;
	}

	if ( tState == STATE_DOWN )
		OnClick();

	tState = STATE_UP;

	pRender->pFocus = this;

	CALLBACK12* pTemp = mMouseUp->pHead;

	while ( pTemp )
	{
		LPMOUSEUPCALLBACK Callback = (LPMOUSEUPCALLBACK)pTemp->lpCallback;

		Callback( _nKeyContext, _nButtonContext, _nX, _nY, pTemp->lpData );

		pTemp = pTemp->pNext;
	}
}

VOID BUTTON12::OnMouseDown ( KEYCONTEXT _nKeyContext, BUTTONCONTEXT _nButtonContext, SHORT _nX, SHORT _nY )
{
	if ( bVisible == FALSE )
		return;

	SHORT x1 = (SHORT)(AbsoluteLeft() * (FLOAT)pWindow->nClientWidth);
	SHORT y1 = (SHORT)(AbsoluteTop() * (FLOAT)pWindow->nClientHeight);
	SHORT x2 = (SHORT)(AbsoluteWidth() * (FLOAT)pWindow->nClientWidth) + x1;
	SHORT y2 = (SHORT)(AbsoluteHeight() * (FLOAT)pWindow->nClientHeight) + y1;

	if ( _nX < x1 || _nX > x2 || _nY < y1 || _nY > y2 )
	{
		tState = STATE_UP;

		return;
	}

	if ( _nButtonContext & BC_LEFT )
		tState = STATE_DOWN;

	pRender->pFocus = this;

	CALLBACK12* pTemp = mMouseDown->pHead;

	while ( pTemp )
	{
		LPMOUSEDOWNCALLBACK Callback = (LPMOUSEDOWNCALLBACK)pTemp->lpCallback;

		Callback( _nKeyContext, _nButtonContext, _nX, _nY, pTemp->lpData );

		pTemp = pTemp->pNext;
	}
}
