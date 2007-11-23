
#include "control_effect.h"
#include "control.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID CONTROL12::ApplyEffect ( CONTROL12_EFFECT* _pEffect )
{
	if ( pEffect )
	{
		pEffect->ApplyNext( _pEffect );
	}
	else
	{
		pEffect = _pEffect;

		pEffect->Create();
	}
}



VOID CONTROL12_EFFECT::ApplyNext ( CONTROL12_EFFECT* _pNext )
{
	if ( pNext )
	{
		pNext->ApplyNext( _pNext );
	}
	else
	{
		pNext = _pNext;
	}
}



CONTROL12_EFFECT::CONTROL12_EFFECT ( CONTROL12* _pControl, DOUBLE _fDuration )
{
	pControl = _pControl;

	pNext = NULL;

	pEngine = pControl->pRender->pEngine;

	fDuration = _fDuration;
}



VOID CONTROL12_EFFECT::Create ( )
{
	fStartTime = pEngine->GetTime();
	fStopTime = fStartTime + fDuration;
}



VOID CONTROL12_EFFECT::Update ( )
{
	if ( pEngine->GetTime() > fStopTime ) Destroy();
}



VOID CONTROL12_EFFECT::Destroy ( )
{
	pControl->pEffect = pNext;
	
	if ( pNext )
		pNext->Create();

	delete this;
}
