
#pragma once

#include "object.h"

#include "util.h"



CONST DWORD OBJECT_TYPE_GRID = 0x00000101 ;



class DLL GRID12 : public OBJECT12
{

private:

public:

	GRID12 ( RENDER12* _pRender ) ;

	virtual GRID12* Copy( BOOLEAN bCopyGeometry = FALSE, BOOLEAN bCopyTexture = FALSE ) ;

	VOID Create ( FLOAT _fWidth, FLOAT _fHeight, WORD _nDX, WORD _nDY ) ;

};