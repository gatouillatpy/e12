
#include "render.h"
#include "geometry.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID GEOMETRY12::UpdateGeometry ( )
{
	DWORD dwOffset = 0L;

	LPVOID pData = NULL;

	if ( lpVertexBuffer ) lpVertexBuffer->Release();

	dwVertexSize = 3 * sizeof(FLOAT);
	if ( dwFVF & D3DFVF_NORMAL ) dwVertexSize += 3 * sizeof(FLOAT);
	if ( dwFVF & D3DFVF_DIFFUSE ) dwVertexSize += 1 * sizeof(DWORD);
	if ( dwFVF & D3DFVF_TEX1 ) dwVertexSize += 2 * sizeof(FLOAT);

	pRender->lpD3DDevice->CreateVertexBuffer( dwVertexSize * dwVertex, D3DUSAGE_WRITEONLY, dwFVF, D3DPOOL_DEFAULT,
		&lpVertexBuffer, NULL );

	lpVertexBuffer->Lock( 0, dwVertexSize * dwVertex, (LPVOID*)&pData, 0 );
	for ( DWORD i = dwOffset = 0L ; i < dwVertex ; i++ )
	{
		if ( ppVertex[i]->x < vMin.x ) vMin.x = ppVertex[i]->x;
		if ( ppVertex[i]->y < vMin.y ) vMin.y = ppVertex[i]->y;
		if ( ppVertex[i]->z < vMin.z ) vMin.z = ppVertex[i]->z;
		if ( ppVertex[i]->x > vMax.x ) vMax.x = ppVertex[i]->x;
		if ( ppVertex[i]->y > vMax.y ) vMax.y = ppVertex[i]->y;
		if ( ppVertex[i]->z > vMax.z ) vMax.z = ppVertex[i]->z;

		*(FLOAT*)(((BYTE*)pData)+dwOffset) = ppVertex[i]->x; dwOffset += sizeof(FLOAT);
		*(FLOAT*)(((BYTE*)pData)+dwOffset) = ppVertex[i]->y; dwOffset += sizeof(FLOAT);
		*(FLOAT*)(((BYTE*)pData)+dwOffset) = ppVertex[i]->z; dwOffset += sizeof(FLOAT);
		if ( dwFVF & D3DFVF_NORMAL )
		{
			*(FLOAT*)(((BYTE*)pData)+dwOffset) = ppVertex[i]->l; dwOffset += sizeof(FLOAT);
			*(FLOAT*)(((BYTE*)pData)+dwOffset) = ppVertex[i]->m; dwOffset += sizeof(FLOAT);
			*(FLOAT*)(((BYTE*)pData)+dwOffset) = ppVertex[i]->n; dwOffset += sizeof(FLOAT);
		}
		if ( dwFVF & D3DFVF_DIFFUSE )
		{
			*(DWORD*)(((BYTE*)pData)+dwOffset) = D3DCOLOR_COLORVALUE(ppVertex[i]->r, ppVertex[i]->g, ppVertex[i]->b, ppVertex[i]->a); dwOffset += sizeof(DWORD);
		}
		if ( dwFVF & D3DFVF_TEX1 )
		{
			*(FLOAT*)(((BYTE*)pData)+dwOffset) = ppVertex[i]->u; dwOffset += sizeof(FLOAT);
			*(FLOAT*)(((BYTE*)pData)+dwOffset) = ppVertex[i]->v; dwOffset += sizeof(FLOAT);
		}
	}
	lpVertexBuffer->Unlock();

	if ( lpIndexBuffer ) lpIndexBuffer->Release();

	if ( dwVertex < 65536 )
		dwIndexSize = sizeof(WORD);
	else
		dwIndexSize = sizeof(DWORD);

	pRender->lpD3DDevice->CreateIndexBuffer( dwIndexSize * ( 3 * dwFace + 2 * dwLine ), D3DUSAGE_WRITEONLY, (dwVertex < 65536) ? D3DFMT_INDEX16 : D3DFMT_INDEX32, D3DPOOL_DEFAULT,
		&lpIndexBuffer, NULL );

	lpIndexBuffer->Lock( 0, dwIndexSize * ( 3 * dwFace + 2 * dwLine ), (LPVOID*)&pData, 0 );
	for ( DWORD i = dwOffset = 0L ; i < dwFace ; i++ )
	{
		if ( dwVertex < 65536 )
		{
			*(WORD*)(((BYTE*)pData)+dwOffset) = (WORD)ppFace[i]->a; dwOffset += sizeof(WORD);
			*(WORD*)(((BYTE*)pData)+dwOffset) = (WORD)ppFace[i]->b; dwOffset += sizeof(WORD);
			*(WORD*)(((BYTE*)pData)+dwOffset) = (WORD)ppFace[i]->c; dwOffset += sizeof(WORD);
		}
		else
		{
			*(DWORD*)(((BYTE*)pData)+dwOffset) = ppFace[i]->a; dwOffset += sizeof(DWORD);
			*(DWORD*)(((BYTE*)pData)+dwOffset) = ppFace[i]->b; dwOffset += sizeof(DWORD);
			*(DWORD*)(((BYTE*)pData)+dwOffset) = ppFace[i]->c; dwOffset += sizeof(DWORD);
		}
	}
	for ( DWORD i = dwOffset = 0L ; i < dwLine ; i++ )
	{
		if ( dwVertex < 65536 )
		{
			*(WORD*)(((BYTE*)pData)+dwOffset) = (WORD)ppLine[i]->a; dwOffset += sizeof(WORD);
			*(WORD*)(((BYTE*)pData)+dwOffset) = (WORD)ppLine[i]->b; dwOffset += sizeof(WORD);
		}
		else
		{
			*(DWORD*)(((BYTE*)pData)+dwOffset) = ppLine[i]->a; dwOffset += sizeof(DWORD);
			*(DWORD*)(((BYTE*)pData)+dwOffset) = ppLine[i]->b; dwOffset += sizeof(DWORD);
		}
	}
	lpIndexBuffer->Unlock();

	/* la géométrie est désormais à jour */
	bGeometry = TRUE;
}



