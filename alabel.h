
#pragma once

#include "label.h"
#include "register.h"

#include "util.h"



class DLL ALABEL12 : public LABEL12
{

protected:

	struct CAPTION
	{
		FONT12* pFont;
		DWORD dwColor;
		FLOAT fSize;
		LPSTR sText;
	};

	DWORD nCaptionCount ;
	CAPTION** ppCaption ;

	virtual VOID RenderCaption ( ) ;

	virtual VOID AutoSize ( ) ;
	virtual VOID AutoWrap ( ) ;
	virtual VOID AutoOffset ( ) ;

public:

	ALABEL12 ( RENDER12* _pRender ) ;
	virtual ~ALABEL12 ( ) ;

	virtual VOID SetCaption ( LPSTR _sCaption ) ;
	virtual LPSTR GetCaption ( ) ;

	virtual VOID Render ( ) ;

};