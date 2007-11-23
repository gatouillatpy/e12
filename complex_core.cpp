
#include "complex.h"
#include "scene.h"
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID COMPLEX12::Render ( CAMERA12* _pCamera )
{
	if ( dwOperation == OPERATION_UNION )
	{
		pA->Render( _pCamera );
		pB->Render( _pCamera );
	}
	else if ( dwOperation == OPERATION_SUBTRACTION )
	{
		if ( pA->IsComplex() )
		{
			pA->Render( _pCamera );
		}
		else
		{
			// à traiter
		}

		if ( pB->IsComplex() )
		{
			pB->Render( _pCamera );
		}
		else
		{
			// à traiter
		}
	}
	else if ( dwOperation == OPERATION_INTERSECTION )
	{
		if ( pA->IsComplex() )
		{
			pA->Render( _pCamera );
		}
		else
		{
			// à traiter
		}

		if ( pB->IsComplex() )
		{
			pB->Render( _pCamera );
		}
		else
		{
			// à traiter
		}
	}
}
