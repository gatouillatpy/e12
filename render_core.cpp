
#include "render.h"
#include "indexer.h"
#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID RENDER12::DrawHitbox ( HITBOX12* _pHitbox, CAMERA12* _pCamera )
{
	D3DXMATRIX matWorldViewProj = _pHitbox->Matrix() * _pCamera->Matrix();
	D3DXMatrixTranspose( &matWorldViewProj, &matWorldViewProj );

	lpD3DDevice->SetVertexShaderConstantF( 0, (FLOAT*)matWorldViewProj, 4 );
	lpD3DDevice->SetPixelShaderConstantF( 0, _pHitbox->Color(), 1 );

	lpD3DDevice->SetTexture( 0, NULL );

	lpD3DDevice->SetStreamSource( 0, lpHitboxVB, 0, 12 );
	lpD3DDevice->SetIndices( lpHitboxIB );

	lpD3DDevice->SetVertexDeclaration( lpHitboxVD );
	lpD3DDevice->SetVertexShader( lpHitboxVS );
	lpD3DDevice->SetPixelShader( lpHitboxPS );

	lpD3DDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12 );
}

VOID RENDER12::DrawHitbox ( HITBOX12* _pHitbox, CAMERA12* _pCamera, SCENE12* _pScene )
{
	D3DXMATRIX matWorldViewProj = _pHitbox->Matrix() * _pScene->Matrix() * _pCamera->Matrix();
	D3DXMatrixTranspose( &matWorldViewProj, &matWorldViewProj );

	lpD3DDevice->SetVertexShaderConstantF( 0, (FLOAT*)matWorldViewProj, 4 );
	lpD3DDevice->SetPixelShaderConstantF( 0, _pHitbox->Color(), 1 );

	lpD3DDevice->SetTexture( 0, NULL );

	lpD3DDevice->SetStreamSource( 0, lpHitboxVB, 0, 12 );
	lpD3DDevice->SetIndices( lpHitboxIB );

	lpD3DDevice->SetVertexDeclaration( lpHitboxVD );
	lpD3DDevice->SetVertexShader( lpHitboxVS );
	lpD3DDevice->SetPixelShader( lpHitboxPS );

	lpD3DDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12 );
}



VOID RENDER12::DrawBuffer ( LPDIRECT3DTEXTURE9 _pTexture )
{
	lpD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CW );
	lpD3DDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );
	lpD3DDevice->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_POINT );
	lpD3DDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_POINT );
	lpD3DDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_POINT );

	lpD3DDevice->SetStreamSource( 0, lpBufferVB, 0, 20 );
	lpD3DDevice->SetIndices( lpBufferIB );

	lpD3DDevice->SetTexture( 0, _pTexture );

	lpD3DDevice->SetVertexDeclaration( lpBufferVD );
	lpD3DDevice->SetVertexShader( lpBufferVS );
	lpD3DDevice->SetPixelShader( lpBufferPS );

	lpD3DDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2 );
}



