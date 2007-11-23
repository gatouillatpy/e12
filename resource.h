
#pragma once



#include "entity.h"

#include "util.h"



class DLL RESOURCE12
{

	friend class MANAGER12;
	friend class ENGINE12;

private:

	LPSTR sFile ;

	DWORD dwEntity ;
	ENTITY12** ppEntity ;

public:
	
	RESOURCE12 ( LPSTR _sFile ) ;
	~RESOURCE12 ( ) ;

	DWORD Count ( ) ;

	VOID AddEntity ( ENTITY12* _pEntity ) ;
	VOID DelEntity ( ENTITY12* _pEntity ) ;

	ENTITY12* Entity ( ) ;

	ENTITY12* operator[] ( DWORD k ) ;

	LPSTR File ( ) ;

};
