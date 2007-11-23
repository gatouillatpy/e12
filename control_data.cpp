
#include "control.h"
#include "interface.h"
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID CONTROL12::Show ( )
{
	bVisible = TRUE;
}

VOID CONTROL12::Hide ( )
{
	bVisible = FALSE;
}



VOID CONTROL12::SetInterface ( INTERFACE12* _pInterface )
{
	pInterface = _pInterface;
}

INTERFACE12* CONTROL12::GetInterface ( )
{
	return pInterface;
}



VOID CONTROL12::SetLeft ( FLOAT _fLeft )
{
	fLeft = _fLeft;
}

FLOAT CONTROL12::GetLeft ( )
{
	return fLeft;
}

VOID CONTROL12::SetTop ( FLOAT _fTop )
{
	fTop = _fTop;
}

FLOAT CONTROL12::GetTop ( )
{
	return fTop;
}

VOID CONTROL12::SetRight ( FLOAT _fRight )
{
	fLeft = 1.0f - fWidth - _fRight;
}

FLOAT CONTROL12::GetRight ( )
{
	return 1.0f - fWidth - fLeft;
}

VOID CONTROL12::SetBottom ( FLOAT _fBottom )
{
	fTop = 1.0f - fHeight - _fBottom;
}

FLOAT CONTROL12::GetBottom ( )
{
	return 1.0f - fHeight - fTop;
}



VOID CONTROL12::SetWidth ( FLOAT _fWidth )
{
	fWidth = _fWidth;
}

FLOAT CONTROL12::GetWidth ( )
{
	return fWidth;
}

VOID CONTROL12::SetHeight ( FLOAT _fHeight )
{
	fHeight = _fHeight;
}

FLOAT CONTROL12::GetHeight ( )
{
	return fHeight;
}



VOID CONTROL12::SetAngle ( FLOAT _fAngle )
{
	fAngle = _fAngle;
}

FLOAT CONTROL12::GetAngle ( )
{
	return fAngle;
}



VOID CONTROL12::Move ( FLOAT _x, FLOAT _y )
{
	fLeft += _x;
	fTop += _y;
}

VOID CONTROL12::Rotate ( FLOAT _z )
{
	fAngle += _z;
}

VOID CONTROL12::Grow ( FLOAT _x, FLOAT _y )
{
	fWidth *= _x;
	fHeight *= _y;
}

VOID CONTROL12::Shrink ( FLOAT _x, FLOAT _y )
{
	if ( _x != 0.0f ) fWidth /= _x;
	if ( _y != 0.0f ) fHeight /= _y;
}



FLOAT CONTROL12::AbsoluteLeft ( )
{
	if ( pInterface )
		return fLeft * pInterface->AbsoluteWidth() + pInterface->AbsoluteLeft();
	else
		return fLeft;
}

FLOAT CONTROL12::AbsoluteTop ( )
{
	if ( pInterface )
		return fTop * pInterface->AbsoluteHeight() + pInterface->AbsoluteTop();
	else
		return fTop;
}



FLOAT CONTROL12::AbsoluteWidth ( )
{
	if ( pInterface )
		return fWidth * pInterface->AbsoluteWidth();
	else
		return fWidth;
}

FLOAT CONTROL12::AbsoluteHeight ( )
{
	if ( pInterface )
		return fHeight * pInterface->AbsoluteHeight();
	else
		return fHeight;
}



FLOAT CONTROL12::InterfaceWidth ( )
{
	if ( pInterface )
		return pInterface->AbsoluteWidth();
	else
		return 1.0f;
}

FLOAT CONTROL12::InterfaceHeight ( )
{
	if ( pInterface )
		return pInterface->AbsoluteHeight();
	else
		return 1.0f;
}



FLOAT CONTROL12::left ( )
{
	return fLeft;
}

FLOAT CONTROL12::top ( )
{
	return fTop;
}



FLOAT CONTROL12::width ( )
{
	return fWidth;
}

FLOAT CONTROL12::height ( )
{
	return fHeight;
}



FLOAT CONTROL12::angle ( )
{
	return fAngle;
}
