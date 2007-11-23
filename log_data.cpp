
#include "log.h"
#include "impulse.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



LPSTR LOG12::ReadLn ( DWORD _dwLine )
{
	if ( _dwLine >= dwCount )
		return NULL;

	return pLine[dwCount-_dwLine-1];
}



VOID LOG12::Write ( LPSTR sFormat, ... )
{
	va_list aList;
	va_start(aList, sFormat);

	CHAR sInfo[256];
	StringPrint( sInfo, 256, sFormat, *(void**)aList );

	va_end(aList);

	LPSTR sLine = pLine[dwCount-1];

	DWORD dwLength = StringLength(sLine) + StringLength(sInfo) + 1;
	pLine[dwCount-1] = new CHAR[dwLength];

	StringCopy(pLine[dwCount-1], dwLength, sLine);
	StringCat(pLine[dwCount-1], dwLength, sInfo);

	delete [] sLine;
}

VOID LOG12::WriteLn ( LPSTR sFormat, ... )
{
	va_list aList;
	va_start(aList, sFormat);

	CHAR sInfo[256];
	StringPrint( sInfo, 256, sFormat, *(void**)aList );

	va_end(aList);

	pLine = (LPSTR*) realloc( pLine, ++dwCount * sizeof(LPSTR) );

	DWORD dwLength = StringLength(sInfo) + 1;
	pLine[dwCount-1] = new CHAR[dwLength];

	StringCopy(pLine[dwCount-1], dwLength, sInfo);
}
