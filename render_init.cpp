
#include "render.h"
#include "log.h"
#include "impulse.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



BOOLEAN RENDER12::InitDirect3D ( WINDOW12* _pWindow )
{
	/* on génère une erreur si aucune fenêtre valide n'est passée en paramètre */
	if ( _pWindow == NULL )
	{
		pLog->Push( __FILE__, __LINE__, CODE_CRASH, CODE_RENDER12, 0x0001, this, _pWindow, NULL ); return 0;
	}

	/* on sauvegarde de la fenêtre passée en paramètre */
	lpWindow = _pWindow;

	/* on spécifie la resolution d'affichage */
	if ( bWindowMode == TRUE )
	{
		nWidth = _pWindow->ClientWidth();
		nHeight = _pWindow->ClientHeight();
	}
	else
	{
		nWidth = nScreenWidth;
		nHeight = nScreenHeight;
	}

	/* on initialise Direct3D */
	if ( ( lpD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) == NULL )
	{
		pLog->Push( __FILE__, __LINE__, CODE_CRASH, CODE_RENDER12, 0x0002, this, NULL, NULL ); return 0;
	}

	/* on vérifie la compatibilité du matériel avec le format de depth/stencil buffer désiré */
	if( FAILED( lpD3D->CheckDeviceFormat( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3DFMT_X8R8G8B8, D3DUSAGE_DEPTHSTENCIL,
		D3DRTYPE_SURFACE, D3DFMT_D24S8 ) ) )
	{
		if( FAILED( lpD3D->CheckDepthStencilMatch( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3DFMT_X8R8G8B8, D3DFMT_A8R8G8B8, D3DFMT_D24S8 ) ) )
		{
			pLog->Push( __FILE__, __LINE__, CODE_CRASH, CODE_RENDER12, 0x0003, this, NULL, "D24S8" ); return 0;
		}
	}

	/* on vérifie la compatibilité avec la version des shaders requise */
	D3DCAPS9 d3dCaps;
	lpD3D->GetDeviceCaps( 0, D3DDEVTYPE_HAL, &d3dCaps );
	if ( d3dCaps.VertexShaderVersion < D3DVS_VERSION(3,0) )
	{
		pLog->Push( __FILE__, __LINE__, CODE_CRASH, CODE_RENDER12, 0x0004, this, NULL, "3.0" ); return 0;
	}
	if ( d3dCaps.PixelShaderVersion < D3DPS_VERSION(3,0) )
	{
		pLog->Push( __FILE__, __LINE__, CODE_CRASH, CODE_RENDER12, 0x0005, this, NULL, "3.0" ); return 0;
	}

	/* on définit les paramètres */
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory( &d3dpp, sizeof(d3dpp) );
	d3dpp.Windowed						= bWindowMode;
	d3dpp.SwapEffect					= D3DSWAPEFFECT_COPY;
	d3dpp.BackBufferFormat				= D3DFMT_X8R8G8B8;
	d3dpp.BackBufferWidth				= nWidth;
	d3dpp.BackBufferHeight				= nHeight;
	d3dpp.EnableAutoDepthStencil		= TRUE;
	d3dpp.AutoDepthStencilFormat		= D3DFMT_D24S8;
	d3dpp.FullScreen_RefreshRateInHz	= 0;
	d3dpp.PresentationInterval			= bVSync ? D3DPRESENT_INTERVAL_ONE : D3DPRESENT_INTERVAL_IMMEDIATE;

	/* on initialise le device Direct3D */
#ifndef DEBUG_SHADER
	lpD3D->CreateDevice( D3DADAPTER_DEFAULT, bHardware ? D3DDEVTYPE_HAL : D3DDEVTYPE_REF,
		lpWindow->hWnd, bHardware ? D3DCREATE_HARDWARE_VERTEXPROCESSING : D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &lpD3DDevice );
#else
	lpD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, lpWindow->hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &lpD3DDevice );
#endif

	/* on récupère le back et le depth/stencil buffer afin de faciliter les échanges */
	lpD3DDevice->GetRenderTarget( 0, &lpBackBuffer );
	lpD3DDevice->GetDepthStencilSurface( &lpDepthBuffer );

	return 1;
}



