
#include "interface.h"
#include "render.h"
#include "indexer.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID INTERFACE12::AddChild ( INTERFACE12* _pChild )
{
	_pChild->SetParent( this );

	iChild->Add( _pChild );
}

VOID INTERFACE12::DelChild ( INTERFACE12* _pChild )
{
	_pChild->SetParent( NULL );

	iChild->Del( _pChild );
}



VOID INTERFACE12::AddControl ( CONTROL12* _pControl )
{
	_pControl->SetInterface( this );

	iControl->Add( _pControl );
}

VOID INTERFACE12::DelControl ( CONTROL12* _pControl )
{
	_pControl->SetInterface( NULL );

	iControl->Del( _pControl );
}



VOID INTERFACE12::SetLeft ( FLOAT _fLeft )
{
	fLeft = _fLeft;
}

VOID INTERFACE12::SetTop ( FLOAT _fTop )
{
	fTop = _fTop;
}



VOID INTERFACE12::SetWidth ( FLOAT _fWidth )
{
	fWidth = _fWidth;
}

VOID INTERFACE12::SetHeight ( FLOAT _fHeight )
{
	fHeight = _fHeight;
}



VOID INTERFACE12::Move ( FLOAT _x, FLOAT _y )
{
	fLeft += _x;
	fTop += _y;
}

VOID INTERFACE12::Grow ( FLOAT _x, FLOAT _y )
{
	fWidth *= _x;
	fHeight *= _y;
}

VOID INTERFACE12::Shrink ( FLOAT _x, FLOAT _y )
{
	if ( _x != 0.0f ) fWidth /= _x;
	if ( _y != 0.0f ) fHeight /= _y;
}



FLOAT INTERFACE12::AbsoluteLeft ( )
{
	if ( pParent )
		return fLeft * pParent->AbsoluteWidth() + pParent->AbsoluteLeft();
	else
		return fLeft;
}

FLOAT INTERFACE12::AbsoluteTop ( )
{
	if ( pParent )
		return fTop * pParent->AbsoluteHeight() + pParent->AbsoluteTop();
	else
		return fTop;
}



FLOAT INTERFACE12::AbsoluteWidth ( )
{
	if ( pParent )
		return fWidth * pParent->AbsoluteWidth();
	else
		return fWidth;
}

FLOAT INTERFACE12::AbsoluteHeight ( )
{
	if ( pParent )
		return fHeight * pParent->AbsoluteHeight();
	else
		return fHeight;
}
