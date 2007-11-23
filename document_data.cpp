
#include "document.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID DOCUMENT12::Level ( BYTE* & _pData )
{
	if ( pParent )
	{
		*_pData++ = ' ';
		*_pData++ = ' ';
		*_pData++ = ' ';
		*_pData++ = ' ';

		pParent->Level( _pData );
	}
}



BOOLEAN DOCUMENT12::IsExtended ( )
{
	if ( ppChild )
	{
		for ( DWORD k = 0 ; k < dwChildCount ; k++ )
			if ( ppChild[k]->ppChild )
				return TRUE;
	}

	return FALSE;
}



LPSTR DOCUMENT12::GetDir ( )
{
	if ( sPath )
		return StringDir( sPath );
	else if ( pParent )
		return pParent->GetDir();
	else
		return "";
}



LPSTR DOCUMENT12::GetClass ( )
{
	return sClass;
}

VOID DOCUMENT12::SetClass ( LPSTR _sClass )
{
	if ( sClass )
		delete [] sClass;

	if ( _sClass != NULL )
	{
		DWORD dwLength = StringLength( _sClass ) + 1;

		sClass = new CHAR[dwLength];

		StringCopy( sClass, dwLength, _sClass );
	}
	else
	{
		sClass = NULL;
	}
}



LPSTR DOCUMENT12::GetPath ( )
{
	return sPath;
}

VOID DOCUMENT12::SetPath ( LPSTR _sPath )
{
	if ( sPath )
		delete [] sPath;

	if ( _sPath != NULL )
	{
		DWORD dwLength = StringLength( _sPath ) + 1;

		sPath = new CHAR[dwLength];

		StringCopy( sPath, dwLength, _sPath );
	}
	else
	{
		sPath = NULL;
	}
}



LPSTR DOCUMENT12::GetName ( )
{
	return sName;
}

VOID DOCUMENT12::SetName ( LPSTR _sName )
{
	if ( sName )
		delete [] sName;

	if ( _sName != NULL )
	{
		DWORD dwLength = StringLength( _sName ) + 1;

		sName = new CHAR[dwLength];

		StringCopy( sName, dwLength, _sName );
	}
	else
	{
		sName = NULL;
	}
}



DWORD DOCUMENT12::GetIndex ( )
{
	return dwIndex;
}

VOID DOCUMENT12::SetIndex ( DWORD _dwIndex )
{
	dwIndex = _dwIndex;
}



INT64 DOCUMENT12::GetInteger ( )
{
	return nValue;
}

VOID DOCUMENT12::SetInteger ( INT64 _nValue )
{
	nValue = _nValue;

	dwType = TYPE_INTEGER;
}



DOUBLE DOCUMENT12::GetFloat ( )
{
	return fValue;
}

VOID DOCUMENT12::SetFloat ( DOUBLE _fValue )
{
	fValue = _fValue;

	dwType = TYPE_FLOAT;
}



LPSTR DOCUMENT12::GetString ( )
{
	return sValue;
}

VOID DOCUMENT12::SetString ( LPSTR _sValue )
{
	if ( sValue )
		delete [] sValue;

	if ( _sValue != NULL )
	{
		DWORD dwLength = StringLength( _sValue ) + 1;

		sValue = new CHAR[dwLength];

		StringCopy( sValue, dwLength, _sValue );

		dwType = TYPE_STRING;
	}
	else
	{
		sValue = NULL;

		dwType = TYPE_NONE;
	}
}
