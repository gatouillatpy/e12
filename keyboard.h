
#pragma once



#include "entity.h"

#include "util.h"



typedef void ( CALLBACK *LPKEYUPCALLBACK ) ( DWORD _nKey ) ;
typedef void ( CALLBACK *LPKEYDOWNCALLBACK ) ( DWORD _nKey ) ;
typedef void ( CALLBACK *LPKEYPRESSCALLBACK ) ( DWORD _nKey ) ;



class DLL KEYBOARD12 : public ENTITY12
{

	friend class INPUT12;

private:

	DWORD dwBufferSize ;

	LPKEYUPCALLBACK	   lpKeyUpCallback	  ;
	LPKEYDOWNCALLBACK  lpKeyDownCallback  ;
	LPKEYPRESSCALLBACK lpKeyPressCallback ;

public:

	KEYBOARD12 ( INPUT12* _pInput ) ;

	VOID SetKeyUpCallback ( LPKEYUPCALLBACK _lpCallback )	    ;
	VOID SetKeyDownCallback ( LPKEYDOWNCALLBACK _lpCallback )   ;
	VOID SetKeyPressCallback ( LPKEYPRESSCALLBACK _lpCallback ) ;

	VOID OnKeyUp ( DWORD _nKey ) ;
	VOID OnKeyDown ( DWORD _nKey ) ;
	VOID OnKeyPress ( DWORD _nKey ) ;

	VOID Update ( LPDIRECTINPUTDEVICE8 _lpDIKeyboard, BOOLEAN _bKey[] ) ;

};