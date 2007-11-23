
#include "document.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



DOCUMENT12::DOCUMENT12 ( LOG12* _pLog )
{
	pParent = NULL;

	pLog = _pLog;

	dwType = TYPE_NONE;

	dwChildCount = 0;
	ppChild = NULL;

	sClass = NULL;

	sPath = NULL;

	sName = NULL;
	dwIndex = -1;

	sValue = NULL;
	nValue = 0;
	fValue = 0.0;
}

DOCUMENT12::DOCUMENT12 ( DOCUMENT12* _pParent )
{
	pParent = _pParent;

	pLog = pParent->pLog;

	dwType = TYPE_NONE;

	dwChildCount = 0;
	ppChild = NULL;

	sClass = NULL;

	sPath = NULL;

	sName = NULL;
	dwIndex = -1;

	sValue = NULL;
	nValue = 0;
	fValue = 0.0;

	pParent->AddChild( this );
}

DOCUMENT12::~DOCUMENT12 ( )
{
	if ( ppChild )
	{
		for ( DWORD k = 0 ; k < dwChildCount ; k++ )
		{
			if ( ppChild[k] )
				delete ppChild[k];
		}

		delete [] ppChild;
	}

	if ( sPath )
		delete [] sPath;

	if ( sClass )
		delete [] sClass;

	if ( sName )
		delete [] sName;

	if ( sValue )
		delete [] sValue;
}
