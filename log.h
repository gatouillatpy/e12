
#pragma once

#include "util.h"

#include "register.h"



const CODE LOG_LEVEL_NULL = 0x00000000;
const CODE LOG_LEVEL_INFO = 0x10000000;
const CODE LOG_LEVEL_WARNING = 0x20000000;
const CODE LOG_LEVEL_ERROR = 0x30000000;
const CODE LOG_LEVEL_CRASH = 0x40000000;



class IMPULSE12 ;

class DLL LOG12
{

private:

	typedef void ( CALLBACK *LPIMPULSECALLBACK ) ( LPSTR _sFile, DWORD _dwLine, CODE _nLevel, CODE _nClass, CODE _nNumber, LPVOID _pClass, LPVOID _pData, LPSTR _pComment, LPVOID _pUserData ) ;
	typedef void ( CALLBACK *LPREPORTCALLBACK ) ( LPVOID _pUserData ) ;

	REGISTER12* mImpulse ;
	REGISTER12* mReport ;

	IMPULSE12* pStack ;

	DWORD dwCount ;

	LPSTR* pLine ;

	CODE nLevel ;
	
	virtual VOID OnImpulse ( LPSTR _sFile, DWORD _dwLine, CODE _nLevel, CODE _nClass, CODE _nNumber, LPVOID _pClass, LPVOID _pData, LPSTR _pComment ) ;
	virtual VOID OnReport ( ) ;

public:

	LOG12 ( ) ;
	~LOG12 ( ) ;

	LPSTR ReadLn ( DWORD dwLine ) ;

	VOID Write ( LPSTR sFormat, ... ) ;
	VOID WriteLn ( LPSTR sFormat, ... ) ;

	VOID Push ( LPSTR _sFile, DWORD _dwLine, CODE _nLevel, CODE _nClass, CODE _nNumber, LPVOID _pClass = NULL, LPVOID _pData = NULL, LPSTR _pComment = NULL ) ;
	IMPULSE12* Pop ( ) ;

	CODE Level ( ) ;

	VOID Clear ( ) ;

	VOID Report ( ) ;

	/* Ajoute ou supprime une callback devant être appelée lorsqu'un message est ajouté dans la pile. */
	VOID RegisterImpulseCallback ( LPIMPULSECALLBACK _pCallback, LPVOID _pUserData = NULL ) ;
	VOID UnregisterImpulseCallback ( LPIMPULSECALLBACK _pCallback ) ;

	/* Ajoute ou supprime une callback devant être appelée lorsqu'un rapport est demandé. */
	VOID RegisterReportCallback ( LPREPORTCALLBACK _pCallback, LPVOID _pUserData = NULL ) ;
	VOID UnregisterReportCallback ( LPREPORTCALLBACK _pCallback ) ;

};