
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID RENDER12::SetBlendState ( BLENDSTATE12* _pBlendState )
{
	if ( _pBlendState )
	{
		pBlendState = _pBlendState;

		lpD3DDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
		lpD3DDevice->SetRenderState( D3DRS_SRCBLEND, _pBlendState->Waiting );
		lpD3DDevice->SetRenderState( D3DRS_DESTBLEND, _pBlendState->Current );
		lpD3DDevice->SetRenderState( D3DRS_BLENDOP, _pBlendState->Operation );
		lpD3DDevice->SetRenderState( D3DRS_BLENDFACTOR, _pBlendState->Constant );
	}
	else if ( pBlendState )
	{
		pBlendState = NULL;

		lpD3DDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE );
	}
}

BLENDSTATE12* RENDER12::GetBlendState ( )
{
	return pBlendState;
}
