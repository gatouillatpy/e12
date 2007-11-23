
#include "shader.h"
#include "surface.h"
#include "scene.h"
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID DLL UseSurface ( RENDER12* pRender )
{
	pRender->lpSurfaceShader = new SHADER12( pRender );

//#ifndef DEBUG_SHADER
	pRender->lpSurfaceShader->Load( "..\\data\\surface.s12" );
//#else
//	pRender->lpSurfaceShader->CompileVSFile( "..\\engine\\surface.vsh", "vs_3_sw", "VS_Default" );
//	pRender->lpSurfaceShader->CompilePSFile( "..\\engine\\surface.psh", "ps_3_sw", "PS_Default" );
//#endif
}



SURFACE12::SURFACE12 ( RENDER12* _pRender ) : OBJECT12( _pRender )
{
	wDU = 2;
	wDV = 2;

	pNode = new NODE[4];
	pNode[0].x = -1.0f; pNode[0].y = 0.0f; pNode[0].z = -1.0f;
	pNode[1].x = +1.0f; pNode[1].y = 0.0f; pNode[1].z = -1.0f;
	pNode[2].x = -1.0f; pNode[2].y = 0.0f; pNode[2].z = +1.0f;
	pNode[3].x = +1.0f; pNode[3].y = 0.0f; pNode[3].z = +1.0f;

	bColor = FALSE;
	bUVMap = FALSE;

	bSurface = FALSE;

	bRaytrace = FALSE;
}

SURFACE12::~SURFACE12 ( )
{
	delete [] pNode;
}



SURFACE12* SURFACE12::Copy( BOOLEAN bCopyGeometry, BOOLEAN bCopyTexture )
{
	/* création de l'objet */
	SURFACE12* pObject = new SURFACE12( pRender );

	/* copie du contenu commun */
	OBJECT12::Copy( pObject, bCopyGeometry, bCopyTexture );

	/* copie des paramètres géométriques */
	pObject->fWidth = fWidth;
	pObject->fHeight = fHeight;
	pObject->fLength = fLength;

	/* copie des paramètres spécifiques */
	pObject->wDX = wDX;
	pObject->wDY = wDY;
	pObject->wDU = wDU;
	pObject->wDV = wDV;

	/* copie de la méthode d'affichage */
	pObject->bRaytrace = bRaytrace;

	/* copie des noeuds */
	delete [] pObject->pNode;
	pObject->pNode = new NODE[wDU*wDV];
	CopyMemory( pObject->pNode, pNode, wDU * wDV * sizeof(NODE) );

	/* copie des paramètres des noeuds */
	pObject->bColor = bColor;
	pObject->bUVMap = bUVMap;

	return pObject;
}



VOID SURFACE12::Create ( FLOAT _fWidth, FLOAT _fHeight, FLOAT _fLength, WORD _wDX, WORD _wDY )
{
	if ( pGeometry ) delete pGeometry;
	pGeometry = new GEOMETRY12( pRender );
	pGeometry->SetVertexCount( (_wDX + 1) * (_wDY + 1) );
	pGeometry->SetFaceCount( 2 *  _wDX * _wDY );

	fWidth = _fWidth;
	fHeight = _fHeight;
	fLength = _fLength;

	wDX = _wDX;
	wDY = _wDY;

	UpdateSurface();
}



VOID SURFACE12::SetGridSize ( WORD _wDU, WORD _wDV )
{
	wDU = _wDU;
	wDV = _wDV;

	delete [] pNode;
	pNode = new NODE[wDU*wDV];

	DWORD l = 0L;

	for ( WORD j = 0 ; j < wDV ; j++ )
	{
		for ( WORD i = 0 ; i < wDU ; i++ )
		{
			pNode[l].x = (FLOAT)i / (FLOAT)(wDU - 1) * 2.0f - 1.0f;
			pNode[l].y = 0.0f;
			pNode[l].z = (FLOAT)j / (FLOAT)(wDV - 1) * 2.0f - 1.0f;
			pNode[l].r = 0.0f;
			pNode[l].g = 0.0f;
			pNode[l].b = 0.0f;
			pNode[l].a = 1.0f;
			pNode[l].u = (FLOAT)i / (FLOAT)(wDU - 1);
			pNode[l].v = (FLOAT)j / (FLOAT)(wDV - 1);
			l++;
		}
	}

	bSurface = FALSE;
}

VOID SURFACE12::SetGridWidth ( WORD _wDU )
{
	SetGridSize( _wDU, wDV );
}

VOID SURFACE12::SetGridHeight ( WORD _wDV )
{
	SetGridSize( wDU, _wDV );
}



