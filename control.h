
#pragma once

#include "entity.h"
#include "window.h"

#include "util.h"



class DLL CONTROL12 : public ENTITY12
{

	friend class RENDER12;
	friend class INTERFACE12;

	friend class CONTROL12_EFFECT;

	friend VOID CALLBACK KeyUpCallback ( KEYCONTEXT _nKeyContext, BYTE _nKeyCode, LPVOID _lpData ) ;
	friend VOID CALLBACK KeyDownCallback ( KEYCONTEXT _nKeyContext, BYTE _nKeyCode, LPVOID _lpData ) ;

	friend VOID CALLBACK MouseMoveCallback ( KEYCONTEXT _nKeyContext, BUTTONCONTEXT _nButtonContext, SHORT _nX, SHORT _nY, LPVOID _lpData ) ;
	friend VOID CALLBACK MouseUpCallback ( KEYCONTEXT _nKeyContext, BUTTONCONTEXT _nButtonContext, SHORT _nX, SHORT _nY, LPVOID _lpData ) ;
	friend VOID CALLBACK MouseDownCallback ( KEYCONTEXT _nKeyContext, BUTTONCONTEXT _nButtonContext, SHORT _nX, SHORT _nY, LPVOID _lpData ) ;

protected:

	typedef void ( CALLBACK *LPKEYUPCALLBACK ) ( KEYCONTEXT _nKeyContext, BYTE _nKeyCode, LPVOID _lpData ) ;
	typedef void ( CALLBACK *LPKEYDOWNCALLBACK ) ( KEYCONTEXT _nKeyContext, BYTE _nKeyCode, LPVOID _lpData ) ;

	typedef void ( CALLBACK *LPMOUSEMOVECALLBACK ) ( KEYCONTEXT _nKeyContext, BUTTONCONTEXT _nButtonContext, SHORT _nX, SHORT _nY, LPVOID _lpData ) ;
	typedef void ( CALLBACK *LPMOUSEUPCALLBACK ) ( KEYCONTEXT _nKeyContext, BUTTONCONTEXT _nButtonContext, SHORT _nX, SHORT _nY, LPVOID _lpData ) ;
	typedef void ( CALLBACK *LPMOUSEDOWNCALLBACK ) ( KEYCONTEXT _nKeyContext, BUTTONCONTEXT _nButtonContext, SHORT _nX, SHORT _nY, LPVOID _lpData ) ;

	RENDER12* pRender ;

	WINDOW12* pWindow ;

	FLOAT fLeft ;
	FLOAT fTop ;

	FLOAT fWidth ;
	FLOAT fHeight ;

	FLOAT fAngle ;

	REGISTER12* mKeyUp ;
	REGISTER12* mKeyDown ;

	REGISTER12* mMouseMove ;
	REGISTER12* mMouseUp ;
	REGISTER12* mMouseDown ;

	INTERFACE12* pInterface ;

	BOOLEAN bVisible ;

	FLOAT AbsoluteLeft ( ) ;
	FLOAT AbsoluteTop ( ) ;

	FLOAT AbsoluteWidth ( ) ;
	FLOAT AbsoluteHeight ( ) ;

	FLOAT InterfaceWidth ( ) ;
	FLOAT InterfaceHeight ( ) ;

	CONTROL12_EFFECT* pEffect ;

	virtual VOID OnKeyUp ( KEYCONTEXT _nKeyContext, BYTE _nKeyCode ) ;
	virtual VOID OnKeyDown ( KEYCONTEXT _nKeyContext, BYTE _nKeyCode ) ;

	virtual VOID OnMouseMove ( KEYCONTEXT _nKeyContext, BUTTONCONTEXT _nButtonContext, SHORT _nX, SHORT _nY ) ;
	virtual VOID OnMouseUp ( KEYCONTEXT _nKeyContext, BUTTONCONTEXT _nButtonContext, SHORT _nX, SHORT _nY ) ;
	virtual VOID OnMouseDown ( KEYCONTEXT _nKeyContext, BUTTONCONTEXT _nButtonContext, SHORT _nX, SHORT _nY ) ;

public:

