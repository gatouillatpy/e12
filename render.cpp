
#include "render.h"
#include "engine.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



RENDER12::RENDER12 ( ENGINE12* _pEngine ) : ENTITY12( _pEngine->iRender, _pEngine )
{
	/* attribution des valeurs par défaut aux paramètres */
	bWindowMode = TRUE;
	nScreenWidth = 640;
	nScreenHeight = 480;
	bVSync = TRUE;
	bHardware = TRUE;
	nDraftWidth = 160;
	nDraftHeight = 120;
	dwDraftFlags = DRAFT_FULL;
	bShowDraft = FALSE;
	nMaxLightmapMemory = 64;
	nMaxLightmapResolution = 2048;
	nMinLightmapResolution = 16;
	nMaxCubemapMemory = 64;
	nMaxCubemapResolution = 1024;
	nMinCubemapResolution = 8;
	sShaderPath = new CHAR[256];
	StringCopy( sShaderPath, 256, "..\\data\\" );

	iCamera = new INDEXER12(pLog);
	iControl = new INDEXER12(pLog);
	iInterface = new INDEXER12(pLog);
	iObject = new INDEXER12(pLog);
	iScene = new INDEXER12(pLog);
	iGeometry = new INDEXER12(pLog);
	iHitbox = new INDEXER12(pLog);
	iTexture = new INDEXER12(pLog);
	iFont = new INDEXER12(pLog);
	iShader = new INDEXER12(pLog);

	iAnimation = new INDEXER12(pLog);

	dwBackColor = 0x00000000;

	dwPhaseCount = 1;
	dwPhase = 0;

	bWireframe = FALSE;

	lpD3D = NULL;
	lpD3DDevice = NULL;

	lpDraftQuery = NULL;
	lpDraftTexture = NULL;
	lpDraftBuffer = NULL;
	lpDraftSurface = NULL;

	lpRenderTexture = NULL;
	lpRenderBuffer = NULL;
	lpRenderSurface = NULL;

	lpBackBuffer = NULL;
	lpDepthBuffer = NULL;

	lpSpriteVB = NULL;

	lpSpaceTexture = NULL;
	lpSpaceBuffer = NULL;

	lpLightTexture = NULL;
	lpLightBuffer = NULL;

	lpRayTexture = NULL;
	lpRayBuffer = NULL;

	lpRayPS = NULL;
	lpRayVS = NULL;
	lpRayVD = NULL;
	lpRayVB = NULL;
	lpRayIB = NULL;

	lpHitboxPS = NULL;
	lpHitboxVS = NULL;
	lpHitboxVD = NULL;
	lpHitboxVB = NULL;
	lpHitboxIB = NULL;

	lpBufferPS = NULL;
	lpBufferVS = NULL;
	lpBufferVD = NULL;
	lpBufferVB = NULL;
	lpBufferIB = NULL;

	lpFinalShader = NULL;
	lpSurfaceShader = NULL;
	lpCylinderShader = NULL;

	ppLightmapTexture = NULL;

	ppCubemapTexture = NULL;

	lpComplexTexture = NULL;
	lpComplexColor = NULL;
	lpComplexDepth = NULL;

	pColorShader = NULL;
	pTextureShader = NULL;
	pMaskShader = NULL;
	pCharShader = NULL;

	pFocus = NULL;
}

RENDER12::~RENDER12 ( )
{
	delete sShaderPath;

	iCamera->Free();
	iControl->Free();
	iInterface->Free();
	iObject->Free();
	iScene->Free();
	iGeometry->Free();
	iHitbox->Free();
	iTexture->Free();
	iFont->Free();
	iShader->Free();

	delete iAnimation;

	if ( ppLightmapTexture )
	{
		for ( DWORD i = 0L ; i < dwLightmapCount ; i++ )
		{
			if ( ppLightmapTexture[i] ) 
				ppLightmapTexture[i]->Release();
		}
		delete [] ppLightmapTexture;
	}

	if ( ppCubemapTexture )
	{
		for ( DWORD i = 0L ; i < dwCubemapCount ; i++ )
		{
			if ( ppCubemapTexture[i] ) 
				ppCubemapTexture[i]->Release();
		}
		delete [] ppCubemapTexture;
	}

	if ( lpRayTexture )
		lpRayTexture->Release();
	if ( lpRayBuffer )
		lpRayBuffer->Release();

	if ( lpSpaceTexture )
		lpSpaceTexture->Release();
	if ( lpSpaceBuffer )
		lpSpaceBuffer->Release();

	if ( lpLightTexture )
		lpLightTexture->Release();
	if ( lpLightBuffer )
		lpLightBuffer->Release();

	if ( lpSpriteVB )
		lpSpriteVB->Release();

	if ( lpRenderTexture )
		lpRenderTexture->Release();
	if ( lpRenderBuffer )
		lpRenderBuffer->Release();
	if ( lpRenderSurface )
		lpRenderSurface->Release();

	if ( lpDraftQuery )
		lpDraftQuery->Release();
	if ( lpDraftTexture )
		lpDraftTexture->Release();
	if ( lpDraftBuffer )
		lpDraftBuffer->Release();
	if ( lpDraftSurface )
		lpDraftSurface->Release();

	if ( lpBackBuffer )
		lpBackBuffer->Release();
	if ( lpDepthBuffer )
		lpDepthBuffer->Release();

	if ( lpRayPS )
		lpRayPS->Release();
	if ( lpRayVS )
		lpRayVS->Release();
	if ( lpRayVD )
		lpRayVD->Release();
	if ( lpRayVB )
		lpRayVB->Release();
	if ( lpRayIB )
		lpRayIB->Release();

	if ( lpHitboxPS )
		lpHitboxPS->Release();
	if ( lpHitboxVS )
		lpHitboxVS->Release();
	if ( lpHitboxVD )
		lpHitboxVD->Release();
	if ( lpHitboxVB )
		lpHitboxVB->Release();
	if ( lpHitboxIB )
		lpHitboxIB->Release();

	if ( lpBufferPS )
		lpBufferPS->Release();
	if ( lpBufferVS )
		lpBufferVS->Release();
	if ( lpBufferVD )
		lpBufferVD->Release();
	if ( lpBufferVB )
		lpBufferVB->Release();
	if ( lpBufferIB )
		lpBufferIB->Release();

	if ( lpComplexTexture )
		lpComplexTexture->Release();
	if ( lpComplexColor )
		lpComplexColor->Release();
	if ( lpComplexDepth )
		lpComplexDepth->Release();

	if ( pMaterial )
		delete pMaterial;

	free( ppPhaseBuffer );

	if ( lpD3DDevice )
		lpD3DDevice->Release();
	if ( lpD3D )
		lpD3D->Release();
}
