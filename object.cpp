
#include "object.h"
#include "scene.h"
#include "render.h"
#include "indexer.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



OBJECT12::OBJECT12 ( RENDER12* _pRender ) : ENTITY12( _pRender->iObject, _pRender->pEngine )
{
	bComplex = FALSE;

	pRender = _pRender;

	pShader = NULL;

	iChild = new INDEXER12(pLog);

	iTexture = new INDEXER12(pLog);

	dwPhase = 0;

	pLightMap = NULL;
	pCubeMap = NULL;

	pParent = NULL;

	pScene = NULL;

	pStageState = NULL;

	pHitbox = new HITBOX12( pRender, this );

	vCenter = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	vAngle = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	vSize = D3DXVECTOR3( 1.0f, 1.0f, 1.0f );

	D3DXMatrixIdentity( &matCenter );
	D3DXMatrixIdentity( &matAngle );
	D3DXMatrixIdentity( &matSize );
	D3DXMatrixIdentity( &matObject );
	
	pGeometry = NULL;
	dwFaceStart = 0L;
	dwFaceCount = 0L;

	bHitbox = FALSE;
	bMatrix = FALSE;

	bVisible = TRUE;

	bWireframe = FALSE;
	bLighting = FALSE;

	dwFrameCounter = 0;
	dwTotalCounter = 0;

	pMaterial = NULL;
}



OBJECT12::~OBJECT12 ( )
{
	if ( pMaterial )
		delete pMaterial;

	delete iChild;

	delete iTexture;
}



VOID OBJECT12::Copy ( OBJECT12* pObject, BOOLEAN bCopyGeometry, BOOLEAN bCopyTexture )
{
	/* copie des objets enfants */
	ENTITY12 **ppEntity, **ppEnd;
	iChild->Vector( ppEntity, ppEnd );
	while ( ppEntity < ppEnd )
	{
		OBJECT12* pChild = (OBJECT12*)*ppEntity;
		pObject->AddChild( pChild->Copy( bCopyGeometry, bCopyTexture ) );
		ppEntity++;
	}

	/* copie de la texture */
	//if ( bCopyTexture )
	//	pObject->pTexture = pTexture->Copy();
	//else
	//	pObject->pTexture = pTexture;

	/* copie des liens */
	pObject->pParent = pParent;
	pObject->pScene = pScene;

	/* copie des propriétés spatiales */
	pObject->vCenter = vCenter;
	pObject->vAngle = vAngle;
	pObject->vSize = vSize;

	/* copie de la géométrie */
	if ( bCopyGeometry )
		pObject->pGeometry = pGeometry->Copy();
	else
		pObject->pGeometry = pGeometry;

	// faudrait vraiment virer ces trucs, à un objet devrait correspondre une unique géométrie...
	pObject->dwFaceStart = dwFaceStart;
	pObject->dwFaceCount = dwFaceCount;

	/* copie des paramètres de rendu */
	pObject->bWireframe = bWireframe;
	pObject->bLighting = bLighting;

	/* copie de la phase */
	pObject->dwPhase = dwPhase;
}

OBJECT12* OBJECT12::Copy( BOOLEAN bCopyGeometry, BOOLEAN bCopyTexture )
{
	/* création de l'objet */
	OBJECT12* pObject = new OBJECT12( pRender );

	/* copie du contenu commun */
	OBJECT12::Copy( pObject, bCopyGeometry, bCopyTexture );

	return pObject;
}



INDEXER12* OBJECT12::ChildIndexer ( )
{
	return iChild;
}
