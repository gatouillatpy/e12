
#include "texture.h"
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



BOOLEAN TEXTURE12::Load ( LPSTR _sFile )
{
	if ( _sFile == NULL )
	{
		pLog->Push( __FILE__, __LINE__, CODE_ERROR, CODE_TEXTURE12, 0x0001, this, NULL, NULL ); return 0;
	}
	else if ( CheckFile( _sFile ) == 0 ) 
	{
		pLog->Push( __FILE__, __LINE__, CODE_ERROR, CODE_TEXTURE12, 0x0002, this, NULL, _sFile ); return 0;
	}

	// à faire

	return 1;
}

BOOLEAN TEXTURE12::Import ( LPSTR _sFile )
{
	if ( FAILED ( D3DXCreateTextureFromFile( pRender->lpD3DDevice, _sFile, (LPDIRECT3DTEXTURE9*)&lpD3DTexture ) ) ) return 0;

	D3DSURFACE_DESC d3dsdInfo; ((LPDIRECT3DTEXTURE9)lpD3DTexture)->GetLevelDesc( 0, &d3dsdInfo );
	nWidth = d3dsdInfo.Width;
	nHeight = d3dsdInfo.Height;

	return 1;
}



VOID TEXTURE12::UpdateMatrix ( )
{
	D3DXMATRIX matCenter;
	D3DXMatrixIdentity( &matCenter );
	matCenter._31 = vCenter.x;
	matCenter._32 = vCenter.y;

	D3DXMATRIX matInverse;
	D3DXMatrixIdentity( &matInverse );
	matInverse._31 = -vCenter.x;
	matInverse._32 = -vCenter.y;

	D3DXMATRIX matOffset;
	D3DXMatrixIdentity( &matOffset );
	matOffset._31 = vOffset.x;
	matOffset._32 = vOffset.y;

	D3DXMATRIX matAngle;
	D3DXMatrixRotationZ( &matAngle, fAngle );

	D3DXMATRIX matZoom;
	D3DXMatrixScaling( &matZoom, vZoom.x, vZoom.y, 1.0f );

	matTexture = matInverse * matZoom * matAngle * matCenter * matOffset;

	bMatrix = TRUE;
}

D3DXMATRIX TEXTURE12::Matrix ( )
{
	if ( bMatrix == FALSE ) UpdateMatrix();

	return matTexture;
}
