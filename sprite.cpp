
#include "sprite.h"
#include "scene.h"
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID DLL UseSprite ( RENDER12* pRender )
{
	LPVOID pData = NULL;

	FLOAT aSpriteVertices[] =
		{ -1.0f, -1.0f, 0.0f, 0.0f, 1.0f,
		  +1.0f, -1.0f, 0.0f, 1.0f, 1.0f,
		  -1.0f, +1.0f, 0.0f, 0.0f, 0.0f,
		  +1.0f, +1.0f, 0.0f, 1.0f, 0.0f };

	if ( pRender->lpSpriteVB )
		pRender->lpSpriteVB->Release();

	pRender->lpD3DDevice->CreateVertexBuffer( sizeof(aSpriteVertices), D3DUSAGE_WRITEONLY, D3DFVF_XYZ | D3DFVF_TEX1,
		D3DPOOL_DEFAULT, &pRender->lpSpriteVB, NULL );

	pRender->lpSpriteVB->Lock( 0, sizeof(aSpriteVertices), (LPVOID*)&pData, 0 );
	CopyMemory( pData, aSpriteVertices, sizeof(aSpriteVertices) );
	pRender->lpSpriteVB->Unlock();
}



SPRITE12::SPRITE12 ( RENDER12* _pRender ) : OBJECT12( _pRender )
{
	bBillboard = FALSE;
}



SPRITE12* SPRITE12::Copy( BOOLEAN bCopyGeometry, BOOLEAN bCopyTexture )
{
	/* création de l'objet */
	SPRITE12* pObject = new SPRITE12( pRender );

	/* copie du contenu commun */
	OBJECT12::Copy( pObject, bCopyGeometry, bCopyTexture );

	/* copie des paramètres */
	pObject->bBillboard = bBillboard;

	return pObject;
}



VOID SPRITE12::Render ( CAMERA12* _pCamera )
{
	pRender->lpD3DDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );
	pRender->lpD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

	D3DXMATRIX matWorld;

	if ( bBillboard )
	{
		D3DXMATRIX matSprite = Matrix() * pScene->Matrix();

		D3DXMATRIX matScale;
		D3DXMatrixScaling( &matScale, matSprite._11, matSprite._22, matSprite._33 );

		matWorld = _pCamera->InvViewMatrix() * matScale;
		matWorld._41 = matSprite._41;
		matWorld._42 = matSprite._42;
		matWorld._43 = matSprite._43;
	}
	else
	{
		matWorld = Matrix() * pScene->Matrix();
	}

	pRender->lpD3DDevice->SetTransform( D3DTS_WORLD, &matWorld );
	pRender->lpD3DDevice->SetTransform( D3DTS_VIEW, &_pCamera->ViewMatrix() );
	pRender->lpD3DDevice->SetTransform( D3DTS_PROJECTION, &_pCamera->ProjMatrix() );

	pRender->lpD3DDevice->SetVertexShader( NULL );
	pRender->lpD3DDevice->SetPixelShader( NULL );

	pRender->lpD3DDevice->SetFVF( D3DFVF_XYZ | D3DFVF_TEX1 );

	SetupTextureStandard();

	pRender->lpD3DDevice->SetStreamSource( 0, pRender->lpSpriteVB, 0, 20 );

	pRender->lpD3DDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );

	pRender->lpD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULLMODE_DEFAULT );
	pRender->lpD3DDevice->SetRenderState( D3DRS_FILLMODE, D3DFILLMODE_DEFAULT );
	pRender->lpD3DDevice->SetRenderState( D3DRS_LIGHTING, D3DLIGHTING_DEFAULT );
	pRender->lpD3DDevice->SetTextureStageState( 0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE );
}
