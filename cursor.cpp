
#include "cursor.h"
#include "interface.h"
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



CURSOR12::CURSOR12 ( RENDER12* _pRender ) : CONTROL12( _pRender )
{
	pTexture = NULL;

	lpPixelShader = NULL;
	lpVertexShader = NULL;
	lpVertexDeclaration = NULL;
	lpVertexBuffer = NULL;
	lpIndexBuffer = NULL;

	fWidth = 0.05f;
	fHeight = 0.05f;

	LPVOID pData = NULL;

	const FLOAT aSurfaceVertices[] = { -1.0f, -1.0f, 0.0f, 0.0f, 1.0f,
									   +1.0f, -1.0f, 0.0f, 1.0f, 1.0f,
									   -1.0f, +1.0f, 0.0f, 0.0f, 0.0f,
									   +1.0f, +1.0f, 0.0f, 1.0f, 0.0f };

	if( FAILED( pRender->lpD3DDevice->CreateVertexBuffer( sizeof(aSurfaceVertices), D3DUSAGE_WRITEONLY, D3DFVF_XYZ | D3DFVF_TEX1, D3DPOOL_DEFAULT,
		&lpVertexBuffer, NULL ) ) ) return;

	lpVertexBuffer->Lock( 0, sizeof(aSurfaceVertices), (LPVOID*)&pData, 0 );
	CopyMemory( pData, aSurfaceVertices, sizeof(aSurfaceVertices) );
	lpVertexBuffer->Unlock();

	const WORD aSurfaceIndices[] = { 0, 1, 2, 3, 2, 1 };

	if( FAILED( pRender->lpD3DDevice->CreateIndexBuffer( sizeof(aSurfaceIndices), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_DEFAULT,
		&lpIndexBuffer, NULL ) ) ) return;

	lpIndexBuffer->Lock( 0, sizeof(aSurfaceIndices), (LPVOID*)&pData, 0 );
	CopyMemory( pData, aSurfaceIndices, sizeof(aSurfaceIndices) );
	lpIndexBuffer->Unlock();

	ID3DXBuffer* pCode = NULL;

	const D3DVERTEXELEMENT9 aSurfaceDeclaration[] = 
	{
		{ 0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 12, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
		D3DDECL_END()
	};

	pRender->lpD3DDevice->CreateVertexDeclaration( aSurfaceDeclaration, &lpVertexDeclaration );

	const CHAR sVertexShader[] =
		"vs.1.1 \n"\
		\
		"dcl_position v0 \n"\
		"dcl_texcoord v1 \n"\
		\
		"mul r0, v0, c0 \n"\
		"add r1, r0, c1 \n"\
		"mov oPos, r1 \n"\
		\
		"mov oT0, v1 \n";
	D3DXAssembleShader( sVertexShader, strlen(sVertexShader), NULL, NULL, NULL, &pCode, NULL );

	if( FAILED( pRender->lpD3DDevice->CreateVertexShader( (DWORD*)pCode->GetBufferPointer(), &lpVertexShader ) ) ) return;

	if( pCode )
	{
		pCode->Release(); 
		pCode = NULL; 
	}

	const CHAR sPixelShader[] = 
		"ps.1.1 \n"\
		\
		"tex t0 \n"\
		"mov r0, t0 \n";
	D3DXAssembleShader( sPixelShader, strlen(sPixelShader), NULL, NULL, NULL, &pCode, NULL );

	if( FAILED( pRender->lpD3DDevice->CreatePixelShader( (DWORD*)pCode->GetBufferPointer(), &lpPixelShader ) ) ) return;

	if( pCode )
	{
		pCode->Release(); 
		pCode = NULL; 
	}
}

CURSOR12::~CURSOR12 ( )
{
	if ( lpPixelShader )
		lpPixelShader->Release();

	if ( lpVertexShader )
		lpVertexShader->Release();

	if ( lpVertexDeclaration )
		lpVertexDeclaration->Release();

	if ( lpVertexBuffer )
		lpVertexBuffer->Release();

	if ( lpIndexBuffer )
		lpIndexBuffer->Release();
}



VOID CURSOR12::Update ( )
{
	fLeft = (FLOAT)pRender->lpWindow->X / (FLOAT)pRender->lpWindow->ClientWidth() * 2.0f;
	fTop = (FLOAT)pRender->lpWindow->Y / (FLOAT)pRender->lpWindow->ClientHeight() * 2.0f;
}



VOID CURSOR12::Render ( )
{
	if ( bVisible == FALSE ) return;
	if ( pTexture == NULL ) return;

	pRender->lpD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	pRender->lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	pRender->lpD3DDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );

	FLOAT c0[4] = { fWidth, fHeight, 1.0f, 1.0f };
	FLOAT c1[4] = { fLeft + fWidth - 1.0f, 1.0f - fTop - fHeight, 0.0f, 0.0f };

	pRender->lpD3DDevice->SetVertexShaderConstantF( 0, c0, 1 );
	pRender->lpD3DDevice->SetVertexShaderConstantF( 1, c1, 1 );

	pRender->lpD3DDevice->SetStreamSource( 0, lpVertexBuffer, 0, 20 );
	pRender->lpD3DDevice->SetIndices( lpIndexBuffer );

	pRender->lpD3DDevice->SetTexture( 0, pTexture->lpD3DTexture );

	pRender->lpD3DDevice->SetVertexDeclaration( lpVertexDeclaration );
	pRender->lpD3DDevice->SetVertexShader( lpVertexShader );
	pRender->lpD3DDevice->SetPixelShader( lpPixelShader );

	pRender->lpD3DDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2 );

	pRender->lpD3DDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE );
}
