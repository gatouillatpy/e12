
#include "texture.h"
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID TEXTURE12::SetCenter ( FLOAT _u, FLOAT _v )
{
	vCenter = D3DXVECTOR2(_u, _v);

	bMatrix = FALSE;
}

VOID TEXTURE12::SetCenter ( D3DXVECTOR2 & _vCenter )
{
	vCenter = _vCenter;

	bMatrix = FALSE;
}

_inline D3DXVECTOR2 TEXTURE12::GetCenter ( )
{
	return vCenter;
}



VOID TEXTURE12::SetOffset ( FLOAT _u, FLOAT _v )
{
	vOffset = D3DXVECTOR2(_u, _v);

	bMatrix = FALSE;
}

VOID TEXTURE12::SetOffset ( D3DXVECTOR2 & _vOffset )
{
	vOffset = _vOffset;

	bMatrix = FALSE;
}

_inline D3DXVECTOR2 TEXTURE12::GetOffset ( )
{
	return vOffset;
}



VOID TEXTURE12::SetAngle ( FLOAT _alpha )
{
	fAngle = _alpha;

	bMatrix = FALSE;
}

_inline FLOAT TEXTURE12::GetAngle ( )
{
	return fAngle;
}



VOID TEXTURE12::SetZoom ( FLOAT _du, FLOAT _dv )
{
	vZoom = D3DXVECTOR2(_du, _dv);

	bMatrix = FALSE;
}

VOID TEXTURE12::SetZoom ( D3DXVECTOR2 & _vZoom )
{
	vZoom = _vZoom;

	bMatrix = FALSE;
}

_inline D3DXVECTOR2 TEXTURE12::GetZoom ( )
{
	return vZoom;
}



VOID TEXTURE12::Move ( FLOAT _u, FLOAT _v )
{
	vOffset.x += _u;
	vOffset.y += _v;

	bMatrix = FALSE;
}

VOID TEXTURE12::Rotate ( FLOAT _alpha )
{
	fAngle += _alpha;

	bMatrix = FALSE;
}

VOID TEXTURE12::Grow ( FLOAT _du, FLOAT _dv )
{
	vZoom.x *= _du;
	vZoom.y *= _dv;

	bMatrix = FALSE;
}

VOID TEXTURE12::Shrink ( FLOAT _du, FLOAT _dv )
{
	if ( _du != 0.0f ) vZoom.x /= _du;
	if ( _dv != 0.0f ) vZoom.y /= _dv;

	bMatrix = FALSE;
}



_inline FLOAT TEXTURE12::du ( )
{ 
	return vZoom.x;
}

_inline FLOAT TEXTURE12::dv ( )
{
	return vZoom.y;
}

_inline FLOAT TEXTURE12::alpha ( )
{
	return fAngle;
}

_inline FLOAT TEXTURE12::u ( )
{
	return vOffset.x;
}

_inline FLOAT TEXTURE12::v ( )
{
	return vOffset.y;
}

_inline FLOAT TEXTURE12::cu ( )
{
	return vCenter.x;
}

_inline FLOAT TEXTURE12::cv ( )
{
	return vCenter.y;
}