VOID GEOMETRY12::Render ( )
{
	if ( bGeometry == FALSE ) UpdateGeometry();

	pRender->lpD3DDevice->SetFVF( dwFVF );

	pRender->lpD3DDevice->SetStreamSource( 0, lpVertexBuffer, 0, dwVertexSize );
	pRender->lpD3DDevice->SetIndices( lpIndexBuffer );

	if ( dwFace > 0 )
		pRender->lpD3DDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, dwVertex, 0, dwFace );
	if ( dwLine > 0 )
		pRender->lpD3DDevice->DrawIndexedPrimitive( D3DPT_LINELIST, 0, 0, dwVertex, dwFace * 3, dwLine );
}

VOID GEOMETRY12::Render ( DWORD dwFaceStart, DWORD dwFaceCount )
{
	if ( !bGeometry ) UpdateGeometry();

	pRender->lpD3DDevice->SetFVF( dwFVF );

	pRender->lpD3DDevice->SetStreamSource( 0, lpVertexBuffer, 0, dwVertexSize );
	pRender->lpD3DDevice->SetIndices( lpIndexBuffer );

	if ( dwFaceCount > 0 && dwFaceStart + dwFaceCount <= dwFace )
		pRender->lpD3DDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, dwVertex, dwFaceStart, dwFaceCount );
}