VOID RENDER12::RayProjection ( CAMERA12* _pCamera )
{
	FLOAT fY = tanf( _pCamera->fFOV * 0.5f );
	FLOAT fX = fY * (FLOAT)_pCamera->nWidth / (FLOAT)_pCamera->nHeight;

	D3DXVECTOR3 vCamDir = D3DXVECTOR3( cos(_pCamera->pitch()) * cos(_pCamera->yaw()), sin(_pCamera->yaw()), sin(_pCamera->pitch()) * cos(_pCamera->yaw()) );
	D3DXVECTOR3 vCamUp = D3DXVECTOR3( cos(_pCamera->pitch()) * sin(_pCamera->roll()), cos(_pCamera->roll()), 0.0f );

	D3DXVECTOR3 vRight;
	D3DXVec3Cross( &vRight, &vCamDir, &vCamUp );
	D3DXVec3Normalize( &vRight, &vRight );

	D3DXVECTOR3 vUp;
	D3DXVec3Cross( &vUp, &vRight, &vCamDir );
	D3DXVec3Normalize( &vUp, &vUp );

	D3DXVECTOR4 vRayDir = D3DXVECTOR4( fY * vUp + fX * vRight + vCamDir, 4999.999f );
	lpD3DDevice->SetPixelShaderConstantF( 0, (FLOAT*)vRayDir, 1 );

	D3DXVECTOR4 vRayX = D3DXVECTOR4( 2.0f * fX * vRight / nWidth, 1.0f );
	lpD3DDevice->SetPixelShaderConstantF( 1, (FLOAT*)vRayX, 1 );

	D3DXVECTOR4 vRayY = D3DXVECTOR4( 2.0f * fY * vUp / nHeight, 1.0f );
	lpD3DDevice->SetPixelShaderConstantF( 2, (FLOAT*)vRayY, 1 );

	lpD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CW );
	lpD3DDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );

	lpD3DDevice->SetTexture( 0, NULL );
	lpD3DDevice->SetRenderTarget( 0, lpRayBuffer );

	lpD3DDevice->BeginScene();

	lpD3DDevice->SetStreamSource( 0, lpRayVB, 0, 12 );
	lpD3DDevice->SetIndices( lpRayIB );

	lpD3DDevice->SetVertexDeclaration( lpRayVD );
	lpD3DDevice->SetVertexShader( lpRayVS );
	lpD3DDevice->SetPixelShader( lpRayPS );

	lpD3DDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2 );

	lpD3DDevice->EndScene();
}



