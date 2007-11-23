
#pragma once

#include "entity.h"
#include "register.h"

#include "util.h"



typedef WORD KEYCONTEXT;

const KEYCONTEXT KC_NONE = 0x0000;
const KEYCONTEXT KC_SHIFT = 0x0001;
const KEYCONTEXT KC_CTRL = 0x0002;
const KEYCONTEXT KC_ALT = 0x0004;



typedef WORD BUTTONCONTEXT;

const BUTTONCONTEXT BC_NONE = 0x0000;
const BUTTONCONTEXT BC_LEFT = 0x0001;
const BUTTONCONTEXT BC_RIGHT = 0x0002;
const BUTTONCONTEXT BC_MIDDLE = 0x0004;



typedef WORD WINDOWCONTEXT;

const WINDOWCONTEXT WC_NORMAL = 0x0000;
const WINDOWCONTEXT WC_MAXIMIZED = 0x0001;
const WINDOWCONTEXT WC_MINIMIZED = 0x0002;



class DLL WINDOW12 : public ENTITY12
{

	typedef void ( CALLBACK *LPSHOWCALLBACK ) ( LPVOID _lpData ) ;
	typedef void ( CALLBACK *LPHIDECALLBACK ) ( LPVOID _lpData ) ;

	typedef void ( CALLBACK *LPCHARCALLBACK ) ( KEYCONTEXT _nKeyContext, BYTE _nCharCode, LPVOID _lpData ) ;

	typedef void ( CALLBACK *LPKEYUPCALLBACK ) ( KEYCONTEXT _nKeyContext, BYTE _nKeyCode, LPVOID _lpData ) ;
	typedef void ( CALLBACK *LPKEYDOWNCALLBACK ) ( KEYCONTEXT _nKeyContext, BYTE _nKeyCode, LPVOID _lpData ) ;

	typedef void ( CALLBACK *LPMOUSEMOVECALLBACK ) ( KEYCONTEXT _nKeyContext, BUTTONCONTEXT _nButtonContext, SHORT _nX, SHORT _nY, LPVOID _lpData ) ;
	typedef void ( CALLBACK *LPMOUSEUPCALLBACK ) ( KEYCONTEXT _nKeyContext, BUTTONCONTEXT _nButtonContext, SHORT _nX, SHORT _nY, LPVOID _lpData ) ;
	typedef void ( CALLBACK *LPMOUSEDOWNCALLBACK ) ( KEYCONTEXT _nKeyContext, BUTTONCONTEXT _nButtonContext, SHORT _nX, SHORT _nY, LPVOID _lpData ) ;

	typedef void ( CALLBACK *LPMAXIMIZECALLBACK ) ( LPVOID _lpData ) ;
	typedef void ( CALLBACK *LPMINIMIZECALLBACK ) ( LPVOID _lpData ) ;

	typedef void ( CALLBACK *LPRESIZECALLBACK ) ( SHORT _nWidth, SHORT _nHeight, LPVOID _lpData ) ;

	typedef void ( CALLBACK *LPCLOSECALLBACK ) ( LPVOID _lpData ) ;

	friend LRESULT WINAPI WindowProc ( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam ) ;
	friend DWORD WINAPI WindowThread( LPVOID lpParam ) ;

	friend class ENGINE12 ;

	friend class RENDER12 ;
	friend class INPUT12 ;

	friend class FONT12 ;

	friend class BUTTON12 ;
	friend class CONTROL12 ;
	friend class TEXTBOX12 ;

private:

	REGISTER12* mShow ;
	REGISTER12* mHide ;

	REGISTER12* mChar ;

	REGISTER12* mKeyUp ;
	REGISTER12* mKeyDown ;

	REGISTER12* mMouseMove ;
	REGISTER12* mMouseUp ;
	REGISTER12* mMouseDown ;

	REGISTER12* mMaximize ;
	REGISTER12* mMinimize ;

	REGISTER12* mResize ;

	REGISTER12* mClose ;

	SHORT nLeft ;
	SHORT nTop ;
	SHORT nWidth ;
	SHORT nHeight ;

	SHORT nClientWidth ;
	SHORT nClientHeight ;

	WINDOWCONTEXT wcState ;

	LPSTR sTitle ;

	HWND hWnd ;

	KEYCONTEXT kcState ;
	BUTTONCONTEXT bcState ;

	VOID OnKeyUp ( KEYCONTEXT _nKeyContext, BYTE _nKeyCode ) ;
	VOID OnKeyDown ( KEYCONTEXT _nKeyContext, BYTE _nKeyCode ) ;

	VOID OnChar ( KEYCONTEXT _nKeyContext, BYTE _nCharCode ) ;

	VOID OnMouseMove ( KEYCONTEXT _nKeyContext, BUTTONCONTEXT _nButtonContext, SHORT _nX, SHORT _nY ) ;
	VOID OnMouseUp ( KEYCONTEXT _nKeyContext, BUTTONCONTEXT _nButtonContext, SHORT _nX, SHORT _nY ) ;
	VOID OnMouseDown ( KEYCONTEXT _nKeyContext, BUTTONCONTEXT _nButtonContext, SHORT _nX, SHORT _nY ) ;

	VOID OnMaximize ( ) ;
	VOID OnMinimize ( ) ;

	VOID OnHide ( ) ;
	VOID OnShow ( ) ;

	VOID OnResize ( SHORT _nWidth, SHORT _nHeight ) ;

	VOID OnClose ( ) ;

	HANDLE* pThread ;

	BOOLEAN bEnabled ;

	BOOLEAN bVisible ;

public:

	WINDOW12 ( ENGINE12* _pEngine ) ;
	virtual ~WINDOW12 ( ) ;

