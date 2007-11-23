
#include "render.h"
#include "geometry.h"
#include "engine.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID GEOMETRY12::Copy ( GEOMETRY12* _pDestination )
{
	/* copie du type des vertices */
	_pDestination->dwFVF = dwFVF;

	/* copie du nombre de vertices, de faces, et de lignes */
	_pDestination->dwVertex = dwVertex;
	_pDestination->dwFace = dwFace;
	_pDestination->dwLine = dwLine;

	/* copie des vertices */
	_pDestination->ppVertex = (VERTEX**) malloc( dwVertex * sizeof(LPVOID) );
	for ( DWORD i = 0L ; i < dwVertex ; i++ )
	{
		_pDestination->ppVertex[i] = new VERTEX;
		CopyMemory( _pDestination->ppVertex[i], ppVertex[i], sizeof(VERTEX) );
	}

	/* copie des faces */
	_pDestination->ppFace = (FACE**) malloc( dwFace * sizeof(LPVOID) );
	for ( DWORD i = 0L ; i < dwFace ; i++ )
	{
		_pDestination->ppFace[i] = new FACE;
		CopyMemory( _pDestination->ppFace[i], ppFace[i], sizeof(FACE) );
	}

	/* copie des lignes */
	_pDestination->ppLine = (LINE**) malloc( dwLine * sizeof(LPVOID) );
	for ( DWORD i = 0L ; i < dwLine ; i++ )
	{
		_pDestination->ppLine[i] = new LINE;
		CopyMemory( _pDestination->ppLine[i], ppLine[i], sizeof(LINE) );
	}
}



GEOMETRY12* GEOMETRY12::Copy ( )
{
	/* creation de la géométrie */
	GEOMETRY12* pGeometry = pRender->AddGeometry();

	/* copie du contenu */
	Copy( pGeometry );

	return pGeometry;
}
