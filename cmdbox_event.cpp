
#include "cmdbox.h"
#include "render.h"
#include "engine.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID CMDBOX12::OnChar ( KEYCONTEXT _nKeyContext, BYTE _nCharCode )
{
	if ( pRender->pFocus != this )
		return;

	if ( _nCharCode == 13 )
	{
		pEngine->ProcessCommand( sText );

		ZeroMemory( sText, 2048 );

		nCursor = 0;
	}
	else if ( _nCharCode > 31 )
	{
		sText[nCursor++] = _nCharCode;
	}

	LABEL12::SetCaption( sText );

	CALLBACK12* pTemp = mChar->pHead;

	while ( pTemp )
	{
		LPCHARCALLBACK Callback = (LPCHARCALLBACK)pTemp->lpCallback;

		Callback( _nKeyContext, _nCharCode, pTemp->lpData );

		pTemp = pTemp->pNext;
	}
}
