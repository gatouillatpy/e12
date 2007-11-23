
#include "control.h"
#include "interface.h"
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID CONTROL12::OnKeyUp ( KEYCONTEXT _nKeyContext, BYTE _nKeyCode )
{
	if ( pRender->pFocus != this )
		return;

	CALLBACK12* pTemp = mKeyUp->pHead;

	while ( pTemp )
	{
		LPKEYUPCALLBACK Callback = (LPKEYUPCALLBACK)pTemp->lpCallback;

		Callback( _nKeyContext, _nKeyCode, pTemp->lpData );

		pTemp = pTemp->pNext;
	}
}

VOID CONTROL12::OnKeyDown ( KEYCONTEXT _nKeyContext, BYTE _nKeyCode )
{
	if ( pRender->pFocus != this )
		return;

	CALLBACK12* pTemp = mKeyDown->pHead;

	while ( pTemp )
	{
		LPKEYDOWNCALLBACK Callback = (LPKEYDOWNCALLBACK)pTemp->lpCallback;

		Callback( _nKeyContext, _nKeyCode, pTemp->lpData );

		pTemp = pTemp->pNext;
	}
}



VOID CONTROL12::OnMouseMove ( KEYCONTEXT _nKeyContext, BUTTONCONTEXT _nButtonContext, SHORT _nX, SHORT _nY )
{
	if ( bVisible == FALSE )
		return;

	SHORT x1 = (SHORT)(AbsoluteLeft() * (FLOAT)pWindow->nClientWidth);
	SHORT y1 = (SHORT)(AbsoluteTop() * (FLOAT)pWindow->nClientHeight);
	SHORT x2 = (SHORT)(AbsoluteWidth() * (FLOAT)pWindow->nClientWidth) + x1;
	SHORT y2 = (SHORT)(AbsoluteHeight() * (FLOAT)pWindow->nClientHeight) + y1;

	if ( _nX < x1 || _nX > x2 || _nY < y1 || _nY > y2 )
		return;
	
	CALLBACK12* pTemp = mMouseMove->pHead;

	while ( pTemp )
	{
		LPMOUSEMOVECALLBACK Callback = (LPMOUSEMOVECALLBACK)pTemp->lpCallback;

		Callback( _nKeyContext, _nButtonContext, _nX, _nY, pTemp->lpData );

		pTemp = pTemp->pNext;
	}
}

VOID CONTROL12::OnMouseUp ( KEYCONTEXT _nKeyContext, BUTTONCONTEXT _nButtonContext, SHORT _nX, SHORT _nY )
{
	if ( bVisible == FALSE )
		return;

	SHORT x1 = (SHORT)(AbsoluteLeft() * (FLOAT)pWindow->nClientWidth);
	SHORT y1 = (SHORT)(AbsoluteTop() * (FLOAT)pWindow->nClientHeight);
	SHORT x2 = (SHORT)(AbsoluteWidth() * (FLOAT)pWindow->nClientWidth) + x1;
	SHORT y2 = (SHORT)(AbsoluteHeight() * (FLOAT)pWindow->nClientHeight) + y1;

	if ( _nX < x1 || _nX > x2 || _nY < y1 || _nY > y2 )
		return;

	CALLBACK12* pTemp = mMouseUp->pHead;

	while ( pTemp )
	{
		LPMOUSEUPCALLBACK Callback = (LPMOUSEUPCALLBACK)pTemp->lpCallback;

		Callback( _nKeyContext, _nButtonContext, _nX, _nY, pTemp->lpData );

		pTemp = pTemp->pNext;
	}
}

VOID CONTROL12::OnMouseDown ( KEYCONTEXT _nKeyContext, BUTTONCONTEXT _nButtonContext, SHORT _nX, SHORT _nY )
{
	if ( bVisible == FALSE )
		return;

	SHORT x1 = (SHORT)(AbsoluteLeft() * (FLOAT)pWindow->nClientWidth);
	SHORT y1 = (SHORT)(AbsoluteTop() * (FLOAT)pWindow->nClientHeight);
	SHORT x2 = (SHORT)(AbsoluteWidth() * (FLOAT)pWindow->nClientWidth) + x1;
	SHORT y2 = (SHORT)(AbsoluteHeight() * (FLOAT)pWindow->nClientHeight) + y1;

	if ( _nX < x1 || _nX > x2 || _nY < y1 || _nY > y2 )
		return;

	CALLBACK12* pTemp = mMouseDown->pHead;

	while ( pTemp )
	{
		LPMOUSEDOWNCALLBACK Callback = (LPMOUSEDOWNCALLBACK)pTemp->lpCallback;

		Callback( _nKeyContext, _nButtonContext, _nX, _nY, pTemp->lpData );

		pTemp = pTemp->pNext;
	}
}
