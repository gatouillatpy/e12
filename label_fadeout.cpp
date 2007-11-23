
#include "label.h"
#include "label_fadeout.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



LABEL12_FADEOUT::LABEL12_FADEOUT ( CONTROL12* _pControl, DOUBLE _fDuration ) : FRAME12_FADEOUT( _pControl, _fDuration )
{
}



VOID LABEL12_FADEOUT::Create ( )
{
	FRAME12_FADEOUT::Create();

	LABEL12* pLabel = (LABEL12*)pControl;

	pFontBlendState = pLabel->GetFontBlendState();

	pLabel->SetFontBlendState( pFadeBlendState );
}



VOID LABEL12_FADEOUT::Destroy ( )
{
	LABEL12* pLabel = (LABEL12*)pControl;

	pLabel->SetFontBlendState( pFontBlendState );

	FRAME12_FADEOUT::Destroy();
}