BOOLEAN RENDER12::InitComplex ( )
{
	lpD3DDevice->CreateTexture( nWidth, nHeight, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT, &lpComplexTexture, NULL );

	lpComplexTexture->GetSurfaceLevel( 0, &lpComplexColor );

	lpD3DDevice->CreateDepthStencilSurface( nWidth, nHeight, D3DFMT_D24S8, D3DMULTISAMPLE_NONE,
		0, FALSE, &lpComplexDepth, NULL );

	return 1;
}


	
BOOLEAN RENDER12::InitRender ( )
{
	lpD3DDevice->CreateTexture( nWidth, nHeight, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT, &lpRenderTexture, NULL );

	lpRenderTexture->GetSurfaceLevel( 0, &lpRenderBuffer );

	lpD3DDevice->CreateOffscreenPlainSurface( nWidth, nHeight, D3DFMT_A8R8G8B8,
		D3DPOOL_SYSTEMMEM, &lpRenderSurface, NULL );

	return 1;
}



BOOLEAN RENDER12::InitDraftSystem ( )
{
	lpD3DDevice->CreateQuery( D3DQUERYTYPE_OCCLUSION, &lpDraftQuery );

	lpD3DDevice->CreateTexture( nDraftWidth, nDraftHeight, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT, &lpDraftTexture, NULL );

	lpDraftTexture->GetSurfaceLevel( 0, &lpDraftBuffer );

	lpD3DDevice->CreateOffscreenPlainSurface( nDraftWidth, nDraftHeight, D3DFMT_A8R8G8B8,
		D3DPOOL_SYSTEMMEM, &lpDraftSurface, NULL );

	return 1;
}



