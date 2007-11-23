
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID RENDER12::SetStageState ( DWORD _dwStage, STAGESTATE12* _pStageState )
{
	if ( _pStageState )
	{
		pStageState = _pStageState;

		lpD3DDevice->SetTextureStageState( _dwStage, D3DTSS_TEXCOORDINDEX, _pStageState->Input );
	}
	else if ( pStageState )
	{
		pStageState = NULL;

		lpD3DDevice->SetTextureStageState( _dwStage, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_PASSTHRU );
	}
}

STAGESTATE12* RENDER12::GetStageState ( )
{
	return pStageState;
}
