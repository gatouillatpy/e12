
#include "interface.h"
#include "render.h"
#include "indexer.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID INTERFACE12::Update ( )
{
	if ( bVisible == FALSE ) return;

	ENTITY12 **ppEntity, **ppEnd;

	iControl->Vector( ppEntity, ppEnd );
	while ( ppEntity < ppEnd )
	{
		CONTROL12* pControl = (CONTROL12*)*ppEntity;
		pControl->Update();
		ppEntity++;
	}

	iChild->Vector( ppEntity, ppEnd );
	while ( ppEntity < ppEnd )
	{
		INTERFACE12* pChild = (INTERFACE12*)*ppEntity;
		pChild->Update();
		ppEntity++;
	}

	if ( pCursor )
		pCursor->Update();
}
