
#include "window.h"
#include "engine.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



LRESULT WINAPI WindowProc ( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    WINDOW12* pWindow = (WINDOW12*)GetWindowLong( hWnd, GWL_USERDATA );

	if ( pWindow == NULL )
		return DefWindowProc( hWnd, msg, wParam, lParam );

	RECT tRect;

	switch( msg )
	{
		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_MBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_RBUTTONUP:
		case WM_MBUTTONUP:
		case WM_MOUSEMOVE:
		{
			pWindow->X = (UINT)LOWORD(lParam);
			pWindow->Y = (UINT)HIWORD(lParam);

			if ( GetAsyncKeyState(VK_SHIFT) & 0x8000 ) pWindow->kcState |= KC_SHIFT; else pWindow->kcState ^= KC_SHIFT;
			if ( GetAsyncKeyState(VK_CONTROL) & 0x8000 ) pWindow->kcState |= KC_CTRL; else pWindow->kcState ^= KC_CTRL;
			if ( GetAsyncKeyState(VK_MENU) & 0x8000 ) pWindow->kcState |= KC_ALT; else pWindow->kcState ^= KC_ALT;
		}
	}

	switch( msg )
    {
		case WM_LBUTTONDOWN:
			pWindow->bcState |= BC_LEFT;
			break;
		case WM_RBUTTONDOWN:
			pWindow->bcState |= BC_RIGHT;
			break;
		case WM_MBUTTONDOWN:
			pWindow->bcState |= BC_MIDDLE;
			break;
    }

	switch( msg )
    {
		case WM_SHOWWINDOW:
			{
				pWindow->bVisible = (BOOLEAN)wParam;
				if ( pWindow->bVisible == TRUE )
					pWindow->OnShow();
				else
					pWindow->OnHide();
			}
			break;
		case WM_KEYUP:
			pWindow->OnKeyUp( pWindow->kcState, wParam );
			break;
		case WM_KEYDOWN:
			pWindow->OnKeyDown( pWindow->kcState, wParam );
			break;
		case WM_CHAR:
			pWindow->OnChar( pWindow->kcState, wParam );
			break;
		case WM_SIZE:
			{
				GetWindowRect( pWindow->hWnd, &tRect );
				pWindow->nWidth = (SHORT)(tRect.right - tRect.left);
				pWindow->nHeight = (SHORT)(tRect.bottom - tRect.top);

				GetClientRect( hWnd, &tRect );
				pWindow->nClientWidth = (SHORT)(tRect.right - tRect.left);
				pWindow->nClientHeight = (SHORT)(tRect.bottom - tRect.top);

				if ( IsZoomed( pWindow->hWnd ) )
					pWindow->OnMaximize();
				else if ( IsIconic( pWindow->hWnd ) )
					pWindow->OnMinimize();
				else
					pWindow->OnResize( pWindow->nWidth, pWindow->nHeight );
			}
			break;
		case WM_DESTROY:
			pWindow->bEnabled = FALSE;
			pWindow->OnClose();
			break;
		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_MBUTTONDOWN:
			pWindow->OnMouseDown( pWindow->kcState, pWindow->bcState, pWindow->X, pWindow->Y );
			break;
		case WM_LBUTTONUP:
		case WM_RBUTTONUP:
		case WM_MBUTTONUP:
			pWindow->OnMouseUp( pWindow->kcState, pWindow->bcState, pWindow->X, pWindow->Y );
			break;
		case WM_MOUSEMOVE:
			pWindow->OnMouseMove( pWindow->kcState, pWindow->bcState, pWindow->X, pWindow->Y );
			break;
    }

	switch( msg )
    {
		case WM_LBUTTONUP:
			pWindow->bcState ^= BC_LEFT;
			break;
		case WM_RBUTTONUP:
			pWindow->bcState ^= BC_RIGHT;
			break;
		case WM_MBUTTONUP:
			pWindow->bcState ^= BC_MIDDLE;
			break;
    }

	pWindow->Button = pWindow->bcState;

	return DefWindowProc( hWnd, msg, wParam, lParam );
}
