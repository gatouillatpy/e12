
#pragma once

#include "label.h"
#include "register.h"

#include "util.h"



class DLL TEXTBOX12 : public LABEL12
{

	friend VOID CALLBACK CharCallback ( KEYCONTEXT _nKeyContext, BYTE _nCharCode, LPVOID _lpData ) ;

protected:

	typedef void ( CALLBACK *LPCHARCALLBACK ) ( KEYCONTEXT _nKeyContext, BYTE _nCharCode, LPVOID _lpData ) ;

	typedef void ( CALLBACK *LPCHANGECALLBACK ) ( LPVOID _lpData ) ;

	LPSTR sText ;

	REGISTER12* mChange ;

	REGISTER12* mChar ;

	D3DXVECTOR4 vCursorColor ;

	BLENDSTATE12* pCursorBlendState ;

	VOID RenderCursor ( ) ;

	virtual VOID OnChange ( ) ;

	virtual VOID OnChar ( KEYCONTEXT _nKeyContext, BYTE _nCharCode ) ;

	virtual VOID OnKeyUp ( KEYCONTEXT _nKeyContext, BYTE _nKeyCode ) ;
	virtual VOID OnKeyDown ( KEYCONTEXT _nKeyContext, BYTE _nKeyCode ) ;

	virtual VOID OnMouseMove ( KEYCONTEXT _nKeyContext, BUTTONCONTEXT _nButtonContext, SHORT _nX, SHORT _nY ) ;
	virtual VOID OnMouseUp ( KEYCONTEXT _nKeyContext, BUTTONCONTEXT _nButtonContext, SHORT _nX, SHORT _nY ) ;
	virtual VOID OnMouseDown ( KEYCONTEXT _nKeyContext, BUTTONCONTEXT _nButtonContext, SHORT _nX, SHORT _nY ) ;

	DWORD nCursor ;

public:

	TEXTBOX12 ( RENDER12* _pRender ) ;
	virtual ~TEXTBOX12 ( ) ;

	virtual VOID Render ( ) ;

	/* Ajoute ou supprime une callback devant être appelée lorsqu'un caractère est transmis et que le controle a le focus. */
	VOID RegisterCharCallback ( LPCHARCALLBACK _pCallback, LPVOID _pData = NULL ) ;
	VOID UnregisterCharCallback ( LPCHARCALLBACK _pCallback ) ;

	/* Ajoute ou supprime une callback devant être appelée lorsque le texte du controle est modifié. */
	VOID RegisterChangeCallback ( LPCHANGECALLBACK _pCallback, LPVOID _pData = NULL ) ;
	VOID UnregisterChangeCallback ( LPCHANGECALLBACK _pCallback ) ;

	VOID SetCaption ( LPSTR _sCaption ) ;
	LPSTR GetCaption ( ) ;

	VOID SetText ( LPSTR _sText ) ;
	LPSTR GetText ( ) ;

	D3DXVECTOR4 GetCursorColor ( ) ;
	VOID SetCursorColor ( D3DXVECTOR4 & _vColor ) ;
	VOID SetCursorColor ( DWORD _dwColor ) ;
	VOID SetCursorColor ( FLOAT _r, FLOAT _g, FLOAT _b, FLOAT _a ) ;

	VOID SetCursorBlendState ( BLENDSTATE12* _pCursorBlendState ) ;
	BLENDSTATE12* GetCursorBlendState ( ) ;

};