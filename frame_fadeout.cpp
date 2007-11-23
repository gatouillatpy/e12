
#include "frame.h"
#include "frame_fadeout.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



FRAME12_FADEOUT::FRAME12_FADEOUT ( CONTROL12* _pControl, DOUBLE _fDuration ) : CONTROL12_EFFECT( _pControl, _fDuration )
{
}



VOID FRAME12_FADEOUT::Create ( )
{
	CONTROL12_EFFECT::Create();

	FRAME12* pFrame = (FRAME12*)pControl;

	pBackBlendState = pFrame->GetBackBlendState();
	pBorderBlendState = pFrame->GetBorderBlendState();

	pFadeBlendState = new BLENDSTATE12;
	pFadeBlendState->Operation = BO_ADD;
	pFadeBlendState->Current = BF_INVCONSTANT;
	pFadeBlendState->Waiting = BF_CONSTANT;
	pFadeBlendState->Constant = D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f);

	pFrame->SetBackBlendState( pFadeBlendState );
	pFrame->SetBorderBlendState( pFadeBlendState );
}



VOID FRAME12_FADEOUT::Update ( )
{
	DOUBLE fFactor = (fStopTime - pEngine->GetTime()) / (fStopTime - fStartTime);

	pFadeBlendState->Constant = D3DCOLOR_COLORVALUE(fFactor, fFactor, fFactor, fFactor);

	CONTROL12_EFFECT::Update();
}



VOID FRAME12_FADEOUT::Destroy ( )
{
	FRAME12* pFrame = (FRAME12*)pControl;

	pFrame->SetBackBlendState( pBackBlendState );
	pFrame->SetBorderBlendState( pBorderBlendState );
	pFrame->Hide();

	delete pFadeBlendState;

	CONTROL12_EFFECT::Destroy();
}