	/* Crée la fenêtre en fonction des paramètres passés. */
	/* -> Ne peut être appelée qu'une seule fois.         */
	VOID Create ( ) ;
	VOID Create ( LPSTR _sName, LPSTR _sTitle, UINT _nLeft, UINT _nTop, UINT _nWidth, UINT _nHeight ) ;

	/* Detruit la fenêtre.                                         */
	/* -> Doit être appelée avant l'arrêt complet de l'exécutable. */
	VOID Destroy ( ) ;

	VOID WriteSettings ( LPSTR _sSection, LPSTR _sFile ) ;
	VOID ReadSettings ( LPSTR _sSection, LPSTR _sFile ) ;

	/* Renvoie le handle de la fenêtre. */
	HWND Handle ( ) ;

	SHORT Left ( ) ;
	SHORT Top ( ) ;
	SHORT Width ( ) ;
	SHORT Height ( ) ;

	SHORT X, Y ;
	SHORT Button ;

	SHORT ClientWidth ( ) ;
	SHORT ClientHeight ( ) ;

	WINDOWCONTEXT State ( ) ;

	BOOLEAN Visible ( ) ;

	VOID Show ( ) ;
	VOID Hide ( ) ;

	VOID Move ( SHORT _nLeft, SHORT _nTop ) ;
	VOID Size ( SHORT _nWidth, SHORT _nHeight ) ;

	LPSTR GetTitle ( ) ;
	VOID SetTitle ( LPSTR _sTitle ) ;

	/* Ajoute ou supprime une callback devant être appelée lorsqu'une touche du clavier est relachée. */
	VOID RegisterShowCallback ( LPSHOWCALLBACK _pCallback, LPVOID _pData = NULL ) ;
	VOID UnregisterShowCallback ( LPSHOWCALLBACK _pCallback ) ;

	/* Ajoute ou supprime une callback devant être appelée lorsqu'une touche du clavier est enfoncée. */
	VOID RegisterHideCallback ( LPHIDECALLBACK _pCallback, LPVOID _pData = NULL ) ;
	VOID UnregisterHideCallback ( LPHIDECALLBACK _pCallback ) ;

	/* Ajoute ou supprime une callback devant être appelée lorsqu'un caractère est transmis. */
	VOID RegisterCharCallback ( LPCHARCALLBACK _pCallback, LPVOID _pData = NULL ) ;
	VOID UnregisterCharCallback ( LPCHARCALLBACK _pCallback ) ;

	/* Ajoute ou supprime une callback devant être appelée lorsqu'une touche du clavier est relachée. */
	VOID RegisterKeyUpCallback ( LPKEYUPCALLBACK _pCallback, LPVOID _pData = NULL ) ;
	VOID UnregisterKeyUpCallback ( LPKEYUPCALLBACK _pCallback ) ;

	/* Ajoute ou supprime une callback devant être appelée lorsqu'une touche du clavier est enfoncée. */
	VOID RegisterKeyDownCallback ( LPKEYDOWNCALLBACK _pCallback, LPVOID _pData = NULL ) ;
	VOID UnregisterKeyDownCallback ( LPKEYDOWNCALLBACK _pCallback ) ;

	/* Ajoute ou supprime une callback devant être appelée lorsque la souris est en mouvement. */
	VOID RegisterMouseMoveCallback ( LPMOUSEMOVECALLBACK _pCallback, LPVOID _pData = NULL ) ;
	VOID UnregisterMouseMoveCallback ( LPMOUSEMOVECALLBACK _pCallback ) ;

	/* Ajoute ou supprime une callback devant être appelée lorsqu'un bouton de la souris est relaché. */
	VOID RegisterMouseUpCallback ( LPMOUSEUPCALLBACK _pCallback, LPVOID _pData = NULL ) ;
	VOID UnregisterMouseUpCallback ( LPMOUSEUPCALLBACK _pCallback ) ;

	/* Ajoute ou supprime une callback devant être appelée lorsqu'un bouton de la souris est enfoncé. */
	VOID RegisterMouseDownCallback ( LPMOUSEDOWNCALLBACK _pCallback, LPVOID _pData = NULL ) ;
	VOID UnregisterMouseDownCallback ( LPMOUSEDOWNCALLBACK _pCallback ) ;

	/* Ajoute ou supprime une callback devant être appelée lorsque la fenêtre est agrandie. */
	VOID RegisterMaximizeCallback ( LPMAXIMIZECALLBACK _pCallback, LPVOID _pData = NULL ) ;
	VOID UnregisterMaximizeCallback ( LPMAXIMIZECALLBACK _pCallback ) ;

	/* Ajoute ou supprime une callback devant être appelée lorsque la fenêtre est réduite. */
	VOID RegisterMinimizeCallback ( LPMINIMIZECALLBACK _pCallback, LPVOID _pData = NULL ) ;
	VOID UnregisterMinimizeCallback ( LPMINIMIZECALLBACK _pCallback ) ;

	/* Ajoute ou supprime une callback devant être appelée lorsque la fenêtre est redimensionnée. */
	VOID RegisterResizeCallback ( LPRESIZECALLBACK _pCallback, LPVOID _pData = NULL ) ;
	VOID UnregisterResizeCallback ( LPRESIZECALLBACK _pCallback ) ;

	/* Ajoute ou supprime une callback devant être appelée lorsque la fenêtre est fermée. */
	VOID RegisterCloseCallback ( LPCLOSECALLBACK _pCallback, LPVOID _pData = NULL ) ;
	VOID UnregisterCloseCallback ( LPCLOSECALLBACK _pCallback ) ;

	VOID ProcessCommand ( LPSTR sCommand ) ;
	VOID ProcessHelp ( ) ;

};

LRESULT WINAPI WindowProc ( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam ) ;

DWORD WINAPI WindowThread( LPVOID lpParam ) ;
