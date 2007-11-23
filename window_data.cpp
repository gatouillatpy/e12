
#include "window.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



HWND WINDOW12::Handle ( )
{
	return hWnd;
}



SHORT WINDOW12::Left ( )
{
	return nLeft;
}

SHORT WINDOW12::Top ( )
{
	return nTop;
}

SHORT WINDOW12::Width ( )
{
	return nWidth;
}

SHORT WINDOW12::Height ( )
{
	return nHeight;
}



SHORT WINDOW12::ClientWidth ( )
{
	return nClientWidth;
}

SHORT WINDOW12::ClientHeight ( )
{
	return nClientHeight;
}



VOID WINDOW12::Move ( SHORT _nLeft, SHORT _nTop )
{
	nLeft = _nLeft;
	nTop = _nTop;

	MoveWindow( hWnd, nLeft, nTop, nWidth, nHeight, TRUE );
}

VOID WINDOW12::Size ( SHORT _nWidth, SHORT _nHeight )
{
	nWidth = _nWidth;
	nHeight = _nHeight;

	MoveWindow( hWnd, nLeft, nTop, nWidth, nHeight, TRUE );
}



VOID WINDOW12::SetTitle ( LPSTR _sTitle )
{
	DWORD dwLength = StringLength( _sTitle ) + 1;
	sTitle = new CHAR[dwLength];
	StringCopy( sTitle, dwLength, _sTitle );

	SetWindowText( hWnd, sTitle );
}

LPSTR WINDOW12::GetTitle ( )
{
	return sTitle;
}



WINDOWCONTEXT WINDOW12::State ( )
{
	return wcState;
}



BOOLEAN WINDOW12::Visible ( )
{
	return bVisible;
}



VOID WINDOW12::Show ( )
{
	if ( wcState == WC_NORMAL )
		ShowWindow( hWnd, SW_SHOWNORMAL );
	else if ( wcState == WC_MAXIMIZED )
		ShowWindow( hWnd, SW_SHOWMAXIMIZED );
	else if ( wcState == WC_MINIMIZED )
		ShowWindow( hWnd, SW_SHOWMINIMIZED );
}

VOID WINDOW12::Hide ( )
{
	ShowWindow( hWnd, SW_HIDE );
}