VOID GEOMETRY12::DrawVertices ( )
{
	if ( bGeometry == FALSE ) UpdateGeometry();

	LPDIRECT3DVERTEXBUFFER9 tVertexBuffer ;

	pRender->lpD3DDevice->CreateVertexBuffer( 192 * dwVertex, D3DUSAGE_WRITEONLY, dwFVF, D3DPOOL_DEFAULT,
		&tVertexBuffer, NULL );

	DWORD dwOffset = 0L;

	LPVOID pData = NULL;

	tVertexBuffer->Lock( 0, 192 * dwVertex, (LPVOID*)&pData, 0 );
	for ( DWORD i = dwOffset = 0L ; i < dwVertex ; i++ )
	{
		FLOAT fColor[4];
		fColor[3] = (FLOAT)(((DWORD)(&ppVertex[i]) >> 24) & 0xff) / 255.0f;
		fColor[0] = (FLOAT)(((DWORD)(&ppVertex[i]) >> 16) & 0xff) / 255.0f;
		fColor[1] = (FLOAT)(((DWORD)(&ppVertex[i]) >> 8) & 0xff) / 255.0f;
		fColor[2] = (FLOAT)(((DWORD)(&ppVertex[i])) & 0xff) / 255.0f;

		*(FLOAT*)(((BYTE*)pData)+dwOffset) = ppVertex[i]->x - 1.0f; dwOffset += sizeof(FLOAT);
		*(FLOAT*)(((BYTE*)pData)+dwOffset) = ppVertex[i]->y - 1.0f; dwOffset += sizeof(FLOAT);
		*(FLOAT*)(((BYTE*)pData)+dwOffset) = ppVertex[i]->z + 0.0f; dwOffset += sizeof(FLOAT);
		*(DWORD*)(((BYTE*)pData)+dwOffset) = D3DCOLOR_COLORVALUE(fColor[0], fColor[1], fColor[2], fColor[3]); dwOffset += sizeof(DWORD);
		*(FLOAT*)(((BYTE*)pData)+dwOffset) = ppVertex[i]->x - 1.0f; dwOffset += sizeof(FLOAT);
		*(FLOAT*)(((BYTE*)pData)+dwOffset) = ppVertex[i]->y + 1.0f; dwOffset += sizeof(FLOAT);
		*(FLOAT*)(((BYTE*)pData)+dwOffset) = ppVertex[i]->z + 0.0f; dwOffset += sizeof(FLOAT);
		*(DWORD*)(((BYTE*)pData)+dwOffset) = D3DCOLOR_COLORVALUE(fColor[0], fColor[1], fColor[2], fColor[3]); dwOffset += sizeof(DWORD);
		*(FLOAT*)(((BYTE*)pData)+dwOffset) = ppVertex[i]->x + 1.0f; dwOffset += sizeof(FLOAT);
		*(FLOAT*)(((BYTE*)pData)+dwOffset) = ppVertex[i]->y - 1.0f; dwOffset += sizeof(FLOAT);
		*(FLOAT*)(((BYTE*)pData)+dwOffset) = ppVertex[i]->z + 0.0f; dwOffset += sizeof(FLOAT);
		*(DWORD*)(((BYTE*)pData)+dwOffset) = D3DCOLOR_COLORVALUE(fColor[0], fColor[1], fColor[2], fColor[3]); dwOffset += sizeof(DWORD);
		*(FLOAT*)(((BYTE*)pData)+dwOffset) = ppVertex[i]->x + 1.0f; dwOffset += sizeof(FLOAT);
		*(FLOAT*)(((BYTE*)pData)+dwOffset) = ppVertex[i]->y + 1.0f; dwOffset += sizeof(FLOAT);
		*(FLOAT*)(((BYTE*)pData)+dwOffset) = ppVertex[i]->z + 0.0f; dwOffset += sizeof(FLOAT);
		*(DWORD*)(((BYTE*)pData)+dwOffset) = D3DCOLOR_COLORVALUE(fColor[0], fColor[1], fColor[2], fColor[3]); dwOffset += sizeof(DWORD);

		*(FLOAT*)(((BYTE*)pData)+dwOffset) = ppVertex[i]->x + 0.0f; dwOffset += sizeof(FLOAT);
		*(FLOAT*)(((BYTE*)pData)+dwOffset) = ppVertex[i]->y - 1.0f; dwOffset += sizeof(FLOAT);
		*(FLOAT*)(((BYTE*)pData)+dwOffset) = ppVertex[i]->z - 1.0f; dwOffset += sizeof(FLOAT);
		*(DWORD*)(((BYTE*)pData)+dwOffset) = D3DCOLOR_COLORVALUE(fColor[0], fColor[1], fColor[2], fColor[3]); dwOffset += sizeof(DWORD);
		*(FLOAT*)(((BYTE*)pData)+dwOffset) = ppVertex[i]->x + 0.0f; dwOffset += sizeof(FLOAT);
		*(FLOAT*)(((BYTE*)pData)+dwOffset) = ppVertex[i]->y - 1.0f; dwOffset += sizeof(FLOAT);
		*(FLOAT*)(((BYTE*)pData)+dwOffset) = ppVertex[i]->z + 1.0f; dwOffset += sizeof(FLOAT);
		*(DWORD*)(((BYTE*)pData)+dwOffset) = D3DCOLOR_COLORVALUE(fColor[0], fColor[1], fColor[2], fColor[3]); dwOffset += sizeof(DWORD);
		*(FLOAT*)(((BYTE*)pData)+dwOffset) = ppVertex[i]->x + 0.0f; dwOffset += sizeof(FLOAT);
		*(FLOAT*)(((BYTE*)pData)+dwOffset) = ppVertex[i]->y + 1.0f; dwOffset += sizeof(FLOAT);
		*(FLOAT*)(((BYTE*)pData)+dwOffset) = ppVertex[i]->z - 1.0f; dwOffset += sizeof(FLOAT);
		*(DWORD*)(((BYTE*)pData)+dwOffset) = D3DCOLOR_COLORVALUE(fColor[0], fColor[1], fColor[2], fColor[3]); dwOffset += sizeof(DWORD);
		*(FLOAT*)(((BYTE*)pData)+dwOffset) = ppVertex[i]->x + 0.0f; dwOffset += sizeof(FLOAT);
		*(FLOAT*)(((BYTE*)pData)+dwOffset) = ppVertex[i]->y + 1.0f; dwOffset += sizeof(FLOAT);
		*(FLOAT*)(((BYTE*)pData)+dwOffset) = ppVertex[i]->z + 1.0f; dwOffset += sizeof(FLOAT);
		*(DWORD*)(((BYTE*)pData)+dwOffset) = D3DCOLOR_COLORVALUE(fColor[0], fColor[1], fColor[2], fColor[3]); dwOffset += sizeof(DWORD);

		*(FLOAT*)(((BYTE*)pData)+dwOffset) = ppVertex[i]->x - 1.0f; dwOffset += sizeof(FLOAT);
		*(FLOAT*)(((BYTE*)pData)+dwOffset) = ppVertex[i]->y + 0.0f; dwOffset += sizeof(FLOAT);
		*(FLOAT*)(((BYTE*)pData)+dwOffset) = ppVertex[i]->z - 1.0f; dwOffset += sizeof(FLOAT);
		*(DWORD*)(((BYTE*)pData)+dwOffset) = D3DCOLOR_COLORVALUE(fColor[0], fColor[1], fColor[2], fColor[3]); dwOffset += sizeof(DWORD);
		*(FLOAT*)(((BYTE*)pData)+dwOffset) = ppVertex[i]->x + 1.0f; dwOffset += sizeof(FLOAT);
		*(FLOAT*)(((BYTE*)pData)+dwOffset) = ppVertex[i]->y + 0.0f; dwOffset += sizeof(FLOAT);
		*(FLOAT*)(((BYTE*)pData)+dwOffset) = ppVertex[i]->z - 1.0f; dwOffset += sizeof(FLOAT);
		*(DWORD*)(((BYTE*)pData)+dwOffset) = D3DCOLOR_COLORVALUE(fColor[0], fColor[1], fColor[2], fColor[3]); dwOffset += sizeof(DWORD);
		*(FLOAT*)(((BYTE*)pData)+dwOffset) = ppVertex[i]->x - 1.0f; dwOffset += sizeof(FLOAT);
		*(FLOAT*)(((BYTE*)pData)+dwOffset) = ppVertex[i]->y + 0.0f; dwOffset += sizeof(FLOAT);
		*(FLOAT*)(((BYTE*)pData)+dwOffset) = ppVertex[i]->z + 1.0f; dwOffset += sizeof(FLOAT);
		*(DWORD*)(((BYTE*)pData)+dwOffset) = D3DCOLOR_COLORVALUE(fColor[0], fColor[1], fColor[2], fColor[3]); dwOffset += sizeof(DWORD);
		*(FLOAT*)(((BYTE*)pData)+dwOffset) = ppVertex[i]->x + 1.0f; dwOffset += sizeof(FLOAT);
		*(FLOAT*)(((BYTE*)pData)+dwOffset) = ppVertex[i]->y + 0.0f; dwOffset += sizeof(FLOAT);
		*(FLOAT*)(((BYTE*)pData)+dwOffset) = ppVertex[i]->z + 1.0f; dwOffset += sizeof(FLOAT);
		*(DWORD*)(((BYTE*)pData)+dwOffset) = D3DCOLOR_COLORVALUE(fColor[0], fColor[1], fColor[2], fColor[3]); dwOffset += sizeof(DWORD);
	}
	tVertexBuffer->Unlock();

	LPDIRECT3DINDEXBUFFER9 tIndexBuffer ;

	pRender->lpD3DDevice->CreateIndexBuffer( 72 * dwVertex, D3DUSAGE_WRITEONLY, D3DFMT_INDEX32, D3DPOOL_DEFAULT,
		&tIndexBuffer, NULL );

	tIndexBuffer->Lock( 0, 72 * dwVertex, (LPVOID*)&pData, 0 );
	for ( DWORD i = dwOffset = 0L ; i < dwVertex ; i++ )
	{
		*(DWORD*)(((BYTE*)pData)+dwOffset) = i * 12 +  0; dwOffset += sizeof(DWORD);
		*(DWORD*)(((BYTE*)pData)+dwOffset) = i * 12 +  1; dwOffset += sizeof(DWORD);
		*(DWORD*)(((BYTE*)pData)+dwOffset) = i * 12 +  2; dwOffset += sizeof(DWORD);
		*(DWORD*)(((BYTE*)pData)+dwOffset) = i * 12 +  3; dwOffset += sizeof(DWORD);
		*(DWORD*)(((BYTE*)pData)+dwOffset) = i * 12 +  2; dwOffset += sizeof(DWORD);
		*(DWORD*)(((BYTE*)pData)+dwOffset) = i * 12 +  1; dwOffset += sizeof(DWORD);

		*(DWORD*)(((BYTE*)pData)+dwOffset) = i * 12 +  4; dwOffset += sizeof(DWORD);
		*(DWORD*)(((BYTE*)pData)+dwOffset) = i * 12 +  5; dwOffset += sizeof(DWORD);
		*(DWORD*)(((BYTE*)pData)+dwOffset) = i * 12 +  6; dwOffset += sizeof(DWORD);
		*(DWORD*)(((BYTE*)pData)+dwOffset) = i * 12 +  7; dwOffset += sizeof(DWORD);
		*(DWORD*)(((BYTE*)pData)+dwOffset) = i * 12 +  6; dwOffset += sizeof(DWORD);
		*(DWORD*)(((BYTE*)pData)+dwOffset) = i * 12 +  5; dwOffset += sizeof(DWORD);

		*(DWORD*)(((BYTE*)pData)+dwOffset) = i * 12 +  8; dwOffset += sizeof(DWORD);
		*(DWORD*)(((BYTE*)pData)+dwOffset) = i * 12 +  9; dwOffset += sizeof(DWORD);
		*(DWORD*)(((BYTE*)pData)+dwOffset) = i * 12 + 10; dwOffset += sizeof(DWORD);
		*(DWORD*)(((BYTE*)pData)+dwOffset) = i * 12 + 11; dwOffset += sizeof(DWORD);
		*(DWORD*)(((BYTE*)pData)+dwOffset) = i * 12 + 10; dwOffset += sizeof(DWORD);
		*(DWORD*)(((BYTE*)pData)+dwOffset) = i * 12 +  9; dwOffset += sizeof(DWORD);
	}
	tIndexBuffer->Unlock();

	pRender->lpD3DDevice->SetFVF( D3DFVF_XYZ | D3DFVF_DIFFUSE );

	pRender->lpD3DDevice->SetStreamSource( 0, tVertexBuffer, 0, 16 );
	pRender->lpD3DDevice->SetIndices( tIndexBuffer );

	pRender->lpD3DDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, 12 * dwVertex, 0, 6 * dwVertex );

	tVertexBuffer->Release();
	tIndexBuffer->Release();
}



