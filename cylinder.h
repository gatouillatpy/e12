
#pragma once

#include "object.h"

#include "util.h"



VOID DLL UseCylinder ( RENDER12* pRender ) ;



class DLL CYLINDER12 : public OBJECT12
{

private:

	FLOAT fRadius ;
	FLOAT fHeight ;

	BOOLEAN bRaytrace ;

public:

	CYLINDER12 ( RENDER12* _pRender ) ;

	virtual CYLINDER12* Copy( BOOLEAN bCopyGeometry = FALSE, BOOLEAN bCopyTexture = FALSE ) ;

	VOID Create ( FLOAT _fRadius, FLOAT _fHeight ) ;
	VOID Create ( FLOAT _fRadius, FLOAT _fHeight, DWORD _nDR, DWORD _nDH ) ;

	VOID Render ( CAMERA12* _pCamera ) ;
	VOID Raytrace ( CAMERA12* _pCamera ) ;

};