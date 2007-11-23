
#include "alabel.h"
#include "interface.h"
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



ALABEL12::ALABEL12 ( RENDER12* _pRender ) : LABEL12( _pRender )
{
	nCaptionCount = 0;
	ppCaption = NULL;
}

ALABEL12::~ALABEL12 ( )
{
	if ( ppCaption )
	{
		for ( DWORD k = 0 ; k < nCaptionCount ; k++ )
		{
			delete [] ppCaption[k]->sText;
			delete ppCaption[k];
		}

		free( ppCaption );
	}
}
