
#include "textbox.h"
#include "render.h"
#include "engine.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID TEXTBOX12::OnChar ( KEYCONTEXT _nKeyContext, BYTE _nCharCode )
{
	if ( pRender->pFocus != this )
		return;

	if ( _nCharCode > 31 )
		sText[nCursor++] = _nCharCode;

	LABEL12::SetCaption( sText );

	CALLBACK12* pTemp = mChar->pHead;

	while ( pTemp )
	{
		LPCHARCALLBACK Callback = (LPCHARCALLBACK)pTemp->lpCallback;

		Callback( _nKeyContext, _nCharCode, pTemp->lpData );

		pTemp = pTemp->pNext;
	}
}



VOID TEXTBOX12::OnChange ( )
{
	CALLBACK12* pTemp = mChange->pHead;

	while ( pTemp )
	{
		LPCHANGECALLBACK Callback = (LPCHANGECALLBACK)pTemp->lpCallback;

		Callback( pTemp->lpData );

		pTemp = pTemp->pNext;
	}
}



VOID TEXTBOX12::OnKeyUp ( KEYCONTEXT _nKeyContext, BYTE _nKeyCode )
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

VOID TEXTBOX12::OnKeyDown ( KEYCONTEXT _nKeyContext, BYTE _nKeyCode )
{
	if ( pRender->pFocus != this )
		return;

	if ( _nKeyCode == 13 )
	{
		DWORD nLength = StringLength( sText );
		for ( DWORD k = nLength ; k > nCursor ; k-- )
			sText[k] = sText[k-1];
		sText[nCursor++] = 10;
	}
	else if ( _nKeyCode == 8 )
	{
		if ( nCursor > 0 )
		{
			DWORD nLength = StringLength( sText );
			for ( DWORD k = --nCursor ; k < nLength ; k++ )
				sText[k] = sText[k+1];
		}
	}
	else if ( _nKeyCode == 46 )
	{
		DWORD nLength = StringLength( sText );
		if ( nCursor < nLength )
		{
			for ( DWORD k = nCursor ; k < nLength ; k++ )
				sText[k] = sText[k+1];
		}
	}
	else if ( _nKeyCode == 37 )
	{
		if ( nCursor > 0 )
			nCursor--;
	}
	else if ( _nKeyCode == 39 )
	{
		DWORD nLength = StringLength( sText );
		if ( nCursor < nLength )
			nCursor++;
	}
	else if ( _nKeyCode == 9 )
	{
		sText[nCursor++] = 32;
		sText[nCursor++] = 32;
		sText[nCursor++] = 32;
		sText[nCursor++] = 32;
	}

	LABEL12::SetCaption( sText );

	CALLBACK12* pTemp = mKeyDown->pHead;

	while ( pTemp )
	{
		LPKEYDOWNCALLBACK Callback = (LPKEYDOWNCALLBACK)pTemp->lpCallback;

		Callback( _nKeyContext, _nKeyCode, pTemp->lpData );

		pTemp = pTemp->pNext;
	}
}



VOID TEXTBOX12::OnMouseMove ( KEYCONTEXT _nKeyContext, BUTTONCONTEXT _nButtonContext, SHORT _nX, SHORT _nY )
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

VOID TEXTBOX12::OnMouseUp ( KEYCONTEXT _nKeyContext, BUTTONCONTEXT _nButtonContext, SHORT _nX, SHORT _nY )
{
	if ( bVisible == FALSE )
		return;

	SHORT x1 = (SHORT)(AbsoluteLeft() * (FLOAT)pWindow->nClientWidth);
	SHORT y1 = (SHORT)(AbsoluteTop() * (FLOAT)pWindow->nClientHeight);
	SHORT x2 = (SHORT)(AbsoluteWidth() * (FLOAT)pWindow->nClientWidth) + x1;
	SHORT y2 = (SHORT)(AbsoluteHeight() * (FLOAT)pWindow->nClientHeight) + y1;

	if ( _nX < x1 || _nX > x2 || _nY < y1 || _nY > y2 )
		return;

	pRender->pFocus = this;

	CALLBACK12* pTemp = mMouseUp->pHead;

	while ( pTemp )
	{
		LPMOUSEUPCALLBACK Callback = (LPMOUSEUPCALLBACK)pTemp->lpCallback;

		Callback( _nKeyContext, _nButtonContext, _nX, _nY, pTemp->lpData );

		pTemp = pTemp->pNext;
	}
}

VOID TEXTBOX12::OnMouseDown ( KEYCONTEXT _nKeyContext, BUTTONCONTEXT _nButtonContext, SHORT _nX, SHORT _nY )
{
	if ( bVisible == FALSE )
		return;

	SHORT x1 = (SHORT)(AbsoluteLeft() * (FLOAT)pWindow->nClientWidth);
	SHORT y1 = (SHORT)(AbsoluteTop() * (FLOAT)pWindow->nClientHeight);
	SHORT x2 = (SHORT)(AbsoluteWidth() * (FLOAT)pWindow->nClientWidth) + x1;
	SHORT y2 = (SHORT)(AbsoluteHeight() * (FLOAT)pWindow->nClientHeight) + y1;

	if ( _nX < x1 || _nX > x2 || _nY < y1 || _nY > y2 )
		return;

	pRender->pFocus = this;

	CALLBACK12* pTemp = mMouseDown->pHead;

	while ( pTemp )
	{
		LPMOUSEDOWNCALLBACK Callback = (LPMOUSEDOWNCALLBACK)pTemp->lpCallback;

		Callback( _nKeyContext, _nButtonContext, _nX, _nY, pTemp->lpData );

		pTemp = pTemp->pNext;
	}
}
