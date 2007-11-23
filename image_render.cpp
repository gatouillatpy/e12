
#include "image.h"
#include "interface.h"
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID IMAGE12::Render ( )
{
	FLOAT fX1 = AbsoluteLeft();
	FLOAT fY1 = AbsoluteTop();
	FLOAT fX2 = fX1 + AbsoluteWidth();;
	FLOAT fY2 = fY1 + AbsoluteHeight();;

	//pRender->SetBlendState( pFontBlendState );

	D3DXVECTOR2 vPA = D3DXVECTOR2( fX1, fY1 );
	D3DXVECTOR2 vPB = D3DXVECTOR2( fX2, fY2 );
	D3DXVECTOR2 vTA = D3DXVECTOR2( fOffsetU, fOffsetV );
	D3DXVECTOR2 vTB = D3DXVECTOR2( fOffsetU + fFactorU, fOffsetV + fFactorV );
	D3DXVECTOR2 vMin = D3DXVECTOR2( fX1, fY1 );
	D3DXVECTOR2 vMax = D3DXVECTOR2( fX2, fY2 );

	D3DXVECTOR4 vMaskColor = D3DXVECTOR4( 1.0f, 1.0f, 1.0f, 1.0f );
	D3DXVECTOR4 vTestColor = D3DXVECTOR4( 0.0f, 0.0f, 0.0f, 0.0f );

	pRender->DrawTexture( vPA, vPB, vTA, vTB, vMin, vMax, pTexture, vMaskColor, vTestColor );
}
