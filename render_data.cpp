
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID RENDER12::SetFocus ( CONTROL12* _pControl )
{
	pFocus = _pControl;
}

CONTROL12* RENDER12::GetFocus ( )
{
	return pFocus;
}



VOID RENDER12::EnableWireframe ( )
{
	bWireframe = TRUE;
}

VOID RENDER12::DisableWireframe ( )
{
	bWireframe = FALSE;
}



VOID RENDER12::SetPhaseCount ( DWORD _dwPhaseCount )
{
	for ( DWORD k = dwPhaseCount ; k < _dwPhaseCount ; k++ )
	{
		ppPhaseBuffer[k] = new BUFFER12( this );
		ppPhaseBuffer[k]->Generate( nWidth, nHeight );
		ppPhaseBuffer[k]->SetIndex( TEXTURE_PHASE(k) );
	}

	dwPhaseCount = _dwPhaseCount;
}

DWORD RENDER12::GetPhaseCount ( )
{
	return dwPhaseCount;
}
