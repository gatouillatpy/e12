
#include "console.h"
#include "render.h"
#include "cmdbox.h"
#include "label_fadein.h"
#include "label_fadeout.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID CONSOLE12::SetStyle ( STYLE _tStyle )
{
	tStyle = _tStyle;

	pOutput->SetStyle( (FRAME12::STYLE)_tStyle );
	pCommand->SetStyle( (FRAME12::STYLE)_tStyle );
}

CONSOLE12::STYLE CONSOLE12::GetStyle ( )
{
	return tStyle;
}



VOID CONSOLE12::SetFont ( FONT12* _pFont )
{
	pFont = _pFont;

	pOutput->SetFont( _pFont );
	pCommand->SetFont( _pFont );
}

FONT12* CONSOLE12::GetFont ( )
{
	return pFont;
}



VOID CONSOLE12::FadeIn ( )
{
	pOutput->ApplyEffect( new LABEL12_FADEIN( pOutput, 1.0f ) );
	pCommand->ApplyEffect( new LABEL12_FADEIN( pCommand, 1.0f ) );
}

VOID CONSOLE12::FadeOut ( )
{
	pOutput->ApplyEffect( new LABEL12_FADEOUT( pOutput, 1.0f ) );
	pCommand->ApplyEffect( new LABEL12_FADEOUT( pCommand, 1.0f ) );
}



ALABEL12* CONSOLE12::Output ( )
{
	return pOutput;
}

CMDBOX12* CONSOLE12::Command ( )
{
	return pCommand;
}
