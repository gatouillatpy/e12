
#include "object.h"
#include "scene.h"
#include "render.h"
#include "indexer.h"
#include "engine.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



BOOLEAN	OBJECT12::Intersect ( D3DXVECTOR3 & _vRayPos, D3DXVECTOR3 & _vRayDir )
{
	return pHitbox->Intersect( _vRayPos, _vRayDir );
}



VOID OBJECT12::UpdateHitbox ( )
{
	pHitbox->Reset();

	if ( pGeometry )
		pHitbox->Setup( pGeometry->Min(), pGeometry->Max(), Matrix() );

	ENTITY12 **ppEntity, **ppEnd;
	iChild->Vector( ppEntity, ppEnd );
	while ( ppEntity < ppEnd )
	{
		OBJECT12* pObject = (OBJECT12*)*ppEntity;
		pHitbox->Merge( pObject->Hitbox() );
		ppEntity++;
	}

	if ( pParent )
		pParent->bHitbox = FALSE;

	if ( pScene )
		pScene->bHitbox = FALSE;

	bHitbox = TRUE;
}

HITBOX12* OBJECT12::Hitbox ( )
{
	if ( bHitbox == FALSE ) UpdateHitbox();

	return pHitbox;
}



VOID OBJECT12::UpdateMatrix ( )
{
	D3DXMatrixTranslation( &matCenter, vCenter.x, vCenter.y, vCenter.z );
	D3DXMatrixRotationYawPitchRoll( &matAngle, vAngle.y, vAngle.x, vAngle.z );
	D3DXMatrixScaling( &matSize, vSize.x, vSize.y, vSize.z );
	matObject = matSize * matAngle * matCenter;
	if ( pParent ) matObject *= pParent->Matrix();

	bMatrix = TRUE;
}

D3DXMATRIX OBJECT12::Matrix ( )
{
	if ( bMatrix == FALSE ) UpdateMatrix();

	return matObject;
}



VOID OBJECT12::Update ( )
{
	if ( bHitbox == FALSE ) UpdateHitbox();
	if ( bMatrix == FALSE ) UpdateMatrix();

	ENTITY12 **ppEntity, **ppEnd;
	iChild->Vector( ppEntity, ppEnd );
	while ( ppEntity < ppEnd )
	{
		OBJECT12* pObject = (OBJECT12*)*ppEntity;
		if ( pObject->dwPass == dwPass )
			pObject->Update();
		ppEntity++;
	}
}



VOID OBJECT12::SetupTextureStandard ( )
{
	DWORD nStage = 0;

	ENTITY12 **ppEntity, **ppEnd;
	iTexture->Vector( ppEntity, ppEnd );

	while ( ppEntity < ppEnd )
	{
		TEXTURE12* pTexture = (TEXTURE12*)*ppEntity;

		pRender->lpD3DDevice->SetTexture( nStage, pTexture->lpD3DTexture );
		pRender->lpD3DDevice->SetTransform( D3DTS_TEXTURE0, &pTexture->Matrix() );
		pRender->lpD3DDevice->SetTextureStageState( nStage, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2 );

		nStage++;

		ppEntity++;
	}

	for ( ; nStage < 9 ; nStage++ )
	{
		pRender->lpD3DDevice->SetTexture( nStage, NULL );
	}
}



VOID OBJECT12::RenderWired ( CAMERA12* _pCamera )
{
	pRender->lpD3DDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME );
	pRender->lpD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	pRender->lpD3DDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
	pRender->lpD3DDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_ALWAYS );

	D3DXMATRIX matWorld = Matrix() * pScene->Matrix();
	pRender->lpD3DDevice->SetTransform( D3DTS_WORLD, &matWorld );
	pRender->lpD3DDevice->SetTransform( D3DTS_VIEW, &_pCamera->ViewMatrix() );
	pRender->lpD3DDevice->SetTransform( D3DTS_PROJECTION, &_pCamera->ProjMatrix() );

	pRender->lpD3DDevice->SetVertexShader( NULL );
	pRender->lpD3DDevice->SetPixelShader( NULL );

	pRender->lpD3DDevice->SetTexture( 0, NULL );
	pRender->lpD3DDevice->SetTexture( 1, NULL );
	pRender->lpD3DDevice->SetTexture( 2, NULL );
	pRender->lpD3DDevice->SetTexture( 3, NULL );

	/* si le nombre de faces est spécifié alors on affiche qu'une partie de la géométrie */
	if ( dwFaceCount > 0 )
	{
		pGeometry->Render( dwFaceStart, dwFaceCount );
	}
	/* sinon l'affiche intégralement */
	else
	{
		pGeometry->Render();
	}

	pRender->lpD3DDevice->SetRenderState( D3DRS_FILLMODE, D3DFILLMODE_DEFAULT );
	pRender->lpD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULLMODE_DEFAULT );
	pRender->lpD3DDevice->SetRenderState( D3DRS_LIGHTING, D3DLIGHTING_DEFAULT );
	pRender->lpD3DDevice->SetRenderState( D3DRS_ZFUNC, D3DZFUNC_DEFAULT );
}



