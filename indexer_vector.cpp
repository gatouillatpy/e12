
#include "impulse.h"
#include "indexer.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID INDEXER12::FillVector ( NODE12* _pNode, DWORD & k )
{
	if ( _pNode->pA )
		FillVector( _pNode->pA, k );

	ppEntity[k++] = _pNode->pEntity;

	if ( _pNode->pB )
		FillVector( _pNode->pB, k );
}



VOID INDEXER12::UpdateVector ( )
{
	/* destruction du vecteur d'entités */
	if ( ppEntity )
	{
		free( ppEntity );
		ppEntity = NULL;
	}

	/* s'il n'y a rien dans l'arbre alors on sort */
	if ( dwCount == 0 )
		return;

	/* réallocation de la mémoire */
	ppEntity = (ENTITY12**) malloc( dwCount * sizeof(LPVOID) );

	/* remplissage du vecteur de manière récursive */
	DWORD k = 0;
	FillVector( pTickRoot, k );

	bVector = TRUE;
}



VOID INDEXER12::Vector ( ENTITY12** & ppStart, ENTITY12** & ppStop )
{
	if ( bVector == FALSE )
		UpdateVector();

	ppStart = ppEntity;
	ppStop = ppEntity + dwCount;
}



ENTITY12* INDEXER12::operator[] ( DWORD k )
{
	if ( bVector == FALSE )
		UpdateVector();

	if ( k < dwCount )
		return ppEntity[k];
	else
		return NULL;
}
