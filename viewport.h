
#pragma once

#include "entity.h"

#include "util.h"



class DLL WINDOW12;
class DLL CAMERA12;



class DLL VIEWPORT12 : public ENTITY12
{

private:
	
	SHORT nLeft, nTop ;
	SHORT nWidth, nHeight ;

	WINDOW12* lpWindow ;

	CAMERA12* lpCamera ;

public:

	VIEWPORT12 ( WINDOW12* _lpWindow ) ;

};