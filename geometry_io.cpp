
#include "render.h"
#include "geometry.h"
#include "impulse.h"
#include "engine.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



BOOLEAN GEOMETRY12::QuickLoad ( LPSTR _sFile )
{
	if ( pResource )
		pResource->DelEntity( this );

	pResource = pEngine->GetResource( _sFile );

	if ( pResource )
	{
		pResource->AddEntity( this );

		if ( ppVertex )
		{
			for ( DWORD i = 0L ; i < dwVertex ; i++ )
				if ( ppVertex[i] ) 
					delete ppVertex[i];

			delete [] ppVertex;
		}

		if ( ppFace )
		{
			for ( DWORD i = 0L ; i < dwFace ; i++ )
				if ( ppFace[i] ) 
					delete ppFace[i];

			delete [] ppFace;
		}

		if ( ppLine )
		{
			for ( DWORD i = 0L ; i < dwLine ; i++ )
				if ( ppLine[i] ) 
					delete ppLine[i];

			delete [] ppLine;
		}

		if ( lpVertexBuffer )
			lpVertexBuffer->Release();

		if ( lpIndexBuffer )
			lpIndexBuffer->Release();

		GEOMETRY12* pSource = (GEOMETRY12*)pResource->Entity();

		pSource->AddRef();

		if ( pSource->bGeometry == FALSE ) pSource->UpdateGeometry();

		vMin = pSource->vMin;
		vMax = pSource->vMax;

		dwFVF = pSource->dwFVF;

		dwVertexSize = pSource->dwVertexSize;
		dwIndexSize = pSource->dwIndexSize;

		dwVertex = pSource->dwVertex;
		ppVertex = pSource->ppVertex;

		dwFace = pSource->dwFace;
		ppFace = pSource->ppFace;

		dwLine = pSource->dwLine;
		ppLine = pSource->ppLine;

		lpVertexBuffer = pSource->lpVertexBuffer;
		lpVertexBuffer->AddRef();

		lpIndexBuffer = pSource->lpIndexBuffer;
		lpIndexBuffer->AddRef();
	}
	else
	{
		Load( _sFile );

		pResource = pEngine->AddResource( this, _sFile );
	}

	return 1;
}

BOOLEAN GEOMETRY12::QuickSave ( LPSTR _sFile )
{
	if ( pResource )
		pResource->DelEntity( this );

	pResource = pEngine->GetResource( _sFile );

	if ( pResource )
		pEngine->DelResource( _sFile );

	Save( _sFile );

	pResource = pEngine->AddResource( this, _sFile );

	return 1;
}



BOOLEAN GEOMETRY12::Load ( LPSTR _sFile )
{
	if ( _sFile == NULL )
	{
		pLog->Push( __FILE__, __LINE__, CODE_ERROR, CODE_GEOMETRY12, 0x0001, this, NULL, NULL ); return 0;
	}
	else if ( CheckFile( _sFile ) == 0 ) 
	{
		pLog->Push( __FILE__, __LINE__, CODE_ERROR, CODE_GEOMETRY12, 0x0002, this, NULL, _sFile ); return 0;
	}

	FILE* pFile = NULL;

	fopen_s(&pFile, _sFile, "rb");

	fseek( pFile, 0, SEEK_SET );

	DWORD dwCount = 0;

	fread( &dwFVF, sizeof(DWORD), 1, pFile );

	fread( &dwCount, sizeof(DWORD), 1, pFile );
	SetVertexCount( dwCount );
	for ( DWORD p = 0 ; p < dwCount ; p++ )
	{
		if ( dwFVF & D3DFVF_XYZ )
		{
			fread( &ppVertex[p]->x, sizeof(FLOAT), 1, pFile );
			fread( &ppVertex[p]->y, sizeof(FLOAT), 1, pFile );
			fread( &ppVertex[p]->z, sizeof(FLOAT), 1, pFile );
		}
		if ( dwFVF & D3DFVF_NORMAL )
		{
			fread( &ppVertex[p]->l, sizeof(FLOAT), 1, pFile );
			fread( &ppVertex[p]->m, sizeof(FLOAT), 1, pFile );
			fread( &ppVertex[p]->n, sizeof(FLOAT), 1, pFile );
		}
		if ( dwFVF & D3DFVF_DIFFUSE )
		{
			fread( &ppVertex[p]->r, sizeof(FLOAT), 1, pFile );
			fread( &ppVertex[p]->g, sizeof(FLOAT), 1, pFile );
			fread( &ppVertex[p]->b, sizeof(FLOAT), 1, pFile );
			fread( &ppVertex[p]->a, sizeof(FLOAT), 1, pFile );
		}
		if ( dwFVF & D3DFVF_TEX1 )
		{
			fread( &ppVertex[p]->u, sizeof(FLOAT), 1, pFile );
			fread( &ppVertex[p]->v, sizeof(FLOAT), 1, pFile );
		}
	}

	fread( &dwCount, sizeof(DWORD), 1, pFile );
	SetFaceCount( dwCount );
	for ( DWORD q = 0 ; q < dwCount ; q++ )
	{
		fread( &ppFace[q]->a, sizeof(DWORD), 1, pFile );
		fread( &ppFace[q]->b, sizeof(DWORD), 1, pFile );
		fread( &ppFace[q]->c, sizeof(DWORD), 1, pFile );
	}

	fread( &dwCount, sizeof(DWORD), 1, pFile );
	SetLineCount( dwCount );
	for ( DWORD r = 0 ; r < dwCount ; r++ )
	{
		fread( &ppLine[r]->a, sizeof(DWORD), 1, pFile );
		fread( &ppLine[r]->b, sizeof(DWORD), 1, pFile );
	}

	fclose( pFile );

	return 1;
}

