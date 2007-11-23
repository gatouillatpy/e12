
#include "document.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID DOCUMENT12::AddChild ( DOCUMENT12* _pDocument )
{
	ppChild = (DOCUMENT12**) realloc( ppChild, ++dwChildCount * sizeof(DOCUMENT12*) );

	ppChild[dwChildCount-1] = _pDocument;
}

VOID DOCUMENT12::DelChild ( DOCUMENT12* _pDocument )
{
	if ( ppChild )
	{
		for ( DWORD k = 0 ; k < dwChildCount ; k++ )
			if ( ppChild[k] == _pDocument )
				ppChild[k] = NULL;
	}
}



DOCUMENT12* DOCUMENT12::GetChild ( LPSTR _sClass )
{
	if ( ppChild )
	{
		for ( DWORD k = 0 ; k < dwChildCount ; k++ )
			if ( ppChild[k] )
				if ( ppChild[k]->sClass )
					if ( StringCompareLc( ppChild[k]->sClass, _sClass ) == 0 )
						return ppChild[k];
	}

	return NULL;
}

DOCUMENT12* DOCUMENT12::GetChild ( DWORD _nID )
{
	if ( ppChild )
		return ppChild[_nID];
	else
		return NULL;
}
