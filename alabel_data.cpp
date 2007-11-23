
#include "label.h"
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID ALABEL12::SetCaption ( LPSTR _sCaption )
{
	pCaption = _sCaption;

	if ( _sCaption == NULL ) return;

	/* on conserve le style par défaut */
	FONT12* tFont = pFont;
	DWORD tColor = D3DCOLOR_COLORVALUE(vFontColor.x, vFontColor.y, vFontColor.z, vFontColor.w);
	FLOAT tSize = fFontSize;

	/* on supprime le contenu précedent s'il existe */
	if ( ppCaption )
	{
		for ( DWORD k = 0 ; k < nCaptionCount ; k++ )
		{
			delete [] ppCaption[k]->sText;
			delete ppCaption[k];
		}

		free( ppCaption );
	}

	/* on alloue de la mémoire pour le nouveau contenu */
	nCaptionCount = 1;
	ppCaption = (CAPTION**) malloc( sizeof(CAPTION*) );
	ppCaption[0] = new CAPTION;

	UINT nLength = StringLength( _sCaption ) + 1;

	LPSTR sTemp = new CHAR[nLength];

	CONST DWORD BLOCK_TEXT = 0x0000;
	CONST DWORD BLOCK_STYLE = 0x1000;
	CONST DWORD BLOCK_FONT = 0x1001;
	CONST DWORD BLOCK_COLOR = 0x1002;
	CONST DWORD BLOCK_SIZE = 0x1003;

	DWORD dwBlock = BLOCK_TEXT;

	for ( UINT k = 0, n = 0 ; k < nLength ; k++ )
	{
		if ( _sCaption[k] == 0 || _sCaption[k] == '<' )
		{
			sTemp[n] = 0;

			ppCaption[nCaptionCount-1]->pFont = tFont;
			ppCaption[nCaptionCount-1]->dwColor = tColor;
			ppCaption[nCaptionCount-1]->fSize = tSize;
			ppCaption[nCaptionCount-1]->sText = new CHAR[n+1];
			StringCopy( ppCaption[nCaptionCount-1]->sText, n + 1, sTemp );
		}
		
		if ( dwBlock == BLOCK_TEXT )
		{
			if ( _sCaption[k] == '<' )
			{
				dwBlock = BLOCK_STYLE;

				ppCaption = (CAPTION**) realloc( ppCaption, ++nCaptionCount * sizeof(CAPTION*) );
				ppCaption[nCaptionCount-1] = new CAPTION;
			}
			else
			{
				sTemp[n++] = _sCaption[k];
			}
		}
		else if ( dwBlock == BLOCK_STYLE )
		{
			if ( _sCaption[k] == '$' )
				dwBlock = BLOCK_FONT;
			else if ( _sCaption[k] == '#' )
				dwBlock = BLOCK_COLOR;
			else if ( _sCaption[k] == '%' )
				dwBlock = BLOCK_SIZE;

			if ( dwBlock != BLOCK_STYLE ) n = 0;
		}
		else if ( dwBlock == BLOCK_FONT )
		{
			if ( _sCaption[k] == '>' )
				dwBlock = BLOCK_TEXT;
			else if ( _sCaption[k] == '#' )
				dwBlock = BLOCK_COLOR;
			else if ( _sCaption[k] == '%' )
				dwBlock = BLOCK_SIZE;
			else if ( _sCaption[k] == ',' )
				dwBlock = BLOCK_STYLE;
			else if ( _sCaption[k] == ';' )
				dwBlock = BLOCK_STYLE;
			else if ( _sCaption[k] == ' ' )
				dwBlock = BLOCK_STYLE;
			else
				sTemp[n++] = _sCaption[k];
			
			if ( dwBlock != BLOCK_FONT )
			{
				sTemp[n] = 0; n = 0;

				FONT12* p = pRender->GetFont( sTemp );
				if ( p ) tFont = p;
			}
		}
		else if ( dwBlock == BLOCK_COLOR )
		{
			if ( _sCaption[k] == '>' )
				dwBlock = BLOCK_TEXT;
			else if ( _sCaption[k] == '$' )
				dwBlock = BLOCK_FONT;
			else if ( _sCaption[k] == '%' )
				dwBlock = BLOCK_SIZE;
			else if ( _sCaption[k] == ',' )
				dwBlock = BLOCK_STYLE;
			else if ( _sCaption[k] == ';' )
				dwBlock = BLOCK_STYLE;
			else if ( _sCaption[k] == ' ' )
				dwBlock = BLOCK_STYLE;
			else
				sTemp[n++] = _sCaption[k];

			if ( dwBlock != BLOCK_COLOR )
			{
				sTemp[n] = 0; n = 0;

				StringScan( sTemp, "%x", &tColor );
			}
		}
		else if ( dwBlock == BLOCK_SIZE )
		{
			if ( _sCaption[k] == '>' )
				dwBlock = BLOCK_TEXT;
			else if ( _sCaption[k] == '$' )
				dwBlock = BLOCK_FONT;
			else if ( _sCaption[k] == '#' )
				dwBlock = BLOCK_COLOR;
			else if ( _sCaption[k] == ',' )
				dwBlock = BLOCK_STYLE;
			else if ( _sCaption[k] == ';' )
				dwBlock = BLOCK_STYLE;
			else if ( _sCaption[k] == ' ' )
				dwBlock = BLOCK_STYLE;
			else
				sTemp[n++] = _sCaption[k];

			if ( dwBlock != BLOCK_SIZE )
			{
				sTemp[n] = 0; n = 0;

				StringScan( sTemp, "%f", &tSize );
			}
		}
	}

	delete [] sTemp;

	if ( bAutoWrap ) AutoWrap();
	if ( bAutoSize ) AutoSize();
	if ( bAutoOffset ) AutoOffset();
}

LPSTR ALABEL12::GetCaption ( )
{
	return pCaption;
}
