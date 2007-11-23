
#include "document.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID DOCUMENT12::Build ( BYTE* & _pData, BOOLEAN _bInline )
{
	if ( sPath != NULL )
	{
		Level( _pData );

		if ( sClass != NULL )
		{
			*_pData++ = ':';

			CHAR* pClass = sClass;
			while ( *pClass )
				*_pData++ = *pClass++;

			*_pData++ = ' ';
		}

		*_pData++ = '@';

		CHAR* pPath = sPath;
		while ( *pPath )
			*_pData++ = *pPath++;

		*_pData++ = 0xD;
		*_pData++ = 0xA;
	}
	else if ( ppChild )
	{
		Level( _pData );

		if ( sClass != NULL )
		{
			*_pData++ = ':';

			CHAR* pClass = sClass;
			while ( *pClass )
				*_pData++ = *pClass++;

			*_pData++ = ' ';
		}

		if ( sName != NULL )
		{
			*_pData++ = '$';

			CHAR* pName = sName;
			while ( *pName )
				*_pData++ = *pName++;

			*_pData++ = ' ';
		}

		if ( dwIndex != -1 )
		{
			CHAR sIndex[12];
			StringPrint( sIndex, 12, "%d", dwIndex );

			*_pData++ = '#';

			CHAR* pIndex = sIndex;
			while ( *pIndex )
				*_pData++ = *pIndex++;

			*_pData++ = ' ';
		}

		if ( IsExtended() )
		{
			*_pData++ = 0xD;
			*_pData++ = 0xA;

			Level( _pData );

			*_pData++ = '{';

			*_pData++ = 0xD;
			*_pData++ = 0xA;

			for ( DWORD k = 0 ; k < dwChildCount ; k++ )
				if ( ppChild[k] )
					ppChild[k]->Build( _pData );

			Level( _pData );

			*_pData++ = '}';

			*_pData++ = 0xD;
			*_pData++ = 0xA;
		}
		else
		{
			*_pData++ = '{';

			*_pData++ = ' ';

			for ( DWORD k = 0 ; k < dwChildCount ; k++ )
				if ( ppChild[k] )
					ppChild[k]->Build( _pData, TRUE );

			*_pData++ = '}';

			*_pData++ = 0xD;
			*_pData++ = 0xA;
		}
	}
	else if ( dwType != TYPE_NONE )
	{
		if ( _bInline == FALSE ) Level( _pData );

		if ( sClass != NULL )
		{
			CHAR* pClass = sClass;
			while ( *pClass )
				*_pData++ = *pClass++;

			*_pData++ = ' ';

			*_pData++ = '=';

			*_pData++ = ' ';
		}

		if ( dwType == TYPE_STRING )
		{
			*_pData++ = '"';

			CHAR* pValue = sValue;
			while ( *pValue )
				*_pData++ = *pValue++;

			*_pData++ = '"';

			*_pData++ = ';';
		}
		else if ( dwType == TYPE_INTEGER )
		{
			CHAR sInteger[32];
			StringPrint( sInteger, 32, "%d", nValue );

			CHAR* pInteger = sInteger;
			while ( *pInteger )
				*_pData++ = *pInteger++;

			*_pData++ = ';';
		}
		else if ( dwType == TYPE_FLOAT )
		{
			CHAR sFloat[32];
			StringPrint( sFloat, 32, "%f", fValue );

			CHAR* pFloat = sFloat;
			while ( *pFloat )
				*_pData++ = *pFloat++;

			*_pData++ = ';';
		}

		if ( _bInline == TRUE )
		{
			*_pData++ = ' ';
		}
		else
		{
			*_pData++ = 0xD;
			*_pData++ = 0xA;
		}
	}
}
