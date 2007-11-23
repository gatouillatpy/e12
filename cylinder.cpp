
#include "shader.h"
#include "cylinder.h"
#include "scene.h"
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID DLL UseCylinder ( RENDER12* pRender )
{
	pRender->lpCylinderShader = new SHADER12( pRender );

//#ifndef DEBUG_SHADER
	pRender->lpCylinderShader->Load( "..\\data\\cylinder.s12" );
//#else
//	pRender->lpCylinderShader->CompileVSFile( "..\\engine\\cylinder.vsh", "vs_3_sw", "VS_Default" );
//	pRender->lpCylinderShader->CompilePSFile( "..\\engine\\cylinder.psh", "ps_3_sw", "PS_Default" );
//#endif
}



CYLINDER12::CYLINDER12 ( RENDER12* _pRender ) : OBJECT12( _pRender )
{
	fRadius = 0.0f;
	fHeight = 0.0f;

	bRaytrace = FALSE;
}



CYLINDER12* CYLINDER12::Copy( BOOLEAN bCopyGeometry, BOOLEAN bCopyTexture )
{
	/* création de l'objet */
	CYLINDER12* pObject = new CYLINDER12( pRender );

	/* copie du contenu commun */
	OBJECT12::Copy( pObject, bCopyGeometry, bCopyTexture );

	/* copie des paramètres géométriques */
	pObject->fHeight = fHeight;
	pObject->fRadius = fRadius;

	/* copie de la méthode d'affichage */
	pObject->bRaytrace = bRaytrace;

	return pObject;
}



