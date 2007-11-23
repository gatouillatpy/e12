
#pragma once

#include "object.h"

#include "util.h"



class DLL SPRITE12 : public OBJECT12
{

private:
	
	DWORD dwFlags ;

public:

	SPRITE12 ( DWORD _dwIndex, RENDER12* _pRender ) ;

	virtual SPRITE12* Copy ( DWORD _dwIndex, BOOLEAN bCopyGeometry = FALSE, BOOLEAN bCopyTexture = FALSE ) ;

	HRESULT Render ( CAMERA12* _pCamera ) ;

	VOID Release ( ) ;

};