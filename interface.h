
#pragma once

#include "window.h"
#include "control.h"
#include "image.h"
#include "label.h"
#include "alabel.h"
#include "textbox.h"
#include "cmdbox.h"
#include "frame.h"
#include "cursor.h"

#include "util.h"



class DLL INTERFACE12 : public ENTITY12
{

	friend class RENDER12;
	friend class IMAGE12;
	friend class LABEL12;
	friend class CURSOR12;
	friend class BUTTON12;
	friend class CONTROL12;

protected:

	RENDER12* pRender ;

	CURSOR12* pCursor ;

	INDEXER12* iChild ;

	INTERFACE12* pParent ;

	INDEXER12* iControl ;

	FLOAT fLeft ;
	FLOAT fTop ;

	FLOAT fWidth ;
	FLOAT fHeight ;

	BOOLEAN bVisible ;

	FLOAT AbsoluteLeft ( ) ;
	FLOAT AbsoluteTop ( ) ;

	FLOAT AbsoluteWidth ( ) ;
	FLOAT AbsoluteHeight ( ) ;

public:

	INTERFACE12 ( RENDER12* _pRender ) ;
	virtual ~INTERFACE12 ( ) ;

	VOID Show ( ) { bVisible = TRUE; } ;
	VOID Hide ( ) { bVisible = FALSE; } ;

	VOID AddChild ( INTERFACE12* _pChild ) ;
	VOID DelChild ( INTERFACE12* _pChild ) ;

	VOID SetParent ( INTERFACE12* _pParent ) { pParent = _pParent; } ;
	INTERFACE12* GetParent ( ) { return pParent; } ;

	VOID SetCursor ( CURSOR12* _pCursor ) { pCursor = _pCursor; } ;
	CURSOR12* GetCursor ( ) { return pCursor; } ;

	VOID AddControl ( CONTROL12* _pControl ) ;
	VOID DelControl ( CONTROL12* _pControl ) ;

	VOID Move ( FLOAT _x, FLOAT _y ) ;
	VOID Rotate ( FLOAT _z ) ;
	VOID Grow ( FLOAT _x, FLOAT _y ) ;
	VOID Shrink ( FLOAT _x, FLOAT _y ) ;

	VOID SetLeft ( FLOAT _fLeft ) ;
	FLOAT GetLeft ( ) { return fLeft; } ;
	VOID SetTop ( FLOAT _fTop ) ;
	FLOAT GetTop ( ) { return fTop; } ;

	VOID SetWidth ( FLOAT _fWidth ) ;
	FLOAT GetWidth ( ) { return fWidth; } ;
	VOID SetHeight ( FLOAT _fHeight ) ;
	FLOAT GetHeight ( ) { return fHeight; } ;

	FLOAT left ( ) { return fLeft; } ;
	FLOAT top ( ) { return fTop; } ;

	FLOAT width ( ) { return fWidth; } ;
	FLOAT height ( ) { return fHeight; } ;

	virtual VOID ProcessCommand ( LPSTR sCommand ) ;
	virtual VOID ProcessHelp ( ) ;

	virtual VOID Update ( ) ;
	virtual VOID Render ( ) ;

};