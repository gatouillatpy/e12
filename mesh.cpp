
#include "mesh.h"
#include "scene.h"
#include "render.h"

#include "debug.h"

#include <io.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



MESH12::MESH12 ( RENDER12* _pRender ) : OBJECT12( _pRender )
{
}



MESH12* MESH12::Copy( BOOLEAN bCopyGeometry, BOOLEAN bCopyTexture )
{
	/* création de l'objet */
	MESH12* pObject = new MESH12( pRender );

	/* copie du contenu commun */
	OBJECT12::Copy( pObject, bCopyGeometry, bCopyTexture );

	return pObject;
}



BOOLEAN MESH12::ImportX ( LPSTR _sFile )
{
	if ( _sFile == NULL )
	{
		pLog->Push( __FILE__, __LINE__, CODE_ERROR, CODE_MESH12, 0x0001, this, NULL, NULL ); return 0;
	}
	else if ( CheckFile( _sFile ) == 0 ) 
	{
		pLog->Push( __FILE__, __LINE__, CODE_ERROR, CODE_MESH12, 0x0002, this, NULL, _sFile ); return 0;
	}

	LPD3DXMESH tMesh = NULL;
	LPD3DXMESH pMesh = NULL;
	LPD3DXBUFFER pBuffer = NULL;
	DWORD dwMaterial = 0L;

	D3DXLoadMeshFromX( _sFile, D3DXMESH_SYSTEMMEM | D3DXMESH_32BIT, pRender->lpD3DDevice, NULL, &pBuffer, NULL,
		&dwMaterial, &tMesh );

	tMesh->Optimize( D3DXMESHOPT_ATTRSORT, NULL, NULL, NULL, NULL, &pMesh );
	tMesh->Release();
	
	D3DVERTEXELEMENT9 aDeclaration[MAX_FVF_DECL_SIZE];
	pMesh->GetDeclaration( aDeclaration );

	if ( pGeometry ) delete pGeometry;
	pGeometry = new GEOMETRY12( pRender );
	pGeometry->SetVertexCount( pMesh->GetNumVertices() );
	pGeometry->SetFaceCount( pMesh->GetNumFaces() );

	DWORD dwOffset;
	LPVOID pData;
	 
	dwOffset = 0L;
	LPDIRECT3DVERTEXBUFFER9 pVertexBuffer = NULL;
	pMesh->GetVertexBuffer( &pVertexBuffer );
	pVertexBuffer->Lock( 0, 0, (LPVOID*)&pData, 0 );
	for ( DWORD i = 0L ; i < pMesh->GetNumVertices() ; i++ )
	{
		if ( pMesh->GetFVF() & D3DFVF_XYZ )
		{
			FLOAT x, y, z;
			x = *(FLOAT*)(((BYTE*)pData)+dwOffset); dwOffset += sizeof(FLOAT);
			y = *(FLOAT*)(((BYTE*)pData)+dwOffset); dwOffset += sizeof(FLOAT);
			z = *(FLOAT*)(((BYTE*)pData)+dwOffset); dwOffset += sizeof(FLOAT);
			pGeometry->SetVertexPoint( i, x, y, z );
		}
		if ( pMesh->GetFVF() & D3DFVF_NORMAL )
		{
			FLOAT l, m, n;
			l = *(FLOAT*)(((BYTE*)pData)+dwOffset); dwOffset += sizeof(FLOAT);
			m = *(FLOAT*)(((BYTE*)pData)+dwOffset); dwOffset += sizeof(FLOAT);
			n = *(FLOAT*)(((BYTE*)pData)+dwOffset); dwOffset += sizeof(FLOAT);
			pGeometry->SetVertexNormal( i, l, m, n );
		}
		if ( pMesh->GetFVF() & D3DFVF_DIFFUSE )
		{
			DWORD dwDiffuse;
			dwDiffuse = *(DWORD*)(((BYTE*)pData)+dwOffset); dwOffset += sizeof(DWORD);
			FLOAT r, g, b, a;
			a = (FLOAT)((dwDiffuse >> 24) & 0xFF) / 255.0f;
			r = (FLOAT)((dwDiffuse >> 16) & 0xFF) / 255.0f;
			g = (FLOAT)((dwDiffuse >> 8) & 0xFF) / 255.0f;
			b = (FLOAT)(dwDiffuse & 0xFF) / 255.0f;
			pGeometry->SetVertexColor( i, r, g, b, a );
		}
		if ( pMesh->GetFVF() & D3DFVF_TEX1 )
		{
			FLOAT u, v;
			u = *(FLOAT*)(((BYTE*)pData)+dwOffset); dwOffset += sizeof(FLOAT);
			v = *(FLOAT*)(((BYTE*)pData)+dwOffset); dwOffset += sizeof(FLOAT);
			pGeometry->SetVertexUVMap( i, u, v );
		}
	}
	pVertexBuffer->Unlock();
	pVertexBuffer->Release();

	dwOffset = 0L;
	LPDIRECT3DINDEXBUFFER9 pIndexBuffer = NULL;
	pMesh->GetIndexBuffer( &pIndexBuffer );
	pIndexBuffer->Lock( 0, 0, (LPVOID*)&pData, 0 );
	for ( DWORD i = 0L ; i < pMesh->GetNumFaces() ; i++ )
	{
		DWORD a, b, c;
		a = *(DWORD*)(((BYTE*)pData)+dwOffset); dwOffset += sizeof(DWORD);
		b = *(DWORD*)(((BYTE*)pData)+dwOffset); dwOffset += sizeof(DWORD);
		c = *(DWORD*)(((BYTE*)pData)+dwOffset); dwOffset += sizeof(DWORD);
		if ( a > 150 )
			a = a;
		if ( b > 150 )
			b = b;
		if ( c > 150 )
			c = c;
		pGeometry->SetFace( i, a, b, c );
	}
	pIndexBuffer->Unlock();
	pIndexBuffer->Release();

	D3DXMATERIAL* pD3DXMaterial = (D3DXMATERIAL*)pBuffer->GetBufferPointer();

	D3DXATTRIBUTERANGE* pTable = NULL;
	pTable = new D3DXATTRIBUTERANGE[dwMaterial];
	pMesh->GetAttributeTable( pTable, &dwMaterial );

	CHAR sPath[256];
	DWORD k = StringLength( _sFile );
	while ( _sFile[k-1] != '\\' ) k--;

	if ( dwMaterial == 1L )
	{
		if ( pD3DXMaterial )
		{
			pMaterial = new D3DMATERIAL9;
			*pMaterial = pD3DXMaterial[0].MatD3D;
			pMaterial->Ambient = pMaterial->Diffuse;
		}

		if ( pD3DXMaterial[0].pTextureFilename && lstrlen( pD3DXMaterial[0].pTextureFilename ) > 0 )
		{
			TEXTURE12* pTexture = new TEXTURE12( pRender );

			StringCopyN( sPath, 256, _sFile, k );
			StringCat( sPath, 256, pD3DXMaterial[0].pTextureFilename );

			if ( pTexture->Import( sPath ) )
			{
				AddTexture( pTexture );
			}
			else
			{
				if ( pTexture->Import( pD3DXMaterial[0].pTextureFilename ) )
					AddTexture( pTexture );
				else
					pTexture->Release();
			}
		}
	}
	else
	{
		for ( DWORD i = 0L ; i < dwMaterial ; i++ )
		{
			MESH12* pChild = new MESH12( pRender );
			AddChild( pChild );

			pChild->pGeometry = pGeometry;
			pChild->dwFaceStart = pTable[i].FaceStart;
			pChild->dwFaceCount = pTable[i].FaceCount;

			if ( pD3DXMaterial )
			{
				pChild->pMaterial = new D3DMATERIAL9;
				*pChild->pMaterial = pD3DXMaterial[i].MatD3D;
				pChild->pMaterial->Ambient = pChild->pMaterial->Diffuse;
			}

			if ( pD3DXMaterial[i].pTextureFilename && StringLength( pD3DXMaterial[i].pTextureFilename ) > 0 )
			{
				TEXTURE12* pTexture = new TEXTURE12( pRender );

				StringCopyN( sPath, 256, _sFile, k );
				StringCat( sPath, 256, pD3DXMaterial[i].pTextureFilename );

				if ( pTexture->Import( sPath ) )
				{
					pChild->AddTexture( pTexture );
				}
				else
				{
					if ( pTexture->Import( pD3DXMaterial[i].pTextureFilename ) )
						pChild->AddTexture( pTexture );
					else
						pTexture->Release();
				}
			}
		}

		pGeometry = NULL;
	}

	delete [] pTable;
	pBuffer->Release();
	pMesh->Release();

	return 1;
}

