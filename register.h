
#pragma once



#include "util.h"



struct CALLBACK12
{
	LPVOID lpCallback ;
	LPVOID lpData ;

	CALLBACK12* pPrev ;
	CALLBACK12* pNext ;
};



class DLL REGISTER12
{

	friend class LOG12 ;
	friend class TIMER12 ;
	friend class WINDOW12 ;
	friend class BUTTON12 ;
	friend class CONTROL12 ;
	friend class TEXTBOX12 ;
	friend class CMDBOX12 ;

private:

	CALLBACK12* pHead ;
	CALLBACK12* pQueue ;

public:

	REGISTER12 ( ) ;
	~REGISTER12 ( ) ;

	VOID AddCallback ( LPVOID _pCallback, LPVOID _pData ) ;
	VOID DelCallback ( LPVOID _pCallback ) ;

};
