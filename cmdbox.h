
#pragma once

#include "textbox.h"

#include "util.h"



class DLL CMDBOX12 : public TEXTBOX12
{

protected:

	ENGINE12* pEngine ;

	virtual VOID OnChar ( KEYCONTEXT _nKeyContext, BYTE _nCharCode ) ;

public:

	CMDBOX12 ( RENDER12* _pRender ) ;

};