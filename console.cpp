
#include "console.h"
#include "render.h"
#include "cmdbox.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



CONSOLE12::CONSOLE12 ( RENDER12* _pRender, UINT _nLineCount ) : INTERFACE12( _pRender )
{
	pLog = _pRender->pLog;

	pLog->RegisterImpulseCallback( ImpulseCallback, this );
	pLog->RegisterReportCallback( ReportCallback, this );

	tStyle = STYLE_WIN9X;

	pCommand = pRender->AddCmdbox();
	pCommand->SetLeft( 0.0f );
	pCommand->SetTop( 0.96f );
	pCommand->SetWidth( 1.0f );
	pCommand->SetHeight( 0.04f );
	pCommand->SetFontSize( 0.72f );
	AddControl( pCommand );

	nLineCount = _nLineCount;

	pOutput = pRender->AddALabel();
	pOutput->SetLeft( 0.0f );
	pOutput->SetTop( 0.0f );
	pOutput->SetWidth( 1.0f );
	pOutput->SetHeight( 0.95f );
	pOutput->SetFontSize( 0.72f );
	pOutput->SetAutoWrap( TRUE );
	pOutput->SetAutoOffset( TRUE );
	AddControl( pOutput );
}
