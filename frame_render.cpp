
#include "frame.h"
#include "interface.h"
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID FRAME12::RenderBack ( )
{
	FLOAT fLeft = AbsoluteLeft();
	FLOAT fTop = AbsoluteTop();
	FLOAT fWidth = AbsoluteWidth();
	FLOAT fHeight = AbsoluteHeight();

	FLOAT fU = InterfaceWidth() / pRender->GetWidth();
	FLOAT fV = InterfaceHeight() / pRender->GetHeight();

	pRender->SetBlendState( pBackBlendState );

	FLOAT fX1 = fLeft - 2.0f * fU; FLOAT fX2 = fLeft + 2.0f * fU + fWidth;
	FLOAT fY1 = fTop - 1.0f * fV; FLOAT fY2 = fTop + 1.0f * fV + fHeight;

	pRender->DrawArea( D3DXVECTOR2( fX1, fY1 ), D3DXVECTOR2( fX2, fY2 ), vBackColor );
}



VOID FRAME12::RenderBorder ( )
{
	if ( bBorder )
	{
		pRender->SetBlendState( pBorderBlendState );

		if ( tBorderStyle == BS_WIN9X_FRONT )
			RenderBorderWin9XFront();
		else if ( tBorderStyle == BS_WIN9X_BACK )
			RenderBorderWin9XBack();
	}
}



VOID FRAME12::RenderBorderWin9XBack ( )
{
	FLOAT fLeft = AbsoluteLeft();
	FLOAT fTop = AbsoluteTop();
	FLOAT fWidth = AbsoluteWidth();
	FLOAT fHeight = AbsoluteHeight();

	FLOAT fU = InterfaceWidth() / pRender->GetWidth();
	FLOAT fV = InterfaceHeight() / pRender->GetHeight();

	{
		FLOAT fX1 = fLeft - 4.0f * fU; FLOAT fX2 = fLeft + 3.0f * fU + fWidth;
		FLOAT fY1 = fTop - 2.0f * fV; FLOAT fY2 = fTop + 2.0f * fV + fHeight;
		pRender->DrawLine( D3DXVECTOR2( fX1, fY1 ), D3DXVECTOR2( fX2, fY1 ), vBorderColor * 0.25f );
		pRender->DrawLine( D3DXVECTOR2( fX1, fY1 ), D3DXVECTOR2( fX1, fY2 ), vBorderColor * 0.25f );
	}

	{
		FLOAT fX1 = fLeft - 3.0f * fU; FLOAT fX2 = fLeft + 2.0f * fU + fWidth;
		FLOAT fY1 = fTop - 1.0f * fV; FLOAT fY2 = fTop + 1.0f * fV + fHeight;
		pRender->DrawLine( D3DXVECTOR2( fX1, fY1 ), D3DXVECTOR2( fX2, fY1 ), vBorderColor * 0.5f );
		pRender->DrawLine( D3DXVECTOR2( fX1, fY1 ), D3DXVECTOR2( fX1, fY2 ), vBorderColor * 0.5f );
	}

	{
		FLOAT fX1 = fLeft - 4.0f * fU; FLOAT fX2 = fLeft + 3.0f * fU + fWidth;
		FLOAT fY1 = fTop - 3.0f * fV; FLOAT fY2 = fTop + 2.0f * fV + fHeight;
		pRender->DrawLine( D3DXVECTOR2( fX2, fY2 ), D3DXVECTOR2( fX2, fY1 ), vBorderColor * 1.0f );
		pRender->DrawLine( D3DXVECTOR2( fX2, fY2 ), D3DXVECTOR2( fX1, fY2 ), vBorderColor * 1.0f );
	}

	{
		FLOAT fX1 = fLeft - 3.0f * fU; FLOAT fX2 = fLeft + 2.0f * fU + fWidth;
		FLOAT fY1 = fTop - 2.0f * fV; FLOAT fY2 = fTop + 1.0f * fV + fHeight;
		pRender->DrawLine( D3DXVECTOR2( fX2, fY2 ), D3DXVECTOR2( fX2, fY1 ), vBorderColor * 0.75f );
		pRender->DrawLine( D3DXVECTOR2( fX2, fY2 ), D3DXVECTOR2( fX1, fY2 ), vBorderColor * 0.75f );
	}
}

VOID FRAME12::RenderBorderWin9XFront ( )
{
	FLOAT fLeft = AbsoluteLeft();
	FLOAT fTop = AbsoluteTop();
	FLOAT fWidth = AbsoluteWidth();
	FLOAT fHeight = AbsoluteHeight();

	FLOAT fU = InterfaceWidth() / pRender->GetWidth();
	FLOAT fV = InterfaceHeight() / pRender->GetHeight();

	pRender->SetBlendState( pBorderBlendState );

	{
		FLOAT fX1 = fLeft - 4.0f * fU; FLOAT fX2 = fLeft + 3.0f * fU + fWidth;
		FLOAT fY1 = fTop - 2.0f * fV; FLOAT fY2 = fTop + 2.0f * fV + fHeight;
		pRender->DrawLine( D3DXVECTOR2( fX1, fY1 ), D3DXVECTOR2( fX2, fY1 ), vBorderColor * 1.0f );
		pRender->DrawLine( D3DXVECTOR2( fX1, fY1 ), D3DXVECTOR2( fX1, fY2 ), vBorderColor * 1.0f );
	}

	{
		FLOAT fX1 = fLeft - 3.0f * fU; FLOAT fX2 = fLeft + 2.0f * fU + fWidth;
		FLOAT fY1 = fTop - 1.0f * fV; FLOAT fY2 = fTop + 1.0f * fV + fHeight;
		pRender->DrawLine( D3DXVECTOR2( fX1, fY1 ), D3DXVECTOR2( fX2, fY1 ), vBorderColor * 0.75f );
		pRender->DrawLine( D3DXVECTOR2( fX1, fY1 ), D3DXVECTOR2( fX1, fY2 ), vBorderColor * 0.75f );
	}

	{
		FLOAT fX1 = fLeft - 4.0f * fU; FLOAT fX2 = fLeft + 3.0f * fU + fWidth;
		FLOAT fY1 = fTop - 3.0f * fV; FLOAT fY2 = fTop + 2.0f * fV + fHeight;
		pRender->DrawLine( D3DXVECTOR2( fX2, fY2 ), D3DXVECTOR2( fX2, fY1 ), vBorderColor * 0.25f );
		pRender->DrawLine( D3DXVECTOR2( fX2, fY2 ), D3DXVECTOR2( fX1, fY2 ), vBorderColor * 0.25f );
	}

	{
		FLOAT fX1 = fLeft - 3.0f * fU; FLOAT fX2 = fLeft + 2.0f * fU + fWidth;
		FLOAT fY1 = fTop - 2.0f * fV; FLOAT fY2 = fTop + 1.0f * fV + fHeight;
		pRender->DrawLine( D3DXVECTOR2( fX2, fY2 ), D3DXVECTOR2( fX2, fY1 ), vBorderColor * 0.5f );
		pRender->DrawLine( D3DXVECTOR2( fX2, fY2 ), D3DXVECTOR2( fX1, fY2 ), vBorderColor * 0.5f );
	}
}



VOID FRAME12::Render ( )
{
	if ( bVisible == FALSE ) return;

	RenderBack();

	RenderBorder();
}
