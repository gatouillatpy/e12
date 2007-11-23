
#pragma once


#include "util.h"

#include <crtdbg.h>

#ifndef __STDC_WANT_SECURE_LIB__
#include <strsafe.h>
#endif //__STDC_WANT_SECURE_LIB__



/* Affiche un message personnalisé dans l'onglet output de Visual Studio.                     */
/* -> Les arguments à passer sont de même nature que lors de l'appel de la fonction printf(). */
static VOID DebugPrint ( LPSTR sFormat, ... )
{
#ifdef _DEBUG

	va_list aList;
	va_start(aList, sFormat);

	CHAR sOutput[256] = {0};

#ifdef __STDC_WANT_SECURE_LIB__
	vsprintf_s( sOutput, 256, sFormat, aList );
#else //__STDC_WANT_SECURE_LIB__
	StringCbVPrintf( sOutput, 256, sFormat, aList );
#endif //__STDC_WANT_SECURE_LIB__

	OutputDebugString( sOutput );

	va_end(aList);

#endif //_DEBUG
}



/* Affiche dans l'onglet output de Visual Studio l'ensemble des pointeurs n'ayant pas été désalloués. */
/* -> L'entête de debug doit être placée au début de chaque fichier source.                           */
static VOID DebugMemoryLeaks ( )
{
	_CrtDumpMemoryLeaks();
}



#ifdef _DEBUG

	void* operator new(size_t nSize, const char * lpszFileName, int nLine) ;
	void operator delete(void * p, const char * lpszFileName, int nLine) ;
	#define DEBUG_NEW new(THIS_FILE, __LINE__)

	#define MALLOC_DBG(x) _malloc_dbg(x, 1, THIS_FILE, __LINE__);
	#define malloc(x) MALLOC_DBG(x)
	#define REALLOC_DBG(x, y) _realloc_dbg(x, y, 1, THIS_FILE, __LINE__);
	#define realloc(x, y) REALLOC_DBG(x, y)
	#define FREE_DBG(x) _free_dbg(x, 1);
	#define free(x) FREE_DBG(x)

	#define DXAssert(x, y) { if ( FAILED( y ) ) { DXTrace( __FILE__, (DWORD)__LINE__, x, DXGetErrorString(x), TRUE ); return x; } }

#else // _DEBUG

	#define DXAssert(x, y) { if ( FAILED( y ) ) return x; }

#endif // _DEBUG
