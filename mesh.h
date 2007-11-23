
#pragma once

#include "object.h"

#include "util.h"



CONST DWORD OBJECT_TYPE_MESH = 0x00000011 ;



class DLL MESH12 : public OBJECT12
{

private:

public:

	MESH12 ( RENDER12* _pRender ) ;

	virtual MESH12* Copy( BOOLEAN bCopyGeometry = FALSE, BOOLEAN bCopyTexture = FALSE ) ;

	BOOLEAN ImportX ( LPSTR _sFile ) ;
	BOOLEAN Import3DS ( LPSTR _sFile ) ;

};