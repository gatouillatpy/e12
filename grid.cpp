
#include "grid.h"
#include "scene.h"
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



GRID12::GRID12 ( RENDER12* _pRender ) : OBJECT12( _pRender )
{
}



GRID12* GRID12::Copy( BOOLEAN bCopyGeometry, BOOLEAN bCopyTexture )
{
	/* création de l'objet */
	GRID12* pObject = new GRID12( pRender );

	/* copie du contenu commun */
	OBJECT12::Copy( pObject, bCopyGeometry, bCopyTexture );

	return pObject;
}



VOID GRID12::Create ( FLOAT _fWidth, FLOAT _fHeight, WORD _nDX, WORD _nDY )
{
	if ( pGeometry ) delete pGeometry;
	pGeometry = new GEOMETRY12( pRender );
	pGeometry->SetVertexCount( 2 * (_nDX + 1) +  2 * (_nDY + 1) );
	pGeometry->SetLineCount( (_nDX + 1) + (_nDY + 1) );

	DWORD i, j;

	FLOAT p = _fWidth / (FLOAT)_nDX;
	FLOAT q = _fHeight / (FLOAT)_nDY;

	FLOAT u, v;

	i = 0L;
	j = 0L;

	u = -0.5f * _fWidth;
	for ( WORD x = 0L ; x <= _nDX ; x++ )
	{
		pGeometry->SetLine( j, i, i + 1 );
		j++;
		v = -0.5f * _fHeight;
		pGeometry->SetVertexPoint( i, u, v, 0.0f );
		i++;
		v = +0.5f * _fHeight;
		pGeometry->SetVertexPoint( i, u, v, 0.0f );
		i++;
		u += p;
	}

	v = -0.5f * _fHeight;
	for ( WORD y = 0L ; y <= _nDY ; y++ )
	{
		pGeometry->SetLine( j, i, i + 1 );
		j++;
		u = -0.5f * _fWidth;
		pGeometry->SetVertexPoint( i, u, v, 0.0f );
		i++;
		u = +0.5f * _fWidth;
		pGeometry->SetVertexPoint( i, u, v, 0.0f );
		i++;
		v += q;
	}
}
