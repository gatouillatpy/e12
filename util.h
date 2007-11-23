
#pragma once

#pragma warning (disable : 4251)



#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x400
#endif



#ifdef ENGINE_DLL
#define DLL __declspec(dllexport)
#else
#define DLL __declspec(dllimport)
#endif



#define DIRECTINPUT_VERSION  0x0800

//#define DEBUG_SHADER



#include <windows.h>

#include <d3dx9.h>
#include <dinput.h>
#include <dxerr.h>

#include <stdio.h>
#include <assert.h>



#define RANDOM rand() * rand()
#define IRANDOM(min, max) rand() % (max - min) + min
#define FRANDOM(min, max) (FLOAT)rand() / (FLOAT)RAND_MAX * (max - min) + min



typedef DWORD CODE;



#ifndef __STDC_WANT_SECURE_LIB__
#include <strsafe.h>
#define fopen_s(file, path, access) !(*file = fopen(path, access))
#endif //__STDC_WANT_SECURE_LIB__



static BOOLEAN CheckFile ( LPSTR _sFile )
{
	FILE* pFile;

	if ( fopen_s( &pFile, _sFile, "rb" ) )
		return 0;
	
	fclose( pFile );

	return 1;
}



inline static VOID StringCopy ( LPSTR sDestination, DWORD dwLimit, LPSTR sSource )
{
#ifdef __STDC_WANT_SECURE_LIB__
	strcpy_s( sDestination, dwLimit, sSource );
#else //__STDC_WANT_SECURE_LIB__
	StringCbCopy( sDestination, dwLimit, sSource );
#endif //__STDC_WANT_SECURE_LIB__
}

inline static VOID StringCopyN ( LPSTR sDestination, DWORD dwLimit, LPSTR sSource, DWORD dwLength )
{
#ifdef __STDC_WANT_SECURE_LIB__
	strncpy_s( sDestination, dwLimit, sSource, dwLength );
#else //__STDC_WANT_SECURE_LIB__
	StringCbCopyN( sDestination, dwLimit, sSource, dwLength );
#endif //__STDC_WANT_SECURE_LIB__
}

inline static VOID StringCat ( LPSTR sDestination, DWORD dwLimit, LPSTR sSource )
{
#ifdef __STDC_WANT_SECURE_LIB__
	strcat_s( sDestination, dwLimit, sSource );
#else //__STDC_WANT_SECURE_LIB__
	StringCbCat( sDestination, dwLimit, sSource );
#endif //__STDC_WANT_SECURE_LIB__
}

inline static LONG StringCompare ( LPSTR sA, LPSTR sB )
{
	return strcmp( sA, sB );
}

inline static LONG StringCompareLc ( LPSTR sA, LPSTR sB )
{
#ifdef __STDC_WANT_SECURE_LIB__
	return _strcmpi( sA, sB );
#else //__STDC_WANT_SECURE_LIB__
	return strcmpi( sA, sB );
#endif //__STDC_WANT_SECURE_LIB__
}

inline static DWORD StringLength ( LPSTR sT )
{
	return (DWORD)strlen( sT );
}

inline static VOID StringPrint ( LPSTR sDestination, DWORD dwLimit, LPSTR sFormat, ... )
{
	va_list aList;
	va_start(aList, sFormat);

#ifdef __STDC_WANT_SECURE_LIB__
	vsprintf_s( sDestination, dwLimit, sFormat, aList );
#else //__STDC_WANT_SECURE_LIB__
	StringCbVPrintf( sDestination, dwLimit, sFormat, aList );
#endif //__STDC_WANT_SECURE_LIB__

	va_end(aList);
}

inline static VOID StringScan ( LPSTR sSource, LPSTR sFormat, ... )
{
	va_list aList;
	va_start(aList, sFormat);

#ifdef __STDC_WANT_SECURE_LIB__
	sscanf_s( sSource, sFormat, *(void**)aList );
#else //__STDC_WANT_SECURE_LIB__
	sscanf( sSource, sFormat, *(void**)aList );
#endif //__STDC_WANT_SECURE_LIB__

	va_end(aList);
}