BOOLEAN RENDER12::InitHitbox ( )
{
	// création des vertex et index buffers de la hitbox

	LPVOID pData = NULL;

	FLOAT aHitboxVertices[] = { -0.5f, -0.5f, -0.5f,
		-0.5f, +0.5f, -0.5f,
		+0.5f, +0.5f, -0.5f,
		+0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, +0.5f,
		+0.5f, -0.5f, +0.5f,
		+0.5f, +0.5f, +0.5f,
		-0.5f, +0.5f, +0.5f	};

	if ( lpHitboxVB )
		lpHitboxVB->Release();

	lpD3DDevice->CreateVertexBuffer( sizeof(aHitboxVertices), D3DUSAGE_WRITEONLY, D3DFVF_XYZ, D3DPOOL_DEFAULT,
		&lpHitboxVB, NULL );

	lpHitboxVB->Lock( 0, sizeof(aHitboxVertices), (LPVOID*)&pData, 0 );
	CopyMemory( pData, aHitboxVertices, sizeof(aHitboxVertices) );
	lpHitboxVB->Unlock();

	WORD aHitboxIndices[] = { 0, 1, 2, 2, 3, 0, 4, 5, 6,
		6, 7, 4, 0, 3, 5, 5, 4, 0,
		3, 2, 6, 6, 5, 3, 2, 1, 7,
		7, 6, 2, 1, 0, 4, 4, 7, 1 };

	if ( lpHitboxIB )
		lpHitboxIB->Release();

	lpD3DDevice->CreateIndexBuffer( sizeof(aHitboxIndices), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_DEFAULT,
		&lpHitboxIB, NULL );

	lpHitboxIB->Lock( 0, sizeof(aHitboxIndices), (LPVOID*)&pData, 0 );
	CopyMemory( pData, aHitboxIndices, sizeof(aHitboxIndices) );
	lpHitboxIB->Unlock();

	// création du vertex shader de la hitbox

	LPD3DXBUFFER pCode = NULL;

	D3DVERTEXELEMENT9 aHitboxDeclaration[] = 
	{
		{ 0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		D3DDECL_END()
	};

	lpD3DDevice->CreateVertexDeclaration( aHitboxDeclaration, &lpHitboxVD );

	const CHAR sHitboxVertexShader[] =
		"vs_1_1 \n"\
		\
		"dcl_position v0 \n"\
		\
		"m4x4 oPos, v0, c0 \n";
	D3DXAssembleShader( sHitboxVertexShader, strlen(sHitboxVertexShader), NULL, NULL, NULL,
		&pCode, NULL );

	lpD3DDevice->CreateVertexShader( (DWORD*)pCode->GetBufferPointer(), &lpHitboxVS );

	if( pCode )
	{
		pCode->Release(); 
		pCode = NULL; 
	}

	const CHAR sHitboxPixelShader[] = 
		"ps_1_1 \n"\
		\
		"mov r0, c0 \n";
	D3DXAssembleShader( sHitboxPixelShader, strlen(sHitboxPixelShader), NULL, NULL, NULL,
		&pCode, NULL );

	lpD3DDevice->CreatePixelShader( (DWORD*)pCode->GetBufferPointer(), &lpHitboxPS );

	if( pCode )
	{
		pCode->Release(); 
		pCode = NULL; 
	}

	return 1;
}



BOOLEAN RENDER12::InitBuffer ( )
{
	// création des vertex et index buffers de la surface

	LPVOID pData = NULL;

	FLOAT aBufferVertices[] =
	{ -1.0f, -1.0f, 0.0f, 0.0f, 1.0f,
	+1.0f, -1.0f, 0.0f, 1.0f, 1.0f,
	-1.0f, +1.0f, 0.0f, 0.0f, 0.0f,
	+1.0f, +1.0f, 0.0f, 1.0f, 0.0f };

	if ( lpBufferVB ) lpBufferVB->Release();

	lpD3DDevice->CreateVertexBuffer( sizeof(aBufferVertices), D3DUSAGE_WRITEONLY, D3DFVF_XYZ | D3DFVF_TEX1,
		D3DPOOL_DEFAULT, &lpBufferVB, NULL );

	lpBufferVB->Lock( 0, sizeof(aBufferVertices), (LPVOID*)&pData, 0 );
	CopyMemory( pData, aBufferVertices, sizeof(aBufferVertices) );
	lpBufferVB->Unlock();

	WORD aBufferIndices[] = { 0, 1, 2, 3, 2, 1 };

	if ( lpBufferIB ) lpBufferIB->Release();

	lpD3DDevice->CreateIndexBuffer( sizeof(aBufferIndices), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_DEFAULT,
		&lpBufferIB, NULL );

	lpBufferIB->Lock( 0, sizeof(aBufferIndices), (LPVOID*)&pData, 0 );
	CopyMemory( pData, aBufferIndices, sizeof(aBufferIndices) );
	lpBufferIB->Unlock();

	// création des vertex et pixel shaders de la surface

	LPD3DXBUFFER pCode = NULL;

	D3DVERTEXELEMENT9 aBufferDeclaration[] = 
	{
		{ 0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 12, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
		D3DDECL_END()
	};

	lpD3DDevice->CreateVertexDeclaration( aBufferDeclaration, &lpBufferVD );

	const CHAR sBufferVertexShader[] =
		"vs_1_1 \n"\
		\
		"dcl_position v0 \n"\
		"dcl_texcoord v1 \n"\
		\
		"mov oPos, v0 \n"\
		"mov oT0, v1 \n";
	D3DXAssembleShader( sBufferVertexShader, strlen(sBufferVertexShader), NULL, NULL, NULL,
		&pCode, NULL );

	lpD3DDevice->CreateVertexShader( (DWORD*)pCode->GetBufferPointer(), &lpBufferVS );

	if( pCode )
	{
		pCode->Release(); 
		pCode = NULL; 
	}

	const CHAR sBufferPixelShader[] = 
		"ps_1_1 \n"\
		\
		"tex t0 \n"\
		"mov r0, t0 \n";
	D3DXAssembleShader( sBufferPixelShader, strlen(sBufferPixelShader), NULL, NULL, NULL,
		&pCode, NULL );

	lpD3DDevice->CreatePixelShader( (DWORD*)pCode->GetBufferPointer(), &lpBufferPS );

	if( pCode )
	{
		pCode->Release(); 
		pCode = NULL; 
	}

	return 1;
}



BOOLEAN RENDER12::InitRay ( )
{
	// création des surfaces de stockage des rayons projetés

	lpD3DDevice->CreateTexture( nWidth, nHeight, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A32B32G32R32F,
		D3DPOOL_DEFAULT, &lpRayTexture, NULL );

	lpRayTexture->GetSurfaceLevel( 0, &lpRayBuffer );

	// création des vertex et index buffers de la surface de projection des rayons

	LPVOID pData = NULL;

	FLOAT aRayVertices[] = { -1.0f, -1.0f, 0.0f,
		+1.0f, -1.0f, 0.0f,
		-1.0f, +1.0f, 0.0f,
		+1.0f, +1.0f, 0.0f };

	if ( lpRayVB ) lpRayVB->Release();

	lpD3DDevice->CreateVertexBuffer( sizeof(aRayVertices), D3DUSAGE_WRITEONLY, D3DFVF_XYZ,
		D3DPOOL_DEFAULT, &lpRayVB, NULL );

	lpRayVB->Lock( 0, sizeof(aRayVertices), (LPVOID*)&pData, 0 );
	CopyMemory( pData, aRayVertices, sizeof(aRayVertices) );
	lpRayVB->Unlock();

	WORD aRayIndices[] = { 0, 1, 2, 3, 2, 1 };

	if ( lpRayIB ) lpRayIB->Release();

	lpD3DDevice->CreateIndexBuffer( sizeof(aRayIndices), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_DEFAULT,
		&lpRayIB, NULL );

	lpRayIB->Lock( 0, sizeof(aRayIndices), (LPVOID*)&pData, 0 );
	CopyMemory( pData, aRayIndices, sizeof(aRayIndices) );
	lpRayIB->Unlock();

	// création des vertex et pixel shaders de projection de rayons

	LPD3DXBUFFER pCode = NULL;

	D3DVERTEXELEMENT9 aRayDeclaration[] = 
	{
		{ 0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		D3DDECL_END()
	};

	lpD3DDevice->CreateVertexDeclaration( aRayDeclaration, &lpRayVD );

	const CHAR sRayVertexShader[] =
		"vs_3_0 \n"\
		\
		"dcl_position v0 \n"\
		"dcl_position o0 \n"\
		\
		"mov o0, v0 \n";
	D3DXAssembleShader( sRayVertexShader, strlen(sRayVertexShader), NULL, NULL, NULL,
		&pCode, NULL );

	lpD3DDevice->CreateVertexShader( (DWORD*)pCode->GetBufferPointer(), &lpRayVS );

	if( pCode )
	{
		pCode->Release(); 
		pCode = NULL; 
	}

	// c0 = vRayDir
	// c1 = vRayX
	// c2 = vRayY
	const CHAR sRayPixelShader[] = 
		"ps_3_0 \n"\
		\
		"dcl vPos.xy \n"\
		\
		"mov r0, c0 \n"\
		\
		"mad r0, vPos.x, -c1, r0 \n"\
		"mad r0, vPos.y, -c2, r0 \n"\
		\
		"nrm oC0, r0 \n";
	D3DXAssembleShader( sRayPixelShader, strlen(sRayPixelShader), NULL, NULL, NULL,
		&pCode, NULL );

	lpD3DDevice->CreatePixelShader( (DWORD*)pCode->GetBufferPointer(), &lpRayPS );

	if( pCode )
	{
		pCode->Release(); 
		pCode = NULL; 
	}

	return 1;
}



BOOLEAN RENDER12::InitLightmap ( )
{
	// allocation de la mémoire pour les lightmaps

	UINT nMemory = nMaxLightmapMemory * 1024 * 1024;
	UINT nResolution = nMaxLightmapResolution;
	DWORD dwCount = 1;
	dwLightmapCount = 0;
	while ( nMemory > 0 && nResolution >= nMinLightmapResolution )
	{
		for ( DWORD k = 0 ; k < dwCount ; k++ )
		{
			nMemory -= nResolution * nResolution * 4;
			if ( nMemory < 0 )
				break;

			ppLightmapTexture = (LPDIRECT3DTEXTURE9*)realloc(ppLightmapTexture, ++dwLightmapCount * sizeof(LPDIRECT3DTEXTURE9));

			lpD3DDevice->CreateTexture( nResolution, nResolution, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8,
				D3DPOOL_DEFAULT, &ppLightmapTexture[dwLightmapCount-1], NULL );
		}
		dwCount *= 2;
		nResolution /= 2;
	}

	return 1;
}



BOOLEAN RENDER12::InitCubemap ( )
{
	// allocation de la mémoire pour les cubemaps

	UINT nMemory = nMaxCubemapMemory * 1024 * 1024;
	UINT nResolution = nMaxCubemapResolution;
	DWORD dwCount = 1;
	dwCubemapCount = 0;
	while ( nMemory > 0 && nResolution >= nMinCubemapResolution )
	{
		for ( DWORD k = 0 ; k < dwCount ; k++ )
		{
			nMemory -= nResolution * nResolution * 4 * 6;
			if ( nMemory < 0 )
				break;

			ppCubemapTexture = (LPDIRECT3DCUBETEXTURE9*)realloc(ppCubemapTexture, ++dwCubemapCount * sizeof(LPDIRECT3DCUBETEXTURE9));

			lpD3DDevice->CreateCubeTexture( nResolution, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8,
				D3DPOOL_DEFAULT, &ppCubemapTexture[dwCubemapCount-1], NULL );
		}
		dwCount *= 2;
		nResolution /= 2;
	}

	return 1;
}



BOOLEAN RENDER12::Initialize ( WINDOW12* _pWindow )
{
	if ( InitDirect3D( _pWindow ) == 0 )
		return 0;

	if ( InitComplex() == 0 )
		return 0;

	if ( InitRender() == 0 )
		return 0;

	if ( InitDraftSystem() == 0 )
		return 0;

	if ( InitHitbox() == 0 )
		return 0;

	// TEMPORAIRE ???
	if ( InitBuffer() == 0 )
		return 0;

	if ( InitRay() == 0 )
		return 0;

	if ( InitLightmap() == 0 )
		return 0;

	if ( InitCubemap() == 0 )
		return 0;

	// TEMPORAIRE ???
	{
		// création des surfaces de stockage de l'espace

		lpD3DDevice->CreateTexture( nWidth, nHeight, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A32B32G32R32F,
			D3DPOOL_DEFAULT, &lpSpaceTexture, NULL );

		lpSpaceTexture->GetSurfaceLevel( 0, &lpSpaceBuffer );

		// création des surfaces de stockage de la lumière

		lpD3DDevice->CreateTexture( 256, 256, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A32B32G32R32F,
			D3DPOOL_DEFAULT, &lpLightTexture, NULL );

		lpLightTexture->GetSurfaceLevel( 0, &lpLightBuffer );
	}

	// définition des renderstates par défaut

	lpD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );
	lpD3DDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );
	lpD3DDevice->SetRenderState( D3DRS_COLORVERTEX, FALSE );
	lpD3DDevice->SetRenderState( D3DRS_LIGHTING, FALSE );

	// supression du curseur

	lpD3DDevice->ShowCursor( FALSE );

	// chargement du shader de rendu final

	lpFinalShader = new SHADER12( this );

/*
#ifndef DEBUG_SHADER
	lpFinalShader->Load( "..\\data\\final.s12" );
#else
	lpFinalShader->CompileVSFile( "..\\engine\\final.vsh", "vs_3_sw", "VS_Default" );
	lpFinalShader->CompilePSFile( "..\\engine\\final.psh", "ps_3_sw", "PS_Default" );
#endif
*/

	pMaterial = new D3DMATERIAL9;
	pMaterial->Ambient = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	pMaterial->Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	pMaterial->Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	pMaterial->Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pMaterial->Power = 10.0f;

	pColorShader = new SHADER12( this );
	pColorShader->CompileVSFile( StringPath( sShaderPath, "color.vsh" ), "vs_1_1", "VS_Default" );
	pColorShader->CompilePSFile( StringPath( sShaderPath, "color.psh" ), "ps_2_0", "PS_Default" );

	pTextureShader = new SHADER12( this );
	pTextureShader->CompileVSFile( StringPath( sShaderPath, "texture.vsh" ), "vs_1_1", "VS_Default" );
	pTextureShader->CompilePSFile( StringPath( sShaderPath, "texture.psh" ), "ps_2_0", "PS_Default" );

	pMaskShader = new SHADER12( this );
	pMaskShader->CompileVSFile( StringPath( sShaderPath, "mask.vsh" ), "vs_1_1", "VS_Default" );
	pMaskShader->CompilePSFile( StringPath( sShaderPath, "mask.psh" ), "ps_2_0", "PS_Default" );

	pCharShader = new SHADER12( this );
	pCharShader->CompileVSFile( StringPath( sShaderPath, "char.vsh" ), "vs_1_1", "VS_Default" );
	pCharShader->CompilePSFile( StringPath( sShaderPath, "char.psh" ), "ps_2_0", "PS_Default" );

	ppPhaseBuffer = (BUFFER12**)malloc( 256 * sizeof(BUFFER12*) );
	ppPhaseBuffer[0] = new BUFFER12( this );
	ppPhaseBuffer[0]->Generate( nWidth, nHeight );
	ppPhaseBuffer[0]->SetIndex( TEXTURE_PHASE(0) );

	return S_OK;
}



VOID RENDER12::Terminate( )
{
}