VOID RENDER12::Draft ( CAMERA12* _pCamera, DWORD & dwPass )
{
	if ( dwDraftFlags == DRAFT_NONE )
	{
		dwPass = -1;
	}
	else if ( dwDraftFlags == DRAFT_FULL )
	{
		dwPass = RANDOM;

		lpD3DDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );

		lpD3DDevice->SetRenderTarget( 0, lpDraftBuffer );

		lpD3DDevice->BeginScene();

		lpD3DDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_ALWAYS );
		lpD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

		ENTITY12 **ppEntity, **ppEnd;
		iScene->Vector( ppEntity, ppEnd );
		while ( ppEntity < ppEnd )
		{
			SCENE12* pScene = (SCENE12*)*ppEntity;
			if ( pScene->pParent == NULL )
				pScene->Draft( _pCamera, dwPass );
			ppEntity++;
		}

		lpD3DDevice->EndScene();
	}
	else
	{
		dwPass = RANDOM;

		DWORD w = ( (dwDraftFlags & DRAFT_BACK) && (dwDraftFlags & DRAFT_FRONT) ) ? nDraftWidth / 2 : nDraftWidth;
		DWORD h = ( (dwDraftFlags & DRAFT_CW) && (dwDraftFlags & DRAFT_CCW) ) ? nDraftHeight / 2 : nDraftHeight;
		DWORD x = ( (dwDraftFlags & DRAFT_BACK) && (dwDraftFlags & DRAFT_FRONT) ) ? nDraftWidth / 2 : 0;
		DWORD y = ( (dwDraftFlags & DRAFT_CW) && (dwDraftFlags & DRAFT_CCW) ) ? nDraftHeight / 2 : 0;
		D3DVIEWPORT9 vp00 = { 0, 0, w, h, 0.0f, 1.0f }; // BACK & CW
		D3DVIEWPORT9 vp01 = { 0, y, w, h, 0.0f, 1.0f }; // BACK & CCW
		D3DVIEWPORT9 vp10 = { x, 0, w, h, 0.0f, 1.0f }; // FRONT & CW
		D3DVIEWPORT9 vp11 = { x, y, w, h, 0.0f, 1.0f }; // FRONT & CCW

		lpD3DDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );

		lpD3DDevice->SetRenderTarget( 0, lpDraftBuffer );

		lpD3DDevice->BeginScene();

		if ( (dwDraftFlags & DRAFT_BACK) && (dwDraftFlags & DRAFT_CW) )
		{
			lpD3DDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_GREATEREQUAL );
			lpD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CW );

			lpD3DDevice->SetViewport( &vp00 );

			lpD3DDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0L, 0.0f, 0 );

			ENTITY12 **ppEntity, **ppEnd;
			iScene->Vector( ppEntity, ppEnd );
			while ( ppEntity < ppEnd )
			{
				SCENE12* pScene = (SCENE12*)*ppEntity;
				if ( pScene->pParent == NULL )
					pScene->Draft( _pCamera, dwPass );
				ppEntity++;
			}
		}
		if ( (dwDraftFlags & DRAFT_BACK) && (dwDraftFlags & DRAFT_CCW) )
		{
			lpD3DDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_GREATEREQUAL );
			lpD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );

			lpD3DDevice->SetViewport( &vp01 );

			lpD3DDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0L, 0.0f, 0 );

			ENTITY12 **ppEntity, **ppEnd;
			iScene->Vector( ppEntity, ppEnd );
			while ( ppEntity < ppEnd )
			{
				SCENE12* pScene = (SCENE12*)*ppEntity;
				if ( pScene->pParent == NULL )
					pScene->Draft( _pCamera, dwPass );
				ppEntity++;
			}
		}
		if ( (dwDraftFlags & DRAFT_FRONT) && (dwDraftFlags & DRAFT_CW) )
		{
			lpD3DDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_LESSEQUAL );
			lpD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CW );

			lpD3DDevice->SetViewport( &vp10 );

			lpD3DDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0L, 1.0f, 0 );

			ENTITY12 **ppEntity, **ppEnd;
			iScene->Vector( ppEntity, ppEnd );
			while ( ppEntity < ppEnd )
			{
				SCENE12* pScene = (SCENE12*)*ppEntity;
				if ( pScene->pParent == NULL )
					pScene->Draft( _pCamera, dwPass );
				ppEntity++;
			}
		}
		if ( (dwDraftFlags & DRAFT_FRONT) && (dwDraftFlags & DRAFT_CCW) )
		{
			lpD3DDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_LESSEQUAL );
			lpD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );

			lpD3DDevice->SetViewport( &vp11 );

			lpD3DDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0L, 1.0f, 0 );

			ENTITY12 **ppEntity, **ppEnd;
			iScene->Vector( ppEntity, ppEnd );
			while ( ppEntity < ppEnd )
			{
				SCENE12* pScene = (SCENE12*)*ppEntity;
				if ( pScene->pParent == NULL )
					pScene->Draft( _pCamera, dwPass );
				ppEntity++;
			}
		}

		lpD3DDevice->EndScene();
	}
}



