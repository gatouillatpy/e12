
#include "label.h"
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID LABEL12::TextSize ( FLOAT & ax, FLOAT & ay, FLOAT & mx, FLOAT & my, FLOAT & fLineHeight, FONT12* pFont, FLOAT fFontSize, LPSTR sText )
{
	if ( sText == NULL ) return;

	UINT nLength = StringLength( sText );

	for ( UINT k = 0 ; k < nLength ; k++ )
	{
		BYTE c = sText[k];

		if ( c == 10 )
		{
			ay += fLineHeight * fLineSpacing;
			ax = 0.0f;

			fLineHeight = 0.0f;
		}

		D3DXVECTOR2 tOffset = pFont->pOffset[c];
		D3DXVECTOR2 tScale = pFont->pScale[c];

		FLOAT au = tOffset.x;
		FLOAT av = tOffset.y;
		FLOAT bu = tOffset.x + tScale.x;
		FLOAT bv = tOffset.y + tScale.y;

		FLOAT bx = ax + fFontSize * (bu - au);
		FLOAT by = ay + fFontSize * (bv - av);

		if ( by - ay > fLineHeight )
			fLineHeight = by - ay;

		ax = bx;

		if ( bx > mx ) mx = bx;
		if ( by > my ) my = by;
	}
}



VOID LABEL12::TextWrap ( FLOAT & ax, FLOAT & mx, CHAR* & pWordSpace, FLOAT & fWordSize, FLOAT & fGroupSize, FONT12* pFont, FLOAT fFontSize, LPSTR sText )
{
	if ( sText == NULL ) return;

	UINT nLength = StringLength( sText );

	for ( UINT k = 0 ; k < nLength ; k++ )
	{
		BYTE c = sText[k];

		if ( c == 32 )
		{
			pWordSpace = &sText[k];
			fWordSize = 0.0f;
		}

		if ( c == 10 )
		{
			ax = 0.0f;

			pWordSpace = &sText[k];
			fWordSize = 0.0f;
			fGroupSize = 0.0f;
		}

		D3DXVECTOR2 tOffset = pFont->pOffset[c];
		D3DXVECTOR2 tScale = pFont->pScale[c];

		FLOAT au = tOffset.x;
		FLOAT bu = tOffset.x + tScale.x;

		FLOAT bx = ax + fFontSize * (bu - au);

		fGroupSize += bx - ax;
		fWordSize += bx - ax;

		if ( fGroupSize > fMaxWidth )
		{
			*pWordSpace = 10;

			fGroupSize = fWordSize - bx + ax;
		}

		ax = bx;
	}
}



VOID LABEL12::AutoSize ( )
{
	FLOAT ax = 0.0f;
	FLOAT ay = 0.0f;
	FLOAT mx = 0.0f;
	FLOAT my = 0.0f;

	FLOAT fLineHeight = 0.0f;

	TextSize( ax, ay, mx, my, fLineHeight, pFont, fFontSize, sCaption );

	if ( bAutoWrap == FALSE )
	{
		fWidth = mx;
		fMaxWidth = mx;
	}

	fHeight = my;
	fMaxHeight = my;
}



VOID LABEL12::AutoWrap ( )
{
	FLOAT ax = 0.0f;
	FLOAT mx = 0.0f;

	CHAR* pWordSpace = sCaption;
	FLOAT fWordSize = 0.0f;
	FLOAT fGroupSize = 0.0f;

	TextWrap( ax, mx, pWordSpace, fWordSize, fGroupSize, pFont, fFontSize, sCaption );
}



VOID LABEL12::AutoOffset ( )
{
	FLOAT ax = 0.0f;
	FLOAT ay = 0.0f;
	FLOAT mx = 0.0f;
	FLOAT my = 0.0f;

	FLOAT fLineHeight = 0.0f;

	TextSize( ax, ay, mx, my, fLineHeight, pFont, fFontSize, sCaption );

	if ( my > fMaxHeight )
		fOffsetY = fMaxHeight - my;
}
