
#include "render.h"
#include "geometry.h"
#include "engine.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



GEOMETRY12::GEOMETRY12 ( RENDER12* _pRender ) : ENTITY12( _pRender->iGeometry, _pRender->pEngine )
{
	pRender = _pRender;

	dwFVF = 0L;

	dwVertex = 0L;
	ppVertex = NULL;
	
	dwFace = 0L;
	ppFace = NULL;

	dwLine = 0L;
	ppLine = NULL;

	lpVertexBuffer = NULL;
	lpIndexBuffer = NULL;

	vMin = D3DXVECTOR3( +999999.999f, +999999.999f, +999999.999f );
	vMax = D3DXVECTOR3( -999999.999f, -999999.999f, -999999.999f );

	bGeometry = FALSE;
}

GEOMETRY12::~GEOMETRY12 ( )
{
	if ( pResource )
	{
		pResource->DelEntity( this );
	}
	else
	{
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
	}

	if ( lpVertexBuffer )
		lpVertexBuffer->Release();

	if ( lpIndexBuffer )
		lpIndexBuffer->Release();
}