VOID RENDER12::Update ( )
{
	/* mise à jour des scènes et de leur contenu */
	{
		ENTITY12 **ppEntity, **ppEnd;
		iScene->Vector( ppEntity, ppEnd );
		while ( ppEntity < ppEnd )
		{
			SCENE12* pScene = (SCENE12*)*ppEntity;
			if ( pScene->pParent == NULL )
				pScene->Update();
			ppEntity++;
		}
	}

	/* prérendu */

	DWORD dwPass;

	Draft( lpCamera, dwPass );

	// updating phase

	lpD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CW );
	lpD3DDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_LESSEQUAL );
	lpD3DDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );

	/* mise à jour des interfaces et de leur contenu */
	{
		ENTITY12 **ppEntity, **ppEnd;
		iInterface->Vector( ppEntity, ppEnd );
		while ( ppEntity < ppEnd )
		{
			INTERFACE12* pInterface = (INTERFACE12*)*ppEntity;
			if ( pInterface->pParent == NULL )
				pInterface->Update();
			ppEntity++;
		}
	}

	/* mise à jour des textures animées */
	{
		ENTITY12 **ppEntity, **ppEnd;
		iAnimation->Vector( ppEntity, ppEnd );
		while ( ppEntity < ppEnd )
		{
			ANIMATION12* pAnimation = (ANIMATION12*)*ppEntity;
			pAnimation->Update();
			ppEntity++;
		}
	}

	// ray projection phase

	RayProjection( lpCamera );

	// space rendering phase

	lpD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CW );
	lpD3DDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_LESSEQUAL );
	//lpD3DDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME );

	lpD3DDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
	lpD3DDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
	lpD3DDevice->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR );

	//lpD3DDevice->SetRenderTarget( 0, lpSpaceBuffer );
	lpD3DDevice->SetRenderTarget( 0, lpRenderBuffer );

	lpD3DDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, dwBackColor, 1.0f, 0 );

	/* rendu 3d phase par phase */
	for ( dwPhase = 0 ; dwPhase < dwPhaseCount ; dwPhase++ )
	{
		lpD3DDevice->BeginScene();

		ENTITY12 **ppEntity, **ppEnd;
		iScene->Vector( ppEntity, ppEnd );
		if ( dwPass == -1 )
		{
			while ( ppEntity < ppEnd )
			{
				SCENE12* pScene = (SCENE12*)*ppEntity;
				if ( pScene->pParent == NULL )
					pScene->Render( lpCamera );
				ppEntity++;
			}
		}
		else
		{
			while ( ppEntity < ppEnd )
			{
				SCENE12* pScene = (SCENE12*)*ppEntity;
				if ( pScene->pParent == NULL )
					if ( pScene->dwPass == dwPass )
						pScene->Render( lpCamera, dwPass );
				ppEntity++;
			}
		}

		lpD3DDevice->EndScene();

		{
			ppPhaseBuffer[dwPhase]->BeginDraw();

			DrawBuffer( lpRenderTexture );

			ppPhaseBuffer[dwPhase]->EndDraw();
		}
	}

	/* copie du rendu 3d dans le backbuffer */
	{
		lpD3DDevice->SetRenderTarget( 0, lpBackBuffer );

		lpD3DDevice->BeginScene();

		DrawBuffer( lpRenderTexture );

		lpD3DDevice->EndScene();
	}

	// ray projection phase with light's point of view

	/*CAMERA12* tCamera = new CAMERA12( RANDOM );
	tCamera->SetCenter( -930.0f, 580.0f, 30.0f );
	tCamera->SetAngle( 0.059798f, -0.307001f, 0.0f );
	tCamera->SetWidth( 256 );
	tCamera->SetHeight( 256 );
	tCamera->SetRatio( 1.0f );
	tCamera->Rotate( 0.0f, 0.0f, 0.0f );
	RayProjection( tCamera ) );

	// light rendering phase

	lpD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CW ) );
	lpD3DDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_LESSEQUAL ) );
	lpD3DDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID ) );

	lpD3DDevice->SetRenderTarget( 0, lpLightBuffer ) );

	lpD3DDevice->BeginScene() );

	lpD3DDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0 ) );

	for ( DWORD i = 0L ; i < dwSceneCount ; i++ )
	ppSceneList[i]->Render( tCamera ) );

	lpD3DDevice->EndScene() );*/



	// final rendering phase

	/*lpD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CW ) );
	lpD3DDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_LESSEQUAL ) );
	lpD3DDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID ) );

	lpD3DDevice->SetRenderTarget( 0, lpBackBuffer ) );

	lpD3DDevice->BeginScene() );

	lpD3DDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, dwBackColor, 1.0f, 0 ) );

	lpD3DDevice->SetVertexShader( lpFinalShader->lpVertexShader ) );
	lpD3DDevice->SetPixelShader( lpFinalShader->lpPixelShader ) );

	D3DXMATRIX matLightViewProj = tCamera->Matrix();
	D3DXMatrixTranspose( &matLightViewProj, &matLightViewProj );
	lpFinalShader->SetPSMatrix( "matLightViewProj", &matLightViewProj );

	D3DXVECTOR4 vFactor = D3DXVECTOR4( (FLOAT)lpCamera->Width(), (FLOAT)lpCamera->Height(), 0.0f, 0.0f );
	lpFinalShader->SetPSVector( "vFactor", &vFactor );

	D3DXVECTOR4 vOrigin = D3DXVECTOR4( tCamera->GetCenter(), 1.0f );
	lpFinalShader->SetPSVector( "vOrigin", &vOrigin );

	lpFinalShader->SetPSTexture( "smpSpace", lpSpaceTexture );
	lpFinalShader->SetPSTexture( "smpLight", lpLightTexture );

	lpD3DDevice->SetStreamSource( 0, lpBufferVB, 0, 20 ) );
	lpD3DDevice->SetIndices( lpBufferIB ) );

	lpD3DDevice->SetVertexDeclaration( lpBufferVD ) );

	lpD3DDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2 ) );

	tCamera->Release();*/

	lpD3DDevice->BeginScene();

	{
		ENTITY12 **ppEntity, **ppEnd;
		iInterface->Vector( ppEntity, ppEnd );
		while ( ppEntity < ppEnd )
		{
			INTERFACE12* pInterface = (INTERFACE12*)*ppEntity;
			if ( pInterface->pParent == NULL )
				pInterface->Render();
			ppEntity++;
		}
	}

	if ( bShowDraft )
	{
		lpD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
		lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		lpD3DDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
		DrawBuffer( lpDraftTexture );
		lpD3DDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE );
	}

	lpD3DDevice->EndScene();

	lpD3DDevice->SetTexture( 0, NULL );
	lpD3DDevice->SetTexture( 1, NULL );

	lpD3DDevice->Present( NULL, NULL, NULL, NULL );
}



