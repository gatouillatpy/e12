
#include "impulse.h"
#include "indexer.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



INDEXER12::INDEXER12 ( LOG12* _pLog )
{
	pLog = _pLog;

	/* mise des compteurs � zero */
	dwCount = 0;
	dwTick = 0;

	/* initialisation du vecteur d'entit�s */
	ppEntity = NULL;

	/* initialisation des noeuds racines */
	pEntityRoot = NULL;
	pIndexRoot = NULL;
	pNameRoot = NULL;
	pTickRoot = NULL;

	bVector = FALSE;

	bLock = FALSE;
}

INDEXER12::~INDEXER12 ( )
{
	/* destruction du vecteur d'entit�s */
	if ( ppEntity )
	{
		free( ppEntity );
		ppEntity = NULL;
	}

	/* destruction des noeuds racines et tous leurs descendents */
	if ( pEntityRoot )
		Collapse( pEntityRoot );
	if ( pIndexRoot )
		Collapse( pIndexRoot );
	if ( pNameRoot )
		Collapse( pNameRoot );
	if ( pTickRoot )
		Collapse( pTickRoot );
}



VOID INDEXER12::Free ( )
{
	/* v�rouillage */
	if ( bLock == TRUE )
		return;
	else
		bLock = TRUE;

	if ( pIndexRoot )
		Collapse( pIndexRoot );
	if ( pNameRoot )
		Collapse( pNameRoot );

	pIndexRoot = NULL;
	pNameRoot = NULL;

	if ( pTickRoot )
		Free( pTickRoot );

	/* d�v�rouillage */
	bLock = FALSE;

	delete this;
}