BOOLEAN MESH12::Import3DS ( LPSTR _sFile )
{
	if ( _sFile == NULL )
	{
		pLog->Push( __FILE__, __LINE__, CODE_ERROR, CODE_MESH12, 0x0003, this, NULL, NULL ); return 0;
	}
	else if ( CheckFile( _sFile ) == 0 ) 
	{
		pLog->Push( __FILE__, __LINE__, CODE_ERROR, CODE_MESH12, 0x0004, this, NULL, _sFile ); return 0;
	}

	struct MLIMATERIAL
	{
		CHAR Name[256];
		D3DCOLORVALUE Ambient;
		D3DCOLORVALUE Diffuse;
		D3DCOLORVALUE Specular;
		CHAR Texture[256];
	};

	int i;
	unsigned char c;
	unsigned char r, g, b;

	BOOLEAN bDiffuse, bAmbient, bSpecular;

	FILE* pFile;

	CHAR sPath[256];
	DWORD k = StringLength( _sFile );
	while ( _sFile[k-1] != '\\' ) k--;

	DWORD dwMaterialCount = 0;
	MLIMATERIAL* pMaterialArray = NULL;

	USHORT nChunkID;
	UINT nChunkSize;

	USHORT nQuantity;
	USHORT nFlags;

	CHAR tName[256];

	if ( fopen_s(&pFile, _sFile, "rb") ) return 0;

	MESH12* pChild = NULL;

	while ( ftell(pFile) < _filelength(_fileno(pFile)) )
	{
		fread (&nChunkID, sizeof(nChunkID), 1, pFile);
		fread (&nChunkSize, sizeof(nChunkSize), 1, pFile);

		CONST DWORD CHUNK_MAIN = 0x4D4D;
		CONST DWORD CHUNK_EDITOR = 0x3D3D;
		CONST DWORD CHUNK_OBJECT = 0x4000;
		CONST DWORD CHUNK_MESH = 0x4100;
		CONST DWORD CHUNK_MESH_VERTEXDATA = 0x4110;
		CONST DWORD CHUNK_MESH_INDEXDATA = 0x4120;
		CONST DWORD CHUNK_MESH_MATERIAL = 0x4130;
		CONST DWORD CHUNK_MESH_MAPDATA = 0x4140;
		CONST DWORD CHUNK_MATERIAL = 0xAFFF;
		CONST DWORD CHUNK_MATERIAL_NAME = 0xA000;
		CONST DWORD CHUNK_MATERIAL_AMBIENT = 0xA010;
		CONST DWORD CHUNK_MATERIAL_DIFFUSE = 0xA020;
		CONST DWORD CHUNK_MATERIAL_SPECULAR = 0xA030;
		CONST DWORD CHUNK_MATERIAL_MAP = 0xA200;
		CONST DWORD CHUNK_MATERIAL_MAP_FILE = 0xA300;
		CONST DWORD CHUNK_COLOR_RGB1 = 0x0011;

		switch (nChunkID)
		{
			case CHUNK_MAIN: 
				break;
			case CHUNK_EDITOR:
				break;
			case CHUNK_OBJECT: 
				i = 0;
				do
				{
					fread( &c, 1, 1, pFile );
					tName[i] = c;
					i++;
				} while ( c != '\0' && i < 256 );
				SetName( tName );

				pChild = new MESH12( pRender );
				AddChild( pChild );
				pChild->pGeometry = new GEOMETRY12( pRender );

				break;
			case CHUNK_MESH:
				break;				
			case CHUNK_MESH_VERTEXDATA: 
				fread( &nQuantity, sizeof(nQuantity), 1, pFile );
				pChild->pGeometry->SetVertexCount( nQuantity );

				for ( i = 0 ; i < nQuantity ; i++ )
				{
					FLOAT x, y, z;

					fread( &x, sizeof(x), 1, pFile );
					fread( &y, sizeof(y), 1, pFile );
					fread( &z, sizeof(z), 1, pFile );

					pChild->pGeometry->SetVertexPoint( i, x, z, y );
				}

				break;	
			case CHUNK_MESH_INDEXDATA:
				fread( &nQuantity, sizeof(nQuantity), 1, pFile );
				pChild->pGeometry->SetFaceCount( nQuantity );

				for ( i = 0 ; i < nQuantity ; i++ )
				{
					USHORT a, b, c;

					fread( &c, sizeof(c), 1, pFile );
					fread( &b, sizeof(b), 1, pFile );
					fread( &a, sizeof(a), 1, pFile );

					fread( &nFlags, sizeof(nFlags), 1, pFile);

					pChild->pGeometry->SetFace( i, a, b, c );
				}

				break;				
			case CHUNK_MESH_MAPDATA:
				fread ( &nQuantity, sizeof(nQuantity), 1, pFile );

				for ( i = 0 ; i < nQuantity ; i++ )
				{
					FLOAT u, v;

					fread( &u, sizeof(u), 1, pFile );
					fread( &v, sizeof(v), 1, pFile );

					pChild->pGeometry->SetVertexUVMap( i, u, v );
				}

				break;
			case CHUNK_MESH_MATERIAL:
				i = 0;
				do
				{
					fread( &c, 1, 1, pFile );
					tName[i] = c;
					i++;
				} while ( c != '\0' );

				for ( DWORD n = 0 ; n < dwMaterialCount ; n++ )
				{
					if ( StringCompare( pMaterialArray[n].Name, tName ) == 0 )
					{
						pChild->pMaterial = new D3DMATERIAL9;
						pChild->pMaterial->Diffuse = pMaterialArray[n].Diffuse;
						pChild->pMaterial->Ambient = pMaterialArray[n].Ambient;
						pChild->pMaterial->Emissive = pMaterialArray[n].Ambient;
						pChild->pMaterial->Specular = pMaterialArray[n].Specular;

						TEXTURE12* pTexture = new TEXTURE12( pRender );

						StringCopyN( sPath, 256, _sFile, k );
						StringCat( sPath, 256, pMaterialArray[n].Texture );

						if ( pTexture->Import( sPath ) )
						{
							pChild->AddTexture( pTexture );
						}
						else
						{
							if ( pTexture->Import( pMaterialArray[n].Texture ) )
								pChild->AddTexture( pTexture );
							else
								pTexture->Release();
						}
					}
				}

				fread( &nQuantity, sizeof(WORD), 1, pFile );
				fseek( pFile, sizeof(WORD) * nQuantity, SEEK_CUR );

				break;
			case CHUNK_MATERIAL: 
				break;
			case CHUNK_MATERIAL_NAME: 
				dwMaterialCount++;
				pMaterialArray = (MLIMATERIAL*)realloc(pMaterialArray, dwMaterialCount * sizeof(MLIMATERIAL));

				i = 0;
				do
				{
					fread( &c, 1, 1, pFile );
					pMaterialArray[dwMaterialCount-1].Name[i] = c;
					i++;
				} while ( c != '\0' );

				break;
			case CHUNK_MATERIAL_AMBIENT: 
				bDiffuse = FALSE;
				bSpecular = FALSE;
				bAmbient = TRUE;
				break;
			case CHUNK_MATERIAL_DIFFUSE: 
				bDiffuse = TRUE;
				bSpecular = FALSE;
				bAmbient = FALSE;
				break;
			case CHUNK_MATERIAL_SPECULAR: 
				bDiffuse = FALSE;
				bSpecular = TRUE;
				bAmbient = FALSE;
				break;
			case CHUNK_MATERIAL_MAP: 
				break;
			case CHUNK_MATERIAL_MAP_FILE: 
				i = 0;
				do
				{
					fread( &c, 1, 1, pFile );
					pMaterialArray[dwMaterialCount-1].Texture[i] = c;
					i++;
				} while ( c != '\0' && i < 256 );

				break;
			case CHUNK_COLOR_RGB1:
				if ( bDiffuse )
				{
					fread( &r, sizeof(r), 1, pFile );
					fread( &g, sizeof(g), 1, pFile );
					fread( &b, sizeof(b), 1, pFile );
					pMaterialArray[dwMaterialCount-1].Diffuse.r = (float)r / 255.0f;
					pMaterialArray[dwMaterialCount-1].Diffuse.g = (float)g / 255.0f;
					pMaterialArray[dwMaterialCount-1].Diffuse.b = (float)b / 255.0f;
					pMaterialArray[dwMaterialCount-1].Diffuse.a = 1.0f;
				}
				else if ( bAmbient )
				{
					fread( &r, sizeof(r), 1, pFile );
					fread( &g, sizeof(g), 1, pFile );
					fread( &b, sizeof(b), 1, pFile );
					pMaterialArray[dwMaterialCount-1].Ambient.r = (float)r / 255.0f;
					pMaterialArray[dwMaterialCount-1].Ambient.g = (float)g / 255.0f;
					pMaterialArray[dwMaterialCount-1].Ambient.b = (float)b / 255.0f;
					pMaterialArray[dwMaterialCount-1].Ambient.a = 1.0f;
				}
				else if ( bSpecular )
				{
					fread( &r, sizeof(r), 1, pFile );
					fread( &g, sizeof(g), 1, pFile );
					fread( &b, sizeof(b), 1, pFile );
					pMaterialArray[dwMaterialCount-1].Specular.r = (float)r / 255.0f;
					pMaterialArray[dwMaterialCount-1].Specular.g = (float)g / 255.0f;
					pMaterialArray[dwMaterialCount-1].Specular.b = (float)b / 255.0f;
					pMaterialArray[dwMaterialCount-1].Specular.a = 1.0f;
				}
				
				break;
			default:
				fseek( pFile, nChunkSize - 6, SEEK_CUR );
		} 
	}

	fclose(pFile);

	if ( pMaterialArray )
		free(pMaterialArray);

	return 1;
}