VOID GEOMETRY12::DrawFaces ( )
{
	if ( bGeometry == FALSE ) UpdateGeometry();

	LPDIRECT3DVERTEXBUFFER9 tVertexBuffer ;

	pRender->lpD3DDevice->CreateVertexBuffer( 48 * dwFace, D3DUSAGE_WRITEONLY, dwFVF, D3DPOOL_DEFAULT,
		&tVertexBuffer, NULL );

	DWORD dwOffset = 0L;

	LPVOID pData = NULL;

	tVertexBuffer->Lock( 0, 48 * dwFace, (LPVOID*)&pData, 0 );
	for ( DWORD i = dwOffset = 0L ; i < dwFace ; i++ )
	{
		FLOAT fColor[4];
		fColor[3] = (FLOAT)(((DWORD)(&ppVertex[i]) >> 24) & 0xff) / 255.0f;
		fColor[0] = (FLOAT)(((DWORD)(&ppVertex[i]) >> 16) & 0xff) / 255.0f;
		fColor[1] = (FLOAT)(((DWORD)(&ppVertex[i]) >> 8) & 0xff) / 255.0f;
		fColor[2] = (FLOAT)(((DWORD)(&ppVertex[i])) & 0xff) / 255.0f;

		*(FLOAT*)(((BYTE*)pData)+dwOffset) = ppVertex[ppFace[i]->a]->x; dwOffset += sizeof(FLOAT);
		*(FLOAT*)(((BYTE*)pData)+dwOffset) = ppVertex[ppFace[i]->a]->y; dwOffset += sizeof(FLOAT);
		*(FLOAT*)(((BYTE*)pData)+dwOffset) = ppVertex[ppFace[i]->a]->z; dwOffset += sizeof(FLOAT);
		*(DWORD*)(((BYTE*)pData)+dwOffset) = D3DCOLOR_COLORVALUE(fColor[0], fColor[1], fColor[2], fColor[3]); dwOffset += sizeof(DWORD);
		*(FLOAT*)(((BYTE*)pData)+dwOffset) = ppVertex[ppFace[i]->b]->x; dwOffset += sizeof(FLOAT);
		*(FLOAT*)(((BYTE*)pData)+dwOffset) = ppVertex[ppFace[i]->b]->y; dwOffset += sizeof(FLOAT);
		*(FLOAT*)(((BYTE*)pData)+dwOffset) = ppVertex[ppFace[i]->b]->z; dwOffset += sizeof(FLOAT);
		*(DWORD*)(((BYTE*)pData)+dwOffset) = D3DCOLOR_COLORVALUE(fColor[0], fColor[1], fColor[2], fColor[3]); dwOffset += sizeof(DWORD);
		*(FLOAT*)(((BYTE*)pData)+dwOffset) = ppVertex[ppFace[i]->c]->x; dwOffset += sizeof(FLOAT);
		*(FLOAT*)(((BYTE*)pData)+dwOffset) = ppVertex[ppFace[i]->c]->y; dwOffset += sizeof(FLOAT);
		*(FLOAT*)(((BYTE*)pData)+dwOffset) = ppVertex[ppFace[i]->c]->z; dwOffset += sizeof(FLOAT);
		*(DWORD*)(((BYTE*)pData)+dwOffset) = D3DCOLOR_COLORVALUE(fColor[0], fColor[1], fColor[2], fColor[3]); dwOffset += sizeof(DWORD);
	}
	tVertexBuffer->Unlock();

	LPDIRECT3DINDEXBUFFER9 tIndexBuffer ;

	pRender->lpD3DDevice->CreateIndexBuffer( 12 * dwFace, D3DUSAGE_WRITEONLY, D3DFMT_INDEX32, D3DPOOL_DEFAULT,
		&tIndexBuffer, NULL );

	tIndexBuffer->Lock( 0, 12 * dwFace, (LPVOID*)&pData, 0 );
	for ( DWORD i = dwOffset = 0L ; i < dwFace ; i++ )
	{
		*(DWORD*)(((BYTE*)pData)+dwOffset) = i * 3 + 0; dwOffset += sizeof(DWORD);
		*(DWORD*)(((BYTE*)pData)+dwOffset) = i * 3 + 1; dwOffset += sizeof(DWORD);
		*(DWORD*)(((BYTE*)pData)+dwOffset) = i * 3 + 2; dwOffset += sizeof(DWORD);
	}
	tIndexBuffer->Unlock();

	pRender->lpD3DDevice->SetFVF( D3DFVF_XYZ | D3DFVF_DIFFUSE );

	pRender->lpD3DDevice->SetStreamSource( 0, tVertexBuffer, 0, 16 );
	pRender->lpD3DDevice->SetIndices( tIndexBuffer );

	pRender->lpD3DDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, 48 * dwFace, 0, dwFace );

	tVertexBuffer->Release();
	tIndexBuffer->Release();
}