VOID CYLINDER12::Create ( FLOAT _fRadius, FLOAT _fHeight )
{
	fRadius = _fRadius;
	fHeight = _fHeight;

	if ( pGeometry ) delete pGeometry;
	pGeometry = new GEOMETRY12( pRender );
	pGeometry->SetVertexCount( 24L );
	pGeometry->SetFaceCount( 24L );

	pGeometry->SetVertexPoint(  0, _fRadius * cos(0.000f * D3DX_PI), -0.5f * _fHeight, _fRadius * sin(0.000f * D3DX_PI) );
	pGeometry->SetVertexPoint(  1, _fRadius * cos(0.167f * D3DX_PI), -0.5f * _fHeight, _fRadius * sin(0.167f * D3DX_PI) );
	pGeometry->SetVertexPoint(  2, _fRadius * cos(0.333f * D3DX_PI), -0.5f * _fHeight, _fRadius * sin(0.333f * D3DX_PI) );
	pGeometry->SetVertexPoint(  3, _fRadius * cos(0.500f * D3DX_PI), -0.5f * _fHeight, _fRadius * sin(0.500f * D3DX_PI) );
	pGeometry->SetVertexPoint(  4, _fRadius * cos(0.667f * D3DX_PI), -0.5f * _fHeight, _fRadius * sin(0.667f * D3DX_PI) );
	pGeometry->SetVertexPoint(  5, _fRadius * cos(0.833f * D3DX_PI), -0.5f * _fHeight, _fRadius * sin(0.833f * D3DX_PI) );
	pGeometry->SetVertexPoint(  6, _fRadius * cos(1.000f * D3DX_PI), -0.5f * _fHeight, _fRadius * sin(1.000f * D3DX_PI) );
	pGeometry->SetVertexPoint(  7, _fRadius * cos(1.167f * D3DX_PI), -0.5f * _fHeight, _fRadius * sin(1.167f * D3DX_PI) );
	pGeometry->SetVertexPoint(  8, _fRadius * cos(1.333f * D3DX_PI), -0.5f * _fHeight, _fRadius * sin(1.333f * D3DX_PI) );
	pGeometry->SetVertexPoint(  9, _fRadius * cos(1.500f * D3DX_PI), -0.5f * _fHeight, _fRadius * sin(1.500f * D3DX_PI) );
	pGeometry->SetVertexPoint( 10, _fRadius * cos(1.667f * D3DX_PI), -0.5f * _fHeight, _fRadius * sin(1.667f * D3DX_PI) );
	pGeometry->SetVertexPoint( 11, _fRadius * cos(1.833f * D3DX_PI), -0.5f * _fHeight, _fRadius * sin(1.833f * D3DX_PI) );
	pGeometry->SetVertexPoint( 12, _fRadius * cos(0.000f * D3DX_PI), +0.5f * _fHeight, _fRadius * sin(0.000f * D3DX_PI) );
	pGeometry->SetVertexPoint( 13, _fRadius * cos(0.167f * D3DX_PI), +0.5f * _fHeight, _fRadius * sin(0.167f * D3DX_PI) );
	pGeometry->SetVertexPoint( 14, _fRadius * cos(0.333f * D3DX_PI), +0.5f * _fHeight, _fRadius * sin(0.333f * D3DX_PI) );
	pGeometry->SetVertexPoint( 15, _fRadius * cos(0.500f * D3DX_PI), +0.5f * _fHeight, _fRadius * sin(0.500f * D3DX_PI) );
	pGeometry->SetVertexPoint( 16, _fRadius * cos(0.667f * D3DX_PI), +0.5f * _fHeight, _fRadius * sin(0.667f * D3DX_PI) );
	pGeometry->SetVertexPoint( 17, _fRadius * cos(0.833f * D3DX_PI), +0.5f * _fHeight, _fRadius * sin(0.833f * D3DX_PI) );
	pGeometry->SetVertexPoint( 18, _fRadius * cos(1.000f * D3DX_PI), +0.5f * _fHeight, _fRadius * sin(1.000f * D3DX_PI) );
	pGeometry->SetVertexPoint( 19, _fRadius * cos(1.167f * D3DX_PI), +0.5f * _fHeight, _fRadius * sin(1.167f * D3DX_PI) );
	pGeometry->SetVertexPoint( 20, _fRadius * cos(1.333f * D3DX_PI), +0.5f * _fHeight, _fRadius * sin(1.333f * D3DX_PI) );
	pGeometry->SetVertexPoint( 21, _fRadius * cos(1.500f * D3DX_PI), +0.5f * _fHeight, _fRadius * sin(1.500f * D3DX_PI) );
	pGeometry->SetVertexPoint( 22, _fRadius * cos(1.667f * D3DX_PI), +0.5f * _fHeight, _fRadius * sin(1.667f * D3DX_PI) );
	pGeometry->SetVertexPoint( 23, _fRadius * cos(1.833f * D3DX_PI), +0.5f * _fHeight, _fRadius * sin(1.833f * D3DX_PI) );

	pGeometry->SetFace(  0,  0, 12, 13 );
	pGeometry->SetFace(  1, 13,  1,  0 );
	pGeometry->SetFace(  2,  1, 13, 14 );
	pGeometry->SetFace(  3, 14,  2,  1 );
	pGeometry->SetFace(  4,  2, 14, 15 );
	pGeometry->SetFace(  5, 15,  3,  2 );
	pGeometry->SetFace(  6,  3, 15, 16 );
	pGeometry->SetFace(  7, 16,  4,  3 );
	pGeometry->SetFace(  8,  4, 16, 17 );
	pGeometry->SetFace(  9, 17,  5,  4 );
	pGeometry->SetFace( 10,  5, 17, 18 );
	pGeometry->SetFace( 11, 18,  6,  5 );
	pGeometry->SetFace( 12,  6, 18, 19 );
	pGeometry->SetFace( 13, 19,  7,  6 );
	pGeometry->SetFace( 14,  7, 19, 20 );
	pGeometry->SetFace( 15, 20,  8,  7 );
	pGeometry->SetFace( 16,  8, 20, 21 );
	pGeometry->SetFace( 17, 21,  9,  8 );
	pGeometry->SetFace( 18,  9, 21, 22 );
	pGeometry->SetFace( 19, 22, 10,  9 );
	pGeometry->SetFace( 20, 10, 22, 23 );
	pGeometry->SetFace( 21, 23, 11, 10 );
	pGeometry->SetFace( 22, 11, 23, 12 );
	pGeometry->SetFace( 23, 12,  0, 11 );
}

VOID CYLINDER12::Create ( FLOAT _fRadius, FLOAT _fHeight, DWORD _nDR, DWORD _nDH )
{
	fRadius = _fRadius;
	fHeight = _fHeight;

	if ( pGeometry ) delete pGeometry;
	pGeometry = new GEOMETRY12( pRender );
	pGeometry->SetVertexCount( _nDR * (_nDH + 1) );
	pGeometry->SetFaceCount( _nDR * _nDH * 2 );

	DWORD k;

	FLOAT l = D3DX_PI * 2.0f / (FLOAT)_nDR;
	FLOAT m = _fHeight / (FLOAT)_nDH;

	FLOAT u, v;

	k = 0L;

	v = -0.5f * _fHeight;
	for ( DWORD h = 0L ; h <= _nDH ; h++ )
	{
		u = 0.0f;
		for ( DWORD r = 0L ; r < _nDR ; r++ )
		{
			pGeometry->SetVertexPoint( k, _fRadius * cos(u), v, _fRadius * sin(u) );
			u += l;
			k++;
		}
		v += m;
	}

	DWORD a, b, c, d;

	k = 0L;

	for ( DWORD h = 0L ; h < _nDH ; h++ )
	{
		a = h * _nDR;
		b = a + 1;
		c = (h + 1) * _nDR;
		d = c + 1;
		for ( DWORD r = 0L ; r < _nDR ; r++ )
		{
			pGeometry->SetFace( k, a, c, d );
			k++;
			pGeometry->SetFace( k, d, b, a );
			k++;
			a++; b++; c++; d++;
			if ( b == (h + 1) * _nDR ) b -= _nDR;
			if ( d == (h + 2) * _nDR ) d -= _nDR;
		}
	}
}



