
#pragma once

#include "object.h"

#include "util.h"



VOID DLL UseSprite ( RENDER12* pRender ) ;



class DLL SPRITE12 : public OBJECT12
{

private:
	
	BOOLEAN bBillboard ;

public:

	SPRITE12 ( RENDER12* _pRender ) ;

	virtual SPRITE12* Copy ( BOOLEAN bCopyGeometry = FALSE, BOOLEAN bCopyTexture = FALSE ) ;

	VOID Render ( CAMERA12* _pCamera ) ;

};