BOOLEAN GEOMETRY12::Save ( LPSTR _sFile )
{
	FILE* pFile = NULL;
	if ( fopen_s(&pFile, _sFile, "wb") )
		return 0;

	fseek( pFile, 0, SEEK_SET );

	fwrite( &dwFVF, sizeof(DWORD), 1, pFile );

	fwrite( &dwVertex, sizeof(DWORD), 1, pFile );
	for ( DWORD p = 0 ; p < dwVertex ; p++ )
	{
		if ( dwFVF & D3DFVF_XYZ )
		{
			fwrite( &ppVertex[p]->x, sizeof(FLOAT), 1, pFile );
			fwrite( &ppVertex[p]->y, sizeof(FLOAT), 1, pFile );
			fwrite( &ppVertex[p]->z, sizeof(FLOAT), 1, pFile );
		}
		if ( dwFVF & D3DFVF_NORMAL )
		{
			fwrite( &ppVertex[p]->l, sizeof(FLOAT), 1, pFile );
			fwrite( &ppVertex[p]->m, sizeof(FLOAT), 1, pFile );
			fwrite( &ppVertex[p]->n, sizeof(FLOAT), 1, pFile );
		}
		if ( dwFVF & D3DFVF_DIFFUSE )
		{
			fwrite( &ppVertex[p]->r, sizeof(FLOAT), 1, pFile );
			fwrite( &ppVertex[p]->g, sizeof(FLOAT), 1, pFile );
			fwrite( &ppVertex[p]->b, sizeof(FLOAT), 1, pFile );
			fwrite( &ppVertex[p]->a, sizeof(FLOAT), 1, pFile );
		}
		if ( dwFVF & D3DFVF_TEX1 )
		{
			fwrite( &ppVertex[p]->u, sizeof(FLOAT), 1, pFile );
			fwrite( &ppVertex[p]->v, sizeof(FLOAT), 1, pFile );
		}
	}

	fwrite( &dwFace, sizeof(DWORD), 1, pFile );
	for ( DWORD q = 0 ; q < dwFace ; q++ )
	{
		fwrite( &ppFace[q]->a, sizeof(DWORD), 1, pFile );
		fwrite( &ppFace[q]->b, sizeof(DWORD), 1, pFile );
		fwrite( &ppFace[q]->c, sizeof(DWORD), 1, pFile );
	}

	fwrite( &dwLine, sizeof(DWORD), 1, pFile );
	for ( DWORD r = 0 ; r < dwLine ; r++ )
	{
		fwrite( &ppLine[r]->a, sizeof(DWORD), 1, pFile );
		fwrite( &ppLine[r]->b, sizeof(DWORD), 1, pFile );
	}

	fclose( pFile );

	return 1;
}
