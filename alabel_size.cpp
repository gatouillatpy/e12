
#include "alabel.h"
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID ALABEL12::AutoSize ( )
{
	if ( ppCaption == NULL ) return;

	FLOAT ax = 0.0f;
	FLOAT ay = 0.0f;
	FLOAT mx = 0.0f;
	FLOAT my = 0.0f;

	FLOAT fLineHeight = 0.0f;

	for ( UINT n = 0 ; n < nCaptionCount ; n++ )
	{
		LPSTR tCaption = ppCaption[n]->sText;
		FONT12* tFont = ppCaption[n]->pFont;
		FLOAT tSize = ppCaption[n]->fSize;

		TextSize( ax, ay, mx, my, fLineHeight, tFont, tSize, tCaption );
	}

	if ( bAutoWrap == FALSE )
	{
		fWidth = mx;
		fMaxWidth = mx;
	}

	fHeight = my;
	fMaxHeight = my;
}



VOID ALABEL12::AutoWrap ( )
{
	if ( ppCaption == NULL ) return;

	FLOAT ax = 0.0f;
	FLOAT mx = 0.0f;

	CHAR* pWordSpace = ppCaption[0]->sText;
	FLOAT fWordSize = 0.0f;
	FLOAT fGroupSize = 0.0f;

	for ( UINT n = 0 ; n < nCaptionCount ; n++ )
	{
		LPSTR tCaption = ppCaption[n]->sText;
		FONT12* tFont = ppCaption[n]->pFont;
		FLOAT tSize = ppCaption[n]->fSize;

		TextWrap( ax, mx, pWordSpace, fWordSize, fGroupSize, tFont, tSize, tCaption );
	}
}



VOID ALABEL12::AutoOffset ( )
{
	if ( ppCaption == NULL ) return;

	FLOAT ax = 0.0f;
	FLOAT ay = 0.0f;
	FLOAT mx = 0.0f;
	FLOAT my = 0.0f;

	FLOAT fLineHeight = 0.0f;

	for ( UINT n = 0 ; n < nCaptionCount ; n++ )
	{
		LPSTR tCaption = ppCaption[n]->sText;
		FONT12* tFont = ppCaption[n]->pFont;
		FLOAT tSize = ppCaption[n]->fSize;

		TextSize( ax, ay, mx, my, fLineHeight, tFont, tSize, tCaption );
	}

	if ( my > fMaxHeight )
		fOffsetY = fMaxHeight - my;
}
