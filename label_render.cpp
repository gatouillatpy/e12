
#include "label.h"
#include "interface.h"
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID LABEL12::RenderCaption ( )
{
	if ( TryEnterCriticalSection( &cs ) == 0 ) return;

	if ( sCaption )
	{
		FLOAT fFontWidth = fFontSize * InterfaceWidth();
		FLOAT fFontHeight = fFontSize * InterfaceHeight();

		FLOAT fOX = fOffsetX * InterfaceWidth();
		FLOAT fOY = fOffsetY * InterfaceHeight();

		FLOAT fX1 = AbsoluteLeft();
		FLOAT fY1 = AbsoluteTop();
		FLOAT fX2 = fX1 + fMaxWidth * InterfaceWidth();;
		FLOAT fY2 = fY1 + fMaxHeight * InterfaceHeight();;

		pRender->SetBlendState( pFontBlendState );

		UINT nLength = StringLength( sCaption );

		FLOAT fLineHeight = 0.0f;

		D3DXVECTOR2 vOffset = D3DXVECTOR2( fX1 + fOX, fY1 + fOY );
		D3DXVECTOR2 vScale = D3DXVECTOR2( fFontWidth, fFontHeight );
		D3DXVECTOR2 vMin = D3DXVECTOR2( fX1, fY1 );
		D3DXVECTOR2 vMax = D3DXVECTOR2( fX2, fY2 );

		D3DXVECTOR4 vTestColor = D3DXVECTOR4( 0.0f, 0.0f, 0.0f, 0.0f );

		for ( UINT k = 0 ; k < nLength ; k++ )
		{
			UCHAR c = sCaption[k];

			if ( c == 10 )
			{
				vOffset.x = fX1 + fOX;
				vOffset.y += fLineHeight * fLineSpacing;

				fLineHeight = 0.0f;
			}

			FLOAT tLineHeight = pFont->pScale[c].y * fFontHeight;
			if ( tLineHeight > fLineHeight )
				fLineHeight = tLineHeight;

			pRender->DrawChar( vOffset, vScale, vMin, vMax, pFont, vFontColor, vTestColor, c );
		}
	}

	LeaveCriticalSection( &cs );
}



VOID LABEL12::Render ( )
{
	if ( bVisible == FALSE ) return;

	RenderBack();

	RenderCaption();

	RenderBorder();
}
