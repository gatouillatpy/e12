
#include "complex.h"
#include "scene.h"
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



COMPLEX12::COMPLEX12 ( RENDER12* _pRender ) : OBJECT12( _pRender )
{
	// faut vérifier si cette ligne est bien appelé après
	bComplex = TRUE;

	pA = NULL;
	pB = NULL;
}



COMPLEX12* COMPLEX12::Copy( BOOLEAN bCopyGeometry, BOOLEAN bCopyTexture )
{
	/* création de l'objet */
	COMPLEX12* pObject = new COMPLEX12( pRender );

	/* copie du contenu commun */
	OBJECT12::Copy( pObject, bCopyGeometry, bCopyTexture );

	/* copie des opérandes */
	pObject->SetA( pA->Copy( bCopyGeometry, bCopyTexture ) );
	pObject->SetB( pB->Copy( bCopyGeometry, bCopyTexture ) );

	/* copie de l'opération */
	pObject->dwOperation = dwOperation;

	return pObject;
}