VOID RENDER12::PickPoint ( FLOAT _fX, FLOAT _fY, SCENE12* & _pScene, OBJECT12* & _pObject, VERTEX* & _pVertex, FACE* & _pFace )
{
	// vérifier si le moteur n'est pas déjà en train de rendre quelque chose

	if ( _fX < 0.0f ) _fX = 0.0f;
	if ( _fY < 0.0f ) _fY = 0.0f;
	if ( _fX > 1.0f ) _fX = 1.0f;
	if ( _fY > 1.0f ) _fY = 1.0f;

	DWORD nX = (DWORD)(_fX * (FLOAT)nWidth);
	DWORD nY = (DWORD)(_fY * (FLOAT)nHeight);

	lpD3DDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );

	lpD3DDevice->SetRenderTarget( 0, lpRenderBuffer );

	{
		lpD3DDevice->BeginScene();

		lpD3DDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_LESSEQUAL );
		lpD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

		lpD3DDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0L, 1.0f, 0 );

		ENTITY12 **ppEntity, **ppEnd;
		iScene->Vector( ppEntity, ppEnd );
		while ( ppEntity < ppEnd )
		{
			SCENE12* pScene = (SCENE12*)*ppEntity;
			DrawHitbox( pScene->Hitbox(), lpCamera );
			ppEntity++;
		}
				
		lpD3DDevice->EndScene();

		lpD3DDevice->GetRenderTargetData( lpRenderBuffer, lpRenderSurface );
		D3DLOCKED_RECT tLockedRect;
		lpRenderSurface->LockRect( &tLockedRect, NULL, 0 );
		DWORD* dwPixel = (DWORD*)tLockedRect.pBits + nY * nWidth + nX;
		_pScene = (SCENE12*)(*dwPixel);
		lpRenderSurface->UnlockRect();
	}

	if ( _pScene )
	{
		lpD3DDevice->BeginScene();

		lpD3DDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_LESSEQUAL );
		lpD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

		lpD3DDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0L, 1.0f, 0 );

		ENTITY12 **ppEntity, **ppEnd;
		iObject->Vector( ppEntity, ppEnd );
		while ( ppEntity < ppEnd )
		{
			OBJECT12* pObject = (OBJECT12*)*ppEntity;
			if ( pObject->pScene == _pScene )
				DrawHitbox( pObject->Hitbox(), lpCamera, _pScene );
			ppEntity++;
		}

		lpD3DDevice->EndScene();

		lpD3DDevice->GetRenderTargetData( lpRenderBuffer, lpRenderSurface );
		D3DLOCKED_RECT tLockedRect;
		lpRenderSurface->LockRect( &tLockedRect, NULL, 0 );
		DWORD* dwPixel = (DWORD*)tLockedRect.pBits + nY * nWidth + nX;
		_pObject = (OBJECT12*)(*dwPixel);
		lpRenderSurface->UnlockRect();
	}

	if ( _pObject )
	{
		lpD3DDevice->BeginScene();

		lpD3DDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_LESSEQUAL );
		lpD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

		lpD3DDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0L, 1.0f, 0 );

		lpD3DDevice->SetVertexShader( NULL );
		lpD3DDevice->SetPixelShader( NULL );

		D3DXMATRIX matWorld = _pObject->Matrix() * _pScene->Matrix();
		lpD3DDevice->SetTransform( D3DTS_WORLD, &matWorld );
		lpD3DDevice->SetTransform( D3DTS_VIEW, &lpCamera->ViewMatrix() );
		lpD3DDevice->SetTransform( D3DTS_PROJECTION, &lpCamera->ProjMatrix() );

		lpD3DDevice->SetTexture( 0, NULL );
		lpD3DDevice->SetTexture( 1, NULL );
		lpD3DDevice->SetTexture( 2, NULL );
		lpD3DDevice->SetTexture( 3, NULL );

		lpD3DDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
		_pObject->pGeometry->Render();
		lpD3DDevice->SetRenderState( D3DRS_LIGHTING, FALSE );

		_pObject->pGeometry->DrawVertices();

		lpD3DDevice->EndScene();

		lpD3DDevice->GetRenderTargetData( lpRenderBuffer, lpRenderSurface );
		D3DLOCKED_RECT tLockedRect;
		lpRenderSurface->LockRect( &tLockedRect, NULL, 0 );
		DWORD* dwPixel = (DWORD*)tLockedRect.pBits + nY * nWidth + nX;
		_pVertex = (VERTEX*)(*dwPixel);
		lpRenderSurface->UnlockRect();
	}

	if ( _pObject )
	{
		lpD3DDevice->BeginScene();
		lpD3DDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_LESSEQUAL );
		lpD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
		lpD3DDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0L, 1.0f, 0 );

		lpD3DDevice->SetVertexShader( NULL );
		lpD3DDevice->SetPixelShader( NULL );

		D3DXMATRIX matWorld = _pObject->Matrix() * _pScene->Matrix();
		lpD3DDevice->SetTransform( D3DTS_WORLD, &matWorld );
		lpD3DDevice->SetTransform( D3DTS_VIEW, &lpCamera->ViewMatrix() );
		lpD3DDevice->SetTransform( D3DTS_PROJECTION, &lpCamera->ProjMatrix() );

		lpD3DDevice->SetTexture( 0, NULL );
		lpD3DDevice->SetTexture( 1, NULL );
		lpD3DDevice->SetTexture( 2, NULL );
		lpD3DDevice->SetTexture( 3, NULL );

		_pObject->pGeometry->DrawFaces();

		lpD3DDevice->EndScene();

		lpD3DDevice->GetRenderTargetData( lpRenderBuffer, lpRenderSurface );
		D3DLOCKED_RECT tLockedRect;
		lpRenderSurface->LockRect( &tLockedRect, NULL, 0 );
		DWORD* dwPixel = (DWORD*)tLockedRect.pBits + nY * nWidth + nX;
		_pFace = (FACE*)(*dwPixel);
		lpRenderSurface->UnlockRect();
	}
}

VOID PickRegion ( FLOAT _fX, FLOAT _fY, FLOAT _fW, FLOAT _fH, SCENE12** & _pScene, OBJECT12** & _pObject, VERTEX** & _pVertex, FACE** & _pFace ) ;