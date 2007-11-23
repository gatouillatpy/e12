
#include "impulse.h"
#include "manager.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



MANAGER12::MANAGER12 ( LOG12* _pLog )
{
	pLog = _pLog;

	/* initialisation des noeuds racines */
	pResourceRoot = NULL;
	pEntityRoot = NULL;
	pFileRoot = NULL;
}

MANAGER12::~MANAGER12 ( )
{
	/* destruction des noeuds racines et tous leurs descendents */
	if ( pResourceRoot )
		Free( pResourceRoot );
	if ( pEntityRoot )
		Collapse( pEntityRoot );
	if ( pFileRoot )
		Collapse( pFileRoot );
}

