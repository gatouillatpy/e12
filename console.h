
#pragma once

#include "interface.h"

#include "util.h"



/************************************************************************/
/* TODO :                                                               */
/* - relayer les propriétés toutes les propriétés de LABEL12            */
/************************************************************************/



class DLL CONSOLE12 : public INTERFACE12
{

public:

	enum STYLE : DWORD
	{
		STYLE_WIN9X	= 1,
	};

private:

	friend VOID CALLBACK ImpulseCallback ( LPSTR _sFile, DWORD _dwLine, CODE _nLevel, CODE _nClass, CODE _nNumber, LPVOID _pClass, LPVOID _pData, LPSTR _pComment, LPVOID _pUserData ) ;
	
	friend VOID CALLBACK ReportCallback ( LPVOID _pUserData ) ;

	LOG12* pLog ;

	UINT nLineCount ;

	ALABEL12* pOutput ;

	CMDBOX12* pCommand ;

	FONT12* pFont ;

	STYLE tStyle ;

public:

	CONSOLE12 ( RENDER12* _pRender, UINT _nLineCount ) ;

	VOID SetStyle ( STYLE _tStyle ) ;
	STYLE GetStyle ( ) ;

	VOID SetFont ( FONT12* _pFont ) ;
	FONT12* GetFont ( ) ;

	VOID FadeIn ( ) ;
	VOID FadeOut ( ) ;

	ALABEL12* Output ( ) ;
	CMDBOX12* Command ( ) ;

};