
#pragma once

#include "frame.h"
#include "texture.h"

#include "util.h"



class DLL IMAGE12 : public FRAME12
{

private:

	TEXTURE12* pTexture ;

	FLOAT fOffsetU ;
	FLOAT fOffsetV ;

	FLOAT fFactorU ;
	FLOAT fFactorV ;

public:

	IMAGE12 ( RENDER12* _pRender ) ;

	VOID SetTexture ( TEXTURE12* _pTexture ) ;
	TEXTURE12* GetTexture ( ) ;

	VOID SetOffsetU ( FLOAT _fOffsetU ) ;
	FLOAT GetOffsetU ( ) ;
	VOID SetOffsetV ( FLOAT _fOffsetV ) ;
	FLOAT GetOffsetV ( ) ;

	VOID SetFactorU ( FLOAT _fFactorU ) ;
	FLOAT GetFactorU ( ) ;
	VOID SetFactorV ( FLOAT _fFactorV ) ;
	FLOAT GetFactorV ( ) ;

	virtual VOID Render ( ) ;

};