VOID OBJECT12::RenderSolid ( CAMERA12* _pCamera )
{
	pRender->lpD3DDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );
	pRender->lpD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

	if ( pShader != NULL )
	{
		D3DXMATRIX matWorld = Matrix() * pScene->Matrix();

		if ( pShader->lpSetupCallback != NULL )
		{
			pShader->Setup( &matWorld, &_pCamera->ViewMatrix(), &_pCamera->ProjMatrix() );
		}
		else
		{
			if ( pShader->CheckVSConstant( "matWorld" ) )
			{
				pShader->SetVSMatrix( "matWorld", &matWorld );
			}
			if ( pShader->CheckVSConstant( "matView" ) )
			{
				pShader->SetVSMatrix( "matView", &_pCamera->ViewMatrix() );
			}
			if ( pShader->CheckVSConstant( "matProj" ) )
			{
				pShader->SetVSMatrix( "matProj", &_pCamera->ProjMatrix() );
			}
			if ( pShader->CheckVSConstant( "matWorldView" ) )
			{
				D3DXMATRIX matWorldView = matWorld * _pCamera->ViewMatrix();
				pShader->SetVSMatrix( "matWorldView", &matWorldView );
			}
			if ( pShader->CheckVSConstant( "matViewProj" ) )
			{
				D3DXMATRIX matViewProj = _pCamera->ViewMatrix() * _pCamera->ProjMatrix();
				pShader->SetVSMatrix( "matViewProj", &matViewProj );
			}
			if ( pShader->CheckVSConstant( "matWorldViewProj" ) )
			{
				D3DXMATRIX matWorldViewProj = matWorld * _pCamera->ViewMatrix() * _pCamera->ProjMatrix();
				pShader->SetVSMatrix( "matWorldViewProj", &matWorldViewProj );
			}
			if ( pShader->CheckVSConstant( "fTime" ) )
			{
				pShader->SetVSFloat( "fTime", (FLOAT)pRender->pEngine->GetTime() );
			}
		}

		pRender->lpD3DDevice->SetVertexShader( pShader->lpVertexShader );
		pRender->lpD3DDevice->SetPixelShader( pShader->lpPixelShader );
	}
	else
	{
		D3DXMATRIX matWorld = Matrix() * pScene->Matrix();
		pRender->lpD3DDevice->SetTransform( D3DTS_WORLD, &matWorld );
		pRender->lpD3DDevice->SetTransform( D3DTS_VIEW, &_pCamera->ViewMatrix() );
		pRender->lpD3DDevice->SetTransform( D3DTS_PROJECTION, &_pCamera->ProjMatrix() );

		pRender->lpD3DDevice->SetVertexShader( NULL );
		pRender->lpD3DDevice->SetPixelShader( NULL );

		SetupTextureStandard();

		if ( bLighting )
		{
			pRender->lpD3DDevice->SetRenderState( D3DRS_LIGHTING, TRUE );

			if ( pMaterial )
				pRender->lpD3DDevice->SetMaterial( pMaterial );
			else
				pRender->lpD3DDevice->SetMaterial( pRender->pMaterial );
		}
		else
		{
			pRender->lpD3DDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
		}
	}

	// TEMPORAIRE
	//pRender->SetStageState( 0, pStageState );

	/* si le nombre de faces est spécifié alors on affiche qu'une partie de la géométrie */
	if ( dwFaceCount > 0 )
	{
		pGeometry->Render( dwFaceStart, dwFaceCount );
	}
	/* sinon l'affiche intégralement */
	else
	{
		pGeometry->Render();
	}

	pRender->lpD3DDevice->SetRenderState( D3DRS_FILLMODE, D3DFILLMODE_DEFAULT );
	pRender->lpD3DDevice->SetRenderState( D3DRS_LIGHTING, D3DLIGHTING_DEFAULT );
	pRender->lpD3DDevice->SetTextureStageState( 0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE );
}



