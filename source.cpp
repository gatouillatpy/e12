
#include "sprite.h"
#include "scene.h"
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



SPRITE12::SPRITE12 ( DWORD _dwIndex, RENDER12* _pRender ) : OBJECT12( _dwIndex, _pRender )
{
	dwFlags = D3DXSPRITE_ALPHABLEND;
}



SPRITE12* SPRITE12::Copy( DWORD _dwIndex, BOOLEAN bCopyGeometry, BOOLEAN bCopyTexture )
{
	/* création de l'objet */
	SPRITE12* pObject = pRender->AddSprite( _dwIndex );

	/* copie des objets enfants */
	for ( DWORD k = 0 ; k < dwChild ; k++ )
	{
		OBJECT12* pChild = ppChild[k]->Copy( RANDOM, bCopyGeometry, bCopyTexture );
		pObject->AddChild( pChild );
	}

	/* copie de la texture */
	if ( bCopyTexture )
		pObject->pTexture = pTexture->Copy( RANDOM );
	else
		pObject->pTexture = pTexture;

	/* copie des liens */
	pObject->pParent = pParent;
	pObject->pScene = pScene;

	/* copie des propriétés spatiales */
	pObject->vCenter = vCenter;
	pObject->vAngle = vAngle;
	pObject->vSize = vSize;

	return pObject;
}



HRESULT SPRITE12::Render ( CAMERA12* _pCamera )
{
	D3DXMATRIX matWorld = Matrix() * pScene->Matrix();

	pRender->lpD3DDevice->SetTransform( D3DTS_WORLD, &matWorld );
	pRender->lpD3DDevice->SetTransform( D3DTS_VIEW, &_pCamera->ViewMatrix() );
	pRender->lpD3DDevice->SetTransform( D3DTS_PROJECTION, &_pCamera->ProjMatrix() );

	LPD3DXSPRITE lpSprite = pRender->lpSprite;
	lpSprite->SetWorldViewRH( &matWorld, &_pCamera->ViewMatrix() );

	lpSprite->Begin( D3DXSPRITE_OBJECTSPACE | D3DXSPRITE_BILLBOARD | D3DXSPRITE_ALPHABLEND );
	D3DXVECTOR3 vSpriteCenter = D3DXVECTOR3( 128.0f, 128.0f, 0.0f );
	lpSprite->Draw( (LPDIRECT3DTEXTURE9)pTexture->lpD3DTexture, NULL, &vSpriteCenter, NULL, D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 0.5f) );
	lpSprite->End();

	return S_OK;
}



VOID SPRITE12::Release ( )
{
	delete this;
}