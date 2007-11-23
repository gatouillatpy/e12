
#pragma once



#include "entity.h"

#include "util.h"



typedef void ( CALLBACK *LPMOVECALLBACK ) ( FLOAT _fX, FLOAT _fY ) ;
typedef void ( CALLBACK *LPBUTTONUPCALLBACK ) ( BYTE _nButton ) ;
typedef void ( CALLBACK *LPBUTTONDOWNCALLBACK ) ( BYTE _nButton ) ;
typedef void ( CALLBACK *LPWHEELUPCALLBACK ) ( FLOAT _fZ ) ;
typedef void ( CALLBACK *LPWHEELDOWNCALLBACK ) ( FLOAT _fZ ) ;



class DLL MOUSE12 : public ENTITY12
{

	friend class INPUT12;

private:
	
	DWORD dwBufferSize ;

	LPMOVECALLBACK lpMoveCallback ;
	LPBUTTONUPCALLBACK lpButtonUpCallback ;
	LPBUTTONDOWNCALLBACK lpButtonDownCallback ;
	LPWHEELUPCALLBACK lpWheelUpCallback ;
	LPWHEELDOWNCALLBACK lpWheelDownCallback ;

	SHORT nX, nY ;

public:

	MOUSE12 ( INPUT12* _pInput ) ;

	VOID SetMoveCallback ( LPMOVECALLBACK _lpCallback ) ;
	VOID SetButtonUpCallback ( LPBUTTONUPCALLBACK _lpCallback ) ;
	VOID SetButtonDownCallback ( LPBUTTONDOWNCALLBACK _lpCallback ) ;
	VOID SetWheelUpCallback ( LPWHEELUPCALLBACK _lpCallback ) ;
	VOID SetWheelDownCallback ( LPWHEELDOWNCALLBACK _lpCallback ) ;

	VOID OnMove ( FLOAT _fX, FLOAT _fY ) ;
	VOID OnButtonUp ( BYTE _nButton )   ;
	VOID OnButtonDown ( BYTE _nButton ) ;
	VOID OnWheelUp ( FLOAT _fZ ) ;
	VOID OnWheelDown ( FLOAT _fZ ) ;

	VOID Update ( LPDIRECTINPUTDEVICE8 _lpDIMouse, BOOLEAN _bButton[], FLOAT & _fX, FLOAT & _fY, FLOAT & _fZ ) ;

};