
#pragma once

#include "texture.h"

#include "util.h"



class DLL VOLUME12 : public TEXTURE12
{

private:

public:

	VOLUME12 ( RENDER12* _pRender ) ;

	VOLUME12* Copy ( BOOLEAN bCopyPixelData = FALSE ) ;

	BOOLEAN Import ( LPSTR _sFile ) ;
	BOOLEAN Import ( DWORD _dwFileCount, ... ) ;
	BOOLEAN ImportLevel ( DWORD _dwLevel, LPSTR _sFile ) ;

	BOOLEAN Load ( LPSTR _sFile ) ;

};