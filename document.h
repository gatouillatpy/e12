
#pragma once



#include "util.h"



class DOCUMENT12
{

	friend class LOG12 ;

	static const DWORD TYPE_NONE = 0x0;
	static const DWORD TYPE_STRING = 0x1;
	static const DWORD TYPE_INTEGER = 0x2;
	static const DWORD TYPE_FLOAT = 0x3;

private:

	LOG12* pLog ;

	DOCUMENT12* pParent;

	DWORD dwChildCount;
	DOCUMENT12** ppChild;

	LPSTR sPath ;

	LPSTR sClass ;

	LPSTR sName ;
	DWORD dwIndex ;

	DWORD dwType ;

	LPSTR sValue ;
	INT64 nValue ;
	DOUBLE fValue ;

	VOID Level ( BYTE* & _pData ) ;
	
	BOOLEAN IsExtended ( ) ;

	LPSTR GetDir ( ) ;

public:

	DOCUMENT12 ( LOG12* _pLog ) ;
	DOCUMENT12 ( DOCUMENT12* _pParent ) ;
	~DOCUMENT12 ( ) ;

	VOID Parse ( BYTE* & _pData ) ;
	VOID Build ( BYTE* & _pData, BOOLEAN _bInline = FALSE ) ;

	BOOLEAN Load ( LPSTR _sPath ) ;
	BOOLEAN Save ( LPSTR _sPath ) ;

	VOID AddChild ( DOCUMENT12* _pDocument ) ;
	VOID DelChild ( DOCUMENT12* _pDocument ) ;

	DOCUMENT12* GetChild ( LPSTR _sClass ) ;
	DOCUMENT12* GetChild ( DWORD _nID ) ;

	LPSTR GetClass ( ) ;
	VOID SetClass ( LPSTR _sClass ) ;

	LPSTR GetPath ( ) ;
	VOID SetPath ( LPSTR _sPath ) ;

	LPSTR GetName ( ) ;
	VOID SetName ( LPSTR _sName ) ;

	DWORD GetIndex ( ) ;
	VOID SetIndex ( DWORD _dwIndex ) ;

	INT64 GetInteger ( ) ;
	VOID SetInteger ( INT64 _nValue ) ;

	DOUBLE GetFloat ( ) ;
	VOID SetFloat ( DOUBLE _fValue ) ;

	LPSTR GetString ( ) ;
	VOID SetString ( LPSTR _sValue ) ;

};