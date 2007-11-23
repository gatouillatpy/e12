
#include "image.h"
#include "interface.h"
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID IMAGE12::SetTexture ( TEXTURE12* _pTexture )
{
	pTexture = _pTexture;
}

TEXTURE12* IMAGE12::GetTexture ( )
{
	return pTexture;
}



VOID IMAGE12::SetOffsetU ( FLOAT _fOffsetU )
{
	fOffsetU = _fOffsetU;
}

FLOAT IMAGE12::GetOffsetU ( )
{
	return fOffsetU;
}

VOID IMAGE12::SetOffsetV ( FLOAT _fOffsetV )
{
	fOffsetV = _fOffsetV;
}

FLOAT IMAGE12::GetOffsetV ( )
{
	return fOffsetV;
}



VOID IMAGE12::SetFactorU ( FLOAT _fFactorU )
{
	fFactorU = _fFactorU;
}

FLOAT IMAGE12::GetFactorU ( )
{
	return fFactorU;
}

VOID IMAGE12::SetFactorV ( FLOAT _fFactorV )
{
	fFactorV = _fFactorV;
}

FLOAT IMAGE12::GetFactorV ( )
{
	return fFactorV;
}
