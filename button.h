
#pragma once

#include "label.h"
#include "register.h"

#include "util.h"



class DLL BUTTON12 : public LABEL12
{

protected:

	typedef void ( CALLBACK *LPCLICKCALLBACK ) ( LPVOID _lpData ) ;

	enum STATE : DWORD
	{
		STATE_UP	= 1,
		STATE_DOWN	= 2,
		STATE_TEMP	= 3,
	};

	REGISTER12* mClick ;

	STATE tState ;

	virtual VOID OnClick ( ) ;

	virtual VOID OnMouseMove ( KEYCONTEXT _nKeyContext, BUTTONCONTEXT _nButtonContext, SHORT _nX, SHORT _nY ) ;
	virtual VOID OnMouseUp ( KEYCONTEXT _nKeyContext, BUTTONCONTEXT _nButtonContext, SHORT _nX, SHORT _nY ) ;
	virtual VOID OnMouseDown ( KEYCONTEXT _nKeyContext, BUTTONCONTEXT _nButtonContext, SHORT _nX, SHORT _nY ) ;

public:

	BUTTON12 ( RENDER12* _pRender ) ;
	virtual ~BUTTON12 ( ) ;

	virtual VOID Render ( ) ;

	/* Ajoute ou supprime une callback devant être appelée lorsqu'on clique sur le bouton. */
	VOID RegisterClickCallback ( LPCLICKCALLBACK _pCallback, LPVOID _pData = NULL ) ;
	VOID UnregisterClickCallback ( LPCLICKCALLBACK _pCallback ) ;

};