VOID SURFACE12::SetNodePoint ( WORD _p, WORD _q, FLOAT _x, FLOAT _y, FLOAT _z )
{
	pNode[_p*wDV+_q].x = _x;
	pNode[_p*wDV+_q].y = _y;
	pNode[_p*wDV+_q].z = _z;

	bSurface = FALSE;
}

VOID SURFACE12::SetNodeDepth ( WORD _p, WORD _q, FLOAT _z )
{
	pNode[_p*wDV+_q].z = _z;

	bSurface = FALSE;
}

VOID SURFACE12::SetNodeColor ( WORD _p, WORD _q, FLOAT _r, FLOAT _g, FLOAT _b, FLOAT _a )
{
	pNode[_p*wDV+_q].r = _r;
	pNode[_p*wDV+_q].g = _g;
	pNode[_p*wDV+_q].b = _b;
	pNode[_p*wDV+_q].a = _a;

	bColor = TRUE;

	bSurface = FALSE;
}

VOID SURFACE12::SetNodeUVMap ( WORD _p, WORD _q, FLOAT _u, FLOAT _v )
{
	pNode[_p*wDV+_q].u = _u;
	pNode[_p*wDV+_q].v = _v;

	bUVMap = TRUE;

	bSurface = FALSE;
}


VOID SURFACE12::UpdateSurface ( )
{
	DWORD i, j, k, l;

	FLOAT u, v;

	FLOAT* bu = new FLOAT[wDU+1];
	FLOAT* bv = new FLOAT[wDV+1];

	k = 0L;

	VERTEX tVertex;

	for ( WORD y = 0 ; y <= wDY ; y++ )
	{
		v = (FLOAT)y / (FLOAT)wDY;

		for ( WORD j = 0 ; j < wDV + 1 ; j++ )
			bv[j] = 0.0f;

		bv[1] = 1.0f;
		for ( WORD j = 1 ; j < wDV ; j++ )
			for ( WORD i = j + 1 ; i > 0 ; i-- )
				bv[i] = (1.0f - v) * bv[i] + v * bv[i-1];

		for ( WORD x = 0 ; x <= wDX ; x++ )
		{
			u = (FLOAT)x / (FLOAT)wDX;

			for ( WORD i = 0 ; i < wDU + 1 ; i++ )
				bu[i] = 0.0f;

			bu[1] = 1.0f;
			for ( WORD i = 1 ; i < wDU ; i++ )
				for ( WORD j = i + 1 ; j > 0 ; j-- )
					bu[j] = (1.0f - u) * bu[j] + u * bu[j-1];

			ZeroMemory( &tVertex, sizeof(tVertex) ); l = 0L;
			for( WORD i = 0 ; i < wDU ; i++ )
			{
				for( WORD j = 0 ; j < wDV ; j++ )
				{
					tVertex.x += pNode[l].x * bu[i+1] * bv[j+1] * fWidth;
					tVertex.y += pNode[l].y * bu[i+1] * bv[j+1] * fHeight;
					tVertex.z += pNode[l].z * bu[i+1] * bv[j+1] * fLength;
					tVertex.r += pNode[l].r * bu[i+1] * bv[j+1];
					tVertex.g += pNode[l].g * bu[i+1] * bv[j+1];
					tVertex.b += pNode[l].b * bu[i+1] * bv[j+1];
					tVertex.a += pNode[l].a * bu[i+1] * bv[j+1];
					tVertex.u += pNode[l].u * bu[i+1] * bv[j+1];
					tVertex.v += pNode[l].v * bu[i+1] * bv[j+1];
					l++;
				}
			}
			pGeometry->SetVertexPoint( k, tVertex.x, tVertex.y, tVertex.z );
			if ( bColor ) pGeometry->SetVertexColor( k, tVertex.r, tVertex.g, tVertex.b, tVertex.a );
			if ( bUVMap ) pGeometry->SetVertexUVMap( k, tVertex.u, tVertex.v );
			k++;
		}
	}

	delete [] bu;
	delete [] bv;

	k = 0L;

	j = 0L;
	for ( WORD y = 0 ; y < wDY ; y++ )
	{
		i = j;
		j += wDX + 1;
		for ( WORD x = 0 ; x < wDX ; x++ )
		{
			pGeometry->SetFace( k, j + x, i + x + 1, i + x );
			k++;
			pGeometry->SetFace( k, i + x + 1, j + x, j + x + 1 );
			k++;
		}
	}

	bSurface = TRUE;
	bHitbox = FALSE;
}



VOID SURFACE12::Render ( CAMERA12* _pCamera )
{
	if ( bSurface == FALSE ) UpdateSurface();

	if ( bRaytrace == TRUE )
		Raytrace( _pCamera );
	else
		OBJECT12::Render( _pCamera );
}



VOID SURFACE12::Raytrace ( CAMERA12* _pCamera )
{
	if ( bVisible == FALSE ) return;

	pRender->lpD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

	pRender->lpD3DDevice->SetVertexShader( pRender->lpSurfaceShader->lpVertexShader );
	pRender->lpD3DDevice->SetPixelShader( pRender->lpSurfaceShader->lpPixelShader );

	pRender->lpSurfaceShader->SetVSDefault();

	D3DXMATRIX matWorldViewProj = Matrix() * pScene->Matrix() * _pCamera->Matrix();
	D3DXMatrixTranspose( &matWorldViewProj, &matWorldViewProj );
	pRender->lpSurfaceShader->SetVSMatrix( "matWorldViewProj", &matWorldViewProj );

	pRender->lpSurfaceShader->SetPSDefault();

	D3DXMATRIX matWorld = Matrix();
	D3DXMatrixTranspose( &matWorld, &matWorld );
	pRender->lpSurfaceShader->SetPSMatrix( "matWorld", &matWorld );

	D3DXMATRIX matWorldInverse = Matrix();
	D3DXMatrixInverse( &matWorldInverse, NULL, &matWorldInverse );
	D3DXMatrixTranspose( &matWorldInverse, &matWorldInverse );
	pRender->lpSurfaceShader->SetPSMatrix( "matWorldInverse", &matWorldInverse );

	D3DXVECTOR4 vCamera = D3DXVECTOR4( _pCamera->GetCenter(), 1.0f );
	pRender->lpSurfaceShader->SetPSVector( "vRayOrigin", &vCamera );

	D3DXVECTOR4 vFactor = D3DXVECTOR4( (FLOAT)_pCamera->Width(), (FLOAT)_pCamera->Height(), 0.0f, 0.0f );
	pRender->lpSurfaceShader->SetPSVector( "vFactor", &vFactor );

	D3DXVECTOR4 vNode[16];
	for ( WORD k = 0 ; k < 16 ; k++ )
		vNode[k] = D3DXVECTOR4( pNode[k].x, pNode[k].y, pNode[k].z, 0.0f );
	pRender->lpSurfaceShader->SetPSVectorArray( "vNode", vNode, 16 );

	D3DXVECTOR4 vNodeDU[12];
	vNodeDU[ 0] = vNode[ 1] - vNode[ 0]; vNodeDU[ 1] = vNode[ 2] - vNode[ 1]; vNodeDU[ 2] = vNode[ 3] - vNode[ 2];
	vNodeDU[ 3] = vNode[ 5] - vNode[ 4]; vNodeDU[ 4] = vNode[ 6] - vNode[ 5]; vNodeDU[ 5] = vNode[ 7] - vNode[ 6];
	vNodeDU[ 6] = vNode[ 9] - vNode[ 8]; vNodeDU[ 7] = vNode[10] - vNode[ 9]; vNodeDU[ 8] = vNode[11] - vNode[10];
	vNodeDU[ 9] = vNode[13] - vNode[12]; vNodeDU[10] = vNode[14] - vNode[13]; vNodeDU[11] = vNode[15] - vNode[14];
	pRender->lpSurfaceShader->SetPSVectorArray( "vNodeDU", vNodeDU, 12 );

	D3DXVECTOR4 vNodeDV[12];
	vNodeDV[ 0] = vNode[ 4] - vNode[ 0]; vNodeDV[ 1] = vNode[ 5] - vNode[ 1]; vNodeDV[ 2] = vNode[ 6] - vNode[ 2]; vNodeDV[ 3] = vNode[ 7] - vNode[ 3];
	vNodeDV[ 4] = vNode[ 8] - vNode[ 4]; vNodeDV[ 5] = vNode[ 9] - vNode[ 5]; vNodeDV[ 6] = vNode[10] - vNode[ 6]; vNodeDV[ 7] = vNode[11] - vNode[ 7];
	vNodeDV[ 8] = vNode[12] - vNode[ 8]; vNodeDV[ 9] = vNode[13] - vNode[ 9]; vNodeDV[10] = vNode[14] - vNode[10]; vNodeDV[11] = vNode[15] - vNode[11];
	pRender->lpSurfaceShader->SetPSVectorArray( "vNodeDV", vNodeDV, 12 );

	pRender->lpSurfaceShader->SetPSTexture( "smpBuffer", pRender->lpRayTexture );

	pRender->lpSurfaceShader->SetPSFloat( "fZPlane", _pCamera->ZNearPlane() );
	pRender->lpSurfaceShader->SetPSFloat( "fZFactor", _pCamera->ZFarPlane() - _pCamera->ZNearPlane() );

	pGeometry->Render();

	pRender->lpD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULLMODE_DEFAULT );
}
