
#include "frame.h"
#include "frame_fadein.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



FRAME12_FADEIN::FRAME12_FADEIN ( CONTROL12* _pControl, DOUBLE _fDuration ) : CONTROL12_EFFECT( _pControl, _fDuration )
{
}



VOID FRAME12_FADEIN::Create ( )
{
	CONTROL12_EFFECT::Create();

	FRAME12* pFrame = (FRAME12*)pControl;

	pBackBlendState = pFrame->GetBackBlendState();
	pBorderBlendState = pFrame->GetBorderBlendState();

	pFadeBlendState = new BLENDSTATE12;
	pFadeBlendState->Operation = BO_ADD;
	pFadeBlendState->Current = BF_INVCONSTANT;
	pFadeBlendState->Waiting = BF_CONSTANT;
	pFadeBlendState->Constant = D3DCOLOR_COLORVALUE(0.0f, 0.0f, 0.0f, 0.0f);

	pFrame->Show();
	pFrame->SetBackBlendState( pFadeBlendState );
	pFrame->SetBorderBlendState( pFadeBlendState );
}



VOID FRAME12_FADEIN::Update ( )
{
	DOUBLE fFactor = (pEngine->GetTime() - fStartTime) / (fStopTime - fStartTime);

	pFadeBlendState->Constant = D3DCOLOR_COLORVALUE(fFactor, fFactor, fFactor, fFactor);

	CONTROL12_EFFECT::Update();
}



VOID FRAME12_FADEIN::Destroy ( )
{
	FRAME12* pFrame = (FRAME12*)pControl;

	pFrame->SetBackBlendState( pBackBlendState );
	pFrame->SetBorderBlendState( pBorderBlendState );

	delete pFadeBlendState;

	CONTROL12_EFFECT::Destroy();
}
