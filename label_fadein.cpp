
#include "label.h"
#include "label_fadein.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



LABEL12_FADEIN::LABEL12_FADEIN ( CONTROL12* _pControl, DOUBLE _fDuration ) : FRAME12_FADEIN( _pControl, _fDuration )
{
}



VOID LABEL12_FADEIN::Create ( )
{
	FRAME12_FADEIN::Create();

	LABEL12* pLabel = (LABEL12*)pControl;

	pFontBlendState = pLabel->GetFontBlendState();

	pLabel->SetFontBlendState( pFadeBlendState );
}



VOID LABEL12_FADEIN::Destroy ( )
{
	LABEL12* pLabel = (LABEL12*)pControl;

	pLabel->SetFontBlendState( pFontBlendState );

	FRAME12_FADEIN::Destroy();
}
