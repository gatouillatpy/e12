
#include "window.h"
#include "engine.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID WINDOW12::OnChar ( KEYCONTEXT _nKeyContext, BYTE _nCharCode )
{
	CALLBACK12* pTemp = mChar->pHead;

	while ( pTemp )
	{
		LPCHARCALLBACK Callback = (LPCHARCALLBACK)pTemp->lpCallback;

		Callback( _nKeyContext, _nCharCode, pTemp->lpData );

		pTemp = pTemp->pNext;
	}
}



VOID WINDOW12::OnShow ( )
{
	CALLBACK12* pTemp = mShow->pHead;

	while ( pTemp )
	{
		LPSHOWCALLBACK Callback = (LPSHOWCALLBACK)pTemp->lpCallback;

		Callback( pTemp->lpData );

		pTemp = pTemp->pNext;
	}
}

VOID WINDOW12::OnHide ( )
{
	CALLBACK12* pTemp = mHide->pHead;

	while ( pTemp )
	{
		LPHIDECALLBACK Callback = (LPHIDECALLBACK)pTemp->lpCallback;

		Callback( pTemp->lpData );

		pTemp = pTemp->pNext;
	}
}



VOID WINDOW12::OnKeyUp ( KEYCONTEXT _nKeyContext, BYTE _nKeyCode )
{
	CALLBACK12* pTemp = mKeyUp->pHead;

	while ( pTemp )
	{
		LPKEYUPCALLBACK Callback = (LPKEYUPCALLBACK)pTemp->lpCallback;

		Callback( _nKeyContext, _nKeyCode, pTemp->lpData );

		pTemp = pTemp->pNext;
	}
}

VOID WINDOW12::OnKeyDown ( KEYCONTEXT _nKeyContext, BYTE _nKeyCode )
{
	CALLBACK12* pTemp = mKeyDown->pHead;

	while ( pTemp )
	{
		LPKEYDOWNCALLBACK Callback = (LPKEYDOWNCALLBACK)pTemp->lpCallback;

		Callback( _nKeyContext, _nKeyCode, pTemp->lpData );

		pTemp = pTemp->pNext;
	}
}



VOID WINDOW12::OnMouseMove ( KEYCONTEXT _nKeyContext, BUTTONCONTEXT _nButtonContext, SHORT _nX, SHORT _nY )
{
	CALLBACK12* pTemp = mMouseMove->pHead;

	while ( pTemp )
	{
		LPMOUSEMOVECALLBACK Callback = (LPMOUSEMOVECALLBACK)pTemp->lpCallback;

		Callback( _nKeyContext, _nButtonContext, _nX, _nY, pTemp->lpData );

		pTemp = pTemp->pNext;
	}
}

VOID WINDOW12::OnMouseUp ( KEYCONTEXT _nKeyContext, BUTTONCONTEXT _nButtonContext, SHORT _nX, SHORT _nY )
{
	CALLBACK12* pTemp = mMouseUp->pHead;

	while ( pTemp )
	{
		LPMOUSEUPCALLBACK Callback = (LPMOUSEUPCALLBACK)pTemp->lpCallback;

		Callback( _nKeyContext, _nButtonContext, _nX, _nY, pTemp->lpData );

		pTemp = pTemp->pNext;
	}
}

VOID WINDOW12::OnMouseDown ( KEYCONTEXT _nKeyContext, BUTTONCONTEXT _nButtonContext, SHORT _nX, SHORT _nY )
{
	CALLBACK12* pTemp = mMouseDown->pHead;

	while ( pTemp )
	{
		LPMOUSEDOWNCALLBACK Callback = (LPMOUSEDOWNCALLBACK)pTemp->lpCallback;

		Callback( _nKeyContext, _nButtonContext, _nX, _nY, pTemp->lpData );

		pTemp = pTemp->pNext;
	}
}



VOID WINDOW12::OnMaximize ( )
{
	CALLBACK12* pTemp = mMaximize->pHead;

	while ( pTemp )
	{
		LPMAXIMIZECALLBACK Callback = (LPMAXIMIZECALLBACK)pTemp->lpCallback;

		Callback( pTemp->lpData );

		pTemp = pTemp->pNext;
	}
}

VOID WINDOW12::OnMinimize ( )
{
	CALLBACK12* pTemp = mMinimize->pHead;

	while ( pTemp )
	{
		LPMINIMIZECALLBACK Callback = (LPMINIMIZECALLBACK)pTemp->lpCallback;

		Callback( pTemp->lpData );

		pTemp = pTemp->pNext;
	}
}



VOID WINDOW12::OnResize ( SHORT _nWidth, SHORT _nHeight )
{
	CALLBACK12* pTemp = mResize->pHead;

	while ( pTemp )
	{
		LPRESIZECALLBACK Callback = (LPRESIZECALLBACK)pTemp->lpCallback;

		Callback( _nWidth, _nHeight, pTemp->lpData );

		pTemp = pTemp->pNext;
	}
}



VOID WINDOW12::OnClose ( )
{
	CALLBACK12* pTemp = mClose->pHead;

	while ( pTemp )
	{
		LPCLOSECALLBACK Callback = (LPCLOSECALLBACK)pTemp->lpCallback;

		Callback( pTemp->lpData );

		pTemp = pTemp->pNext;
	}
}