inline static BOOLEAN _IsCharAlpha ( CHAR c )
{
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

inline static BOOLEAN _IsCharNumeric ( CHAR c )
{
	return (c >= '0' && c <= '9');
}

inline static BOOLEAN _IsCharAlphaNumeric ( CHAR c )
{
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}

inline static BOOLEAN _IsStringEmpty ( LPSTR sString )
{
	if ( sString[0] == 0 )
		return 1;
	else
		return 0;
}

inline static BOOLEAN _IsStringValidName ( LPSTR sString )
{
	BYTE* pChar = (BYTE*)sString;

	while ( *pChar )
	{
		if ( (*pChar > 0x20 && *pChar <= 0x7E) || (*pChar > 0xA0 && *pChar <= 0xFF) )
			pChar++;
		else
			return 0;
	}

	return 1;
}

inline static BOOLEAN _IsStringAbsolutePath ( LPSTR sString )
{
	BYTE* pChar = (BYTE*)sString;

	while ( *pChar )
	{
		if ( *pChar == ':' )
			return 1;
		else
			pChar++;
	}

	return 0;
}

inline static VOID StringJump ( CHAR* & pSource )
{
	while ( *pSource == ' ' )
	{
		pSource++;
	}
}

inline static VOID StringToString ( CHAR* pDestination, CHAR* & pSource, CHAR* pSeparator )
{
	/* on recopie le contenu de la source jusqu'à l'un des séparateurs */
	while ( *pSource )
	{
		DWORD k = 0;

		for ( DWORD k = 0 ; pSeparator[k] ; k++ )
			if ( *pSource == pSeparator[k] )
				goto end;

		*pDestination++ = *pSource++;
	}

end:

	/* on saute le séparateur */
	pSource++;

	/* on ferme la chaine */
	*pDestination = 0;
}

inline static FLOAT StringToFloat ( CHAR* & pSource, CHAR* pSeparator, FLOAT fDefault )
{
	CHAR sValue[32];

	StringToString( sValue, pSource, pSeparator );

	FLOAT fValue = fDefault;

	StringScan( sValue, "%f", &fValue );

	return fValue;
}

inline static LPSTR StringPath ( LPSTR sDir, LPSTR sFile )
{
	static CHAR sBuffer[256];

	SHORT p, q;

	for ( p = 0 ; p < 254 ; p++ )
	{
		if ( *sDir )
			sBuffer[p] = *sDir++;
		else
			break;
	}

	if ( p > 0 && sBuffer[p-1] != '\\' ) sBuffer[p++] = '\\';

	for ( q = p ; q < 254 ; q++ )
	{
		if ( *sFile )
			sBuffer[q] = *sFile++;
		else
			break;
	}

	sBuffer[q] = 0;

	return sBuffer;
}

inline static LPSTR StringDir ( LPSTR sPath )
{
	CHAR* pChar = sPath;
	
	/* recherche du dernier antislash */

	CHAR* pSlash = pChar - 1;

	while ( *pChar )
	{
		if ( *pChar == '\\' ) pSlash = pChar;

		pChar++;
	}

	/* copie des caractères jusqu'à celui-ci */

	pChar = sPath;

	static CHAR sBuffer[256];

	SHORT k = 0;

	while ( pChar < pSlash )
		sBuffer[k++] = *pChar++;

	/* terminaison de la chaine */

	sBuffer[k] = 0;

	return sBuffer;
}

inline static LPSTR StringFile ( LPSTR sPath )
{
	CHAR* pChar = sPath;

	/* recherche du dernier antislash */

	CHAR* pSlash = pChar - 1;

	while ( *pChar )
	{
		if ( *pChar == '\\' ) pSlash = pChar;

		pChar++;
	}

	/* copie des caractères à partir de celui-ci */

	pChar = pSlash + 1;

	static CHAR sBuffer[256];

	SHORT k = 0;

	while ( *pChar )
		sBuffer[k++] = *pChar++;

	/* terminaison de la chaine */

	sBuffer[k] = 0;

	return sBuffer;
}
