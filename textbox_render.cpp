
#include "textbox.h"
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID TEXTBOX12::RenderCursor ( )
{
	if ( TryEnterCriticalSection( &cs ) == 0 ) return;

	FLOAT ax = fOffsetX;
	FLOAT ay = fOffsetY;

	if ( sCaption )
	{
		UINT nLength = StringLength( sCaption );

		if ( nLength > 0 )
		{
			FLOAT p = (FLOAT)pFont->lWidth / 2048.0f;
			FLOAT q = (FLOAT)pFont->lHeight / 2048.0f;

			FLOAT fLineHeight = 0.0f;

			for ( UINT k = 0 ; k < nCursor ; k++ )
			{
				BYTE c = sCaption[k];

				if ( c == 10 )
				{
					ax = fOffsetX;
					ay += fLineHeight * fLineSpacing;

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
			}
		}
	}

	FLOAT t = pFont->pScale[90].y;

	FLOAT fU = 1.0f / pRender->GetWidth();
	FLOAT fV = 1.0f / pRender->GetHeight();

	FLOAT fX1 = AbsoluteLeft();
	FLOAT fY1 = AbsoluteTop();
	FLOAT fX2 = fX1 + fMaxWidth;
	FLOAT fY2 = fY1 + fMaxHeight;

	if ( ax + 5.0f * fU > fMaxWidth )
		fOffsetX += fMaxWidth - ax - 5.0f * fU;
	if ( ax < 0.0f )
		fOffsetX -= ax;

	if ( ay + t * 0.7f > fMaxHeight )
		fOffsetY += fMaxHeight - ay - t * 0.7f;
	if ( ay < 0.0f )
		fOffsetY -= ay;

	ax *= InterfaceWidth();
	ay *= InterfaceHeight();

	t *= InterfaceHeight();

	D3DXVECTOR2 vPA = D3DXVECTOR2( fX1 + ax, fY1 + ay + t * 0.1f );
	D3DXVECTOR2 vPB = vPA + D3DXVECTOR2( 2.0f * fU, t * 0.5f );

	pRender->SetBlendState( pFontBlendState );

	pRender->DrawArea( vPA, vPB, vFontColor );

	LeaveCriticalSection( &cs );
}



VOID TEXTBOX12::Render ( )
{
	if ( bVisible == FALSE ) return;

	RenderBack();

	RenderCaption();

	RenderCursor();

	RenderBorder();
}
