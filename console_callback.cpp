
#include "console.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID CALLBACK ImpulseCallback ( LPSTR _sFile, DWORD _dwLine, CODE _nLevel, CODE _nClass, CODE _nNumber, LPVOID _pClass, LPVOID _pData, LPSTR _pComment, LPVOID _pUserData )
{
	CONSOLE12* pConsole = (CONSOLE12*)_pUserData;

	pConsole->pLog->Report();
	pConsole->pLog->Clear();
}



VOID CALLBACK ReportCallback ( LPVOID _pUserData )
{
	CONSOLE12* pConsole = (CONSOLE12*)_pUserData;

	static CHAR sText[32768];
	ZeroMemory( sText, 32768 );

	for ( INT k = pConsole->nLineCount - 1 ; k >= 0 ; k-- )
	{
		LPSTR sLine = pConsole->pLog->ReadLn(k);
		if ( sLine )
		{
			StringCat( sText, 32768, sLine );
			StringCat( sText, 32768, "\n" );
		}
	}

	pConsole->pOutput->SetCaption( sText );
}