VOID CYLINDER12::Render ( CAMERA12* _pCamera )
{
	if ( bRaytrace ) return Raytrace( _pCamera );

	OBJECT12::Render( _pCamera );
}



VOID CYLINDER12::Raytrace ( CAMERA12* _pCamera )
{
	if ( bVisible == FALSE ) return;

	pRender->lpD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

	// DEBUT : A FAIRE DANS LA PHASE D'UPDATE
	D3DXVECTOR3 vecSize = pGeometry->Max() - pGeometry->Min();
	if ( vecSize.x < 0.001f ) vecSize.x = 0.001f;
	if ( vecSize.y < 0.001f ) vecSize.y = 0.001f;
	if ( vecSize.z < 0.001f ) vecSize.z = 0.001f;
	D3DXMATRIX matSize;
	D3DXMatrixScaling( &matSize, vecSize.x, vecSize.y, vecSize.z );

	D3DXVECTOR3 vecCenter = (pGeometry->Min() + pGeometry->Max()) * 0.5f;
	D3DXMATRIX matCenter;
	D3DXMatrixTranslation( &matCenter, vecCenter.x, vecCenter.y, vecCenter.z );

	D3DXMATRIX matHitbox = matSize * matCenter * Matrix();
	// FIN : A FAIRE DANS LA PHASE D'UPDATE

	D3DXMATRIX matWorldViewProj = matHitbox * pScene->Matrix() * _pCamera->Matrix();
	D3DXMatrixTranspose( &matWorldViewProj, &matWorldViewProj );
	pRender->lpCylinderShader->SetVSMatrix( "matWorldViewProj", &matWorldViewProj );

	D3DXMATRIX matWorld = Matrix();
	D3DXMatrixTranspose( &matWorld, &matWorld );
	pRender->lpCylinderShader->SetPSMatrix( "matWorld", &matWorld );

	D3DXMATRIX matWorldInverse = Matrix();
	D3DXMatrixInverse( &matWorldInverse, NULL, &matWorldInverse );
	D3DXMatrixTranspose( &matWorldInverse, &matWorldInverse );
	pRender->lpCylinderShader->SetPSMatrix( "matWorldInverse", &matWorldInverse );

	D3DXVECTOR4 vCamera = D3DXVECTOR4( _pCamera->GetCenter(), 1.0f );
	pRender->lpCylinderShader->SetPSVector( "vRayOrigin", &vCamera );

	D3DXVECTOR4 vFactor = D3DXVECTOR4( (FLOAT)_pCamera->Width(), (FLOAT)_pCamera->Height(), 0.0f, 0.0f );
	pRender->lpCylinderShader->SetPSVector( "vFactor", &vFactor );

	pRender->lpCylinderShader->SetPSTexture( "smpBuffer", pRender->lpRayTexture );

	pRender->lpCylinderShader->SetPSFloat( "fRadius", fRadius );
	pRender->lpCylinderShader->SetPSFloat( "fHeight", fHeight );

	pRender->lpCylinderShader->SetPSFloat( "fZPlane", _pCamera->ZNearPlane() );
	pRender->lpCylinderShader->SetPSFloat( "fZFactor", _pCamera->ZFarPlane() - _pCamera->ZNearPlane() );

	pRender->lpD3DDevice->SetVertexShader( pRender->lpCylinderShader->lpVertexShader );
	pRender->lpD3DDevice->SetPixelShader( pRender->lpCylinderShader->lpPixelShader );

	pRender->lpD3DDevice->SetStreamSource( 0, pRender->lpHitboxVB, 0, 12 );
	pRender->lpD3DDevice->SetIndices( pRender->lpHitboxIB );

	pRender->lpD3DDevice->SetVertexDeclaration( pRender->lpHitboxVD );

	pRender->lpD3DDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12 );

	pRender->lpD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULLMODE_DEFAULT );
}
