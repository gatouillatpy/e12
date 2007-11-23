
#include "document.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID DOCUMENT12::Parse ( BYTE* & _pData )
{
	CHAR sBuffer[2048];

headloop:

	DWORD k = 0;

	while ( *_pData )
	{
		if ( *_pData == ';' )
			goto end;
		else if ( *_pData > 0x20 && *_pData < 0x7F )
			break;

		_pData++;
	}

	if ( *_pData == 0 )
	{
		return;
	}
	else if ( *_pData == ':' )
	{
		_pData++;

		while ( *_pData )
		{
			if ( IsCharAlphaNumeric(*_pData) || *_pData == '_' )
				sBuffer[k++] = *_pData++;
			else
				break;
		}

		sBuffer[k++] = 0;

		if ( sClass == NULL )
		{
			sClass = new CHAR[k];

			StringCopy( sClass, k, sBuffer );
		}
	}
	else if ( *_pData == '$' )
	{
		_pData++;

		while ( *_pData )
		{
			if ( IsCharAlphaNumeric(*_pData) || *_pData == '_' )
				sBuffer[k++] = *_pData++;
			else
				break;
		}

		sBuffer[k++] = 0;

		if ( sName )
			delete [] sName;

		sName = new CHAR[k];

		StringCopy( sName, k, sBuffer );
	}
	else if ( *_pData == '#' )
	{
		_pData++;

		while ( *_pData )
		{
			if ( _IsCharNumeric(*_pData) )
				sBuffer[k++] = *_pData++;
			else
				break;
		}

		sBuffer[k++] = 0;

		StringScan( sBuffer, "%d", &dwIndex );
	}
	else if ( *_pData == '@' )
	{
		_pData++;

		while ( *_pData )
		{
			if ( *_pData < 0x20 )
				break;
			else
				sBuffer[k++] = *_pData++;
		}

		sBuffer[k++] = 0;

		Load( sBuffer );

		return;
	}
	else if ( *_pData == '{' )
	{
		_pData++;

bodyloop:

		while ( *_pData )
		{
			if ( *_pData == '}' )
				goto end;
			else if ( *_pData > 0x20 && *_pData < 0x7F )
				break;

			_pData++;
		}

		DOCUMENT12* pChild = new DOCUMENT12( this );

		pChild->Parse( _pData );

		goto bodyloop;
	}
	else if ( *_pData == '"' )
	{
		dwType = TYPE_STRING;

		_pData++;

		while ( *_pData )
		{
			if ( *_pData != '"' )
				sBuffer[k++] = *_pData++;
			else
				break;
		}

		_pData++;

		sBuffer[k++] = 0;

		if ( sValue )
			delete [] sValue;

		sValue = new CHAR[k];

		StringCopy( sValue, k, sBuffer );
	}
	else if ( _IsCharNumeric(*_pData) || *_pData == '-' || *_pData == '+' )
	{
		dwType = TYPE_INTEGER;

		sBuffer[k++] = *_pData++;

		while ( *_pData )
		{
			if ( *_pData == '.' )
				dwType = TYPE_FLOAT;

			if ( _IsCharNumeric(*_pData) || *_pData == '.' )
				sBuffer[k++] = *_pData++;
			else
				break;
		}

		sBuffer[k++] = 0;

		StringScan( sBuffer, "%lg", &fValue );

		nValue = (INT64)fValue;
	}
	else if ( IsCharAlpha(*_pData) || *_pData == '_' )
	{
		sBuffer[k++] = *_pData++;

		while ( *_pData )
		{
			if ( IsCharAlphaNumeric(*_pData) || *_pData == '_' )
				sBuffer[k++] = *_pData++;
			else
				break;
		}

		sBuffer[k++] = 0;

		if ( sClass == NULL )
		{
			sClass = new CHAR[k];

			StringCopy( sClass, k, sBuffer );
		}
	}
	else
	{
		_pData++;
	}

	goto headloop;

end:

	_pData++;
}