	CONTROL12 ( RENDER12* _pRender ) ;
	virtual ~CONTROL12 ( ) ;

	VOID ApplyEffect ( CONTROL12_EFFECT* _pEffect ) ;

	VOID SetInterface ( INTERFACE12* _pInterface ) ;
	INTERFACE12* GetInterface ( ) ;

	virtual VOID Show ( ) ;
	virtual VOID Hide ( ) ;

	VOID Move ( FLOAT _x, FLOAT _y ) ;
	VOID Rotate ( FLOAT _z ) ;
	VOID Grow ( FLOAT _x, FLOAT _y ) ;
	VOID Shrink ( FLOAT _x, FLOAT _y ) ;

	VOID SetLeft ( FLOAT _fLeft ) ;
	FLOAT GetLeft ( ) ;
	VOID SetTop ( FLOAT _fTop ) ;
	FLOAT GetTop ( ) ;
	VOID SetRight ( FLOAT _fRight ) ;
	FLOAT GetRight ( ) ;
	VOID SetBottom ( FLOAT _fBottom ) ;
	FLOAT GetBottom ( ) ;

	virtual VOID SetWidth ( FLOAT _fWidth ) ;
	virtual FLOAT GetWidth ( ) ;
	virtual VOID SetHeight ( FLOAT _fHeight ) ;
	virtual FLOAT GetHeight ( ) ;

	VOID SetAngle ( FLOAT _fAngle ) ;
	FLOAT GetAngle ( ) ;

	FLOAT left ( ) ;
	FLOAT top ( ) ;

	FLOAT width ( ) ;
	FLOAT height ( ) ;

	FLOAT angle ( ) ;

	/* Ajoute ou supprime une callback devant être appelée lorsqu'une touche du clavier est relachée et que le controle a le focus. */
	VOID RegisterKeyUpCallback ( LPKEYUPCALLBACK _pCallback, LPVOID _pData = NULL ) ;
	VOID UnregisterKeyUpCallback ( LPKEYUPCALLBACK _pCallback ) ;

	/* Ajoute ou supprime une callback devant être appelée lorsqu'une touche du clavier est enfoncée et que le controle a le focus. */
	VOID RegisterKeyDownCallback ( LPKEYDOWNCALLBACK _pCallback, LPVOID _pData = NULL ) ;
	VOID UnregisterKeyDownCallback ( LPKEYDOWNCALLBACK _pCallback ) ;

	/* Ajoute ou supprime une callback devant être appelée lorsque la souris est en mouvement sur le controle. */
	VOID RegisterMouseMoveCallback ( LPMOUSEMOVECALLBACK _pCallback, LPVOID _pData = NULL ) ;
	VOID UnregisterMouseMoveCallback ( LPMOUSEMOVECALLBACK _pCallback ) ;

	/* Ajoute ou supprime une callback devant être appelée lorsqu'un bouton de la souris est relaché sur le controle. */
	VOID RegisterMouseUpCallback ( LPMOUSEUPCALLBACK _pCallback, LPVOID _pData = NULL ) ;
	VOID UnregisterMouseUpCallback ( LPMOUSEUPCALLBACK _pCallback ) ;

	/* Ajoute ou supprime une callback devant être appelée lorsqu'un bouton de la souris est enfoncé sur le control. */
	VOID RegisterMouseDownCallback ( LPMOUSEDOWNCALLBACK _pCallback, LPVOID _pData = NULL ) ;
	VOID UnregisterMouseDownCallback ( LPMOUSEDOWNCALLBACK _pCallback ) ;

	virtual VOID ProcessCommand ( LPSTR sCommand ) ;
	virtual VOID ProcessHelp ( ) ;

	virtual VOID Update ( ) ;
	virtual VOID Render ( ) ;

};