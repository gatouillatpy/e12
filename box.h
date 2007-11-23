
#pragma once

#include "object.h"

#include "util.h"



class DLL BOX12 : public OBJECT12
{

private:

public:

	BOX12 ( RENDER12* _pRender ) ;

	virtual BOX12* Copy ( BOOLEAN bCopyGeometry = FALSE, BOOLEAN bCopyTexture = FALSE ) ;

	VOID Create ( FLOAT _fWidth, FLOAT _fHeight, FLOAT _fLength, BOOLEAN bNormal = FALSE, BOOLEAN bUVMap = FALSE ) ;
	VOID Create ( FLOAT _fWidth, FLOAT _fHeight, FLOAT _fLength, DWORD _nDX, DWORD _nDY, DWORD _nDZ, BOOLEAN bNormal = FALSE, BOOLEAN bUVMap = FALSE ) ;

	virtual VOID ProcessCommand ( LPSTR sCommand ) ;
	virtual VOID ProcessHelp ( ) ;

};