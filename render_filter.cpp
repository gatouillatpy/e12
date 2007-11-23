
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID RENDER12::SetFilterState ( FILTERSTATE12* _pFilterState )
{
	if ( _pFilterState )
	{
		pFilterState = _pFilterState;

		lpD3DDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, _pFilterState->Magnification );
		lpD3DDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, _pFilterState->Minification );
		lpD3DDevice->SetSamplerState( 0, D3DSAMP_MIPFILTER, _pFilterState->MipmapFilter );
		lpD3DDevice->SetSamplerState( 0, D3DSAMP_MIPMAPLODBIAS, _pFilterState->MipmapLevel );
		lpD3DDevice->SetSamplerState( 0, D3DSAMP_MAXMIPLEVEL, _pFilterState->LevelOfDetail );
	}
	else if ( pFilterState )
	{
		pFilterState = NULL;

		lpD3DDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_POINT );
		lpD3DDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_POINT );
		lpD3DDevice->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_NONE );
		lpD3DDevice->SetSamplerState( 0, D3DSAMP_MIPMAPLODBIAS, 0 );
		lpD3DDevice->SetSamplerState( 0, D3DSAMP_MAXMIPLEVEL, 0 );
	}
}

FILTERSTATE12* RENDER12::GetFilterState ( )
{
	return pFilterState;
}