VOID OBJECT12::Render ( CAMERA12* _pCamera )
{
	/* si l'objet est invisible alors on ne l'affiche pas */
	if ( bVisible == FALSE ) return;

	/* si la phase de l'objet à rendre ne correspond pas à celle du rendu alors on ne l'affiche pas */
	if ( dwPhase != pRender->dwPhase ) return;

	/* on procède à l'affichage de la géométrie de l'objet s'il en a une */
	if ( pGeometry != NULL )
	{
		/* on définit le style de remplissage */
		if ( bWireframe || pRender->bWireframe )
			RenderWired( _pCamera );
		else
			RenderSolid( _pCamera );

		/* on rétablit les render states potentiellement modifiés pour leur valeur par défaut */
		pRender->lpD3DDevice->SetRenderState( D3DRS_LIGHTING, D3DLIGHTING_DEFAULT );
		pRender->lpD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULLMODE_DEFAULT );
		pRender->lpD3DDevice->SetRenderState( D3DRS_FILLMODE, D3DFILLMODE_DEFAULT );
		pRender->lpD3DDevice->SetRenderState( D3DRS_STENCILENABLE, FALSE );
		pRender->lpD3DDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_LESSEQUAL );
	}

	/* on rend enfin les objets enfant s'ils existent */
	ENTITY12 **ppEntity, **ppEnd;
	iChild->Vector( ppEntity, ppEnd );
	while ( ppEntity < ppEnd )
	{
		OBJECT12* pChild = (OBJECT12*)*ppEntity;
		pChild->Render( _pCamera );
		ppEntity++;
	}
}



VOID OBJECT12::Render ( CAMERA12* _pCamera, DWORD _dwPass )
{
	/* si l'objet est invisible alors on ne l'affiche pas */
	if ( bVisible == FALSE ) return;

	/* si la phase de l'objet à rendre ne correspond pas à celle du rendu alors on ne l'affiche pas */
	if ( dwPhase != pRender->dwPhase ) return;

	/* on procède à l'affichage de la géométrie de l'objet s'il en a une */
	if ( pGeometry != NULL )
	{
		/* on définit le style de remplissage */
		if ( bWireframe || pRender->bWireframe )
			RenderWired( _pCamera );
		else
			RenderSolid( _pCamera );

		/* on rétablit les render states potentiellement modifiés pour leur valeur par défaut */
		pRender->lpD3DDevice->SetRenderState( D3DRS_LIGHTING, D3DLIGHTING_DEFAULT );
		pRender->lpD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULLMODE_DEFAULT );
		pRender->lpD3DDevice->SetRenderState( D3DRS_FILLMODE, D3DFILLMODE_DEFAULT );
		pRender->lpD3DDevice->SetRenderState( D3DRS_STENCILENABLE, FALSE );
		pRender->lpD3DDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_LESSEQUAL );
	}

	/* on rend enfin les objets enfant s'ils existent */
	ENTITY12 **ppEntity, **ppEnd;
	iChild->Vector( ppEntity, ppEnd );
	while ( ppEntity < ppEnd )
	{
		OBJECT12* pChild = (OBJECT12*)*ppEntity;
		if ( pChild->dwPass == _dwPass )
			pChild->Render( _pCamera );
		ppEntity++;
	}
}



VOID OBJECT12::Draft ( CAMERA12* _pCamera, DWORD _dwPass )
{
	LPDIRECT3DQUERY9 lpQuery = pRender->lpDraftQuery;

	lpQuery->Issue( D3DISSUE_BEGIN );
	pRender->DrawHitbox( pHitbox, _pCamera, pScene );
	lpQuery->Issue( D3DISSUE_END );

	DWORD dwPixelCount = 0;
	while ( lpQuery->GetData( (LPVOID)&dwPixelCount, sizeof(DWORD), D3DGETDATA_FLUSH ) == S_FALSE );
	if( dwPixelCount > 0 )
	{
		dwFrameCounter += dwPixelCount;

		dwPass = _dwPass;

		ENTITY12 **ppEntity, **ppEnd;

		iChild->Vector( ppEntity, ppEnd );
		while ( ppEntity < ppEnd )
		{
			OBJECT12* pChild = (OBJECT12*)*ppEntity;
			pChild->Draft( _pCamera, dwPass );
			ppEntity++;
		}
	}
}
