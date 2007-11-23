
#include "box.h"
#include "scene.h"
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



BOX12::BOX12 ( RENDER12* _pRender ) : OBJECT12( _pRender )
{
}



BOX12* BOX12::Copy( BOOLEAN bCopyGeometry, BOOLEAN bCopyTexture )
{
	/* création de l'objet */
	BOX12* pObject = new BOX12( pRender );

	/* copie du contenu commun */
	OBJECT12::Copy( pObject, bCopyGeometry, bCopyTexture );

	return pObject;
}



VOID BOX12::Create ( FLOAT _fWidth, FLOAT _fHeight, FLOAT _fLength, BOOLEAN bNormal, BOOLEAN bUVMap )
{
	if ( pGeometry ) delete pGeometry;
	pGeometry = new GEOMETRY12( pRender );
	pGeometry->SetVertexCount( 8L );
	pGeometry->SetFaceCount( 12L );

	pGeometry->SetVertexPoint( 0, -0.5f * _fWidth, -0.5f * _fHeight, -0.5f * _fLength );
	pGeometry->SetVertexPoint( 1, -0.5f * _fWidth, +0.5f * _fHeight, -0.5f * _fLength );
	pGeometry->SetVertexPoint( 2, +0.5f * _fWidth, +0.5f * _fHeight, -0.5f * _fLength );
	pGeometry->SetVertexPoint( 3, +0.5f * _fWidth, -0.5f * _fHeight, -0.5f * _fLength );
	pGeometry->SetVertexPoint( 4, -0.5f * _fWidth, -0.5f * _fHeight, +0.5f * _fLength );
	pGeometry->SetVertexPoint( 5, +0.5f * _fWidth, -0.5f * _fHeight, +0.5f * _fLength );
	pGeometry->SetVertexPoint( 6, +0.5f * _fWidth, +0.5f * _fHeight, +0.5f * _fLength );
	pGeometry->SetVertexPoint( 7, -0.5f * _fWidth, +0.5f * _fHeight, +0.5f * _fLength );

	if ( bNormal )
	{
		pGeometry->SetVertexNormal( 0, -1.0f, -1.0f, -1.0f );
		pGeometry->SetVertexNormal( 1, -1.0f, +1.0f, -1.0f );
		pGeometry->SetVertexNormal( 2, +1.0f, +1.0f, -1.0f );
		pGeometry->SetVertexNormal( 3, +1.0f, -1.0f, -1.0f );
		pGeometry->SetVertexNormal( 4, -1.0f, -1.0f, +1.0f );
		pGeometry->SetVertexNormal( 5, +1.0f, -1.0f, +1.0f );
		pGeometry->SetVertexNormal( 6, +1.0f, +1.0f, +1.0f );
		pGeometry->SetVertexNormal( 7, -1.0f, +1.0f, +1.0f );
	}

	if ( bUVMap )
	{
		pGeometry->SetVertexUVMap( 0, 0.0f, 1.0f );
		pGeometry->SetVertexUVMap( 1, 0.0f, 0.0f );
		pGeometry->SetVertexUVMap( 2, 1.0f, 0.0f );
		pGeometry->SetVertexUVMap( 3, 1.0f, 1.0f );
		pGeometry->SetVertexUVMap( 4, 0.0f, 1.0f );
		pGeometry->SetVertexUVMap( 5, 1.0f, 1.0f );
		pGeometry->SetVertexUVMap( 6, 1.0f, 0.0f );
		pGeometry->SetVertexUVMap( 7, 0.0f, 0.0f );
	}

	pGeometry->SetFace(  0, 2, 1, 0 );
	pGeometry->SetFace(  1, 0, 3, 2 );
	pGeometry->SetFace(  2, 6, 5, 4 );
	pGeometry->SetFace(  3, 4, 7, 6 );
	pGeometry->SetFace(  4, 5, 3, 0 );
	pGeometry->SetFace(  5, 0, 4, 5 );
	pGeometry->SetFace(  6, 6, 2, 3 );
	pGeometry->SetFace(  7, 3, 5, 6 );
	pGeometry->SetFace(  8, 7, 1, 2 );
	pGeometry->SetFace(  9, 2, 6, 7 );
	pGeometry->SetFace( 10, 4, 0, 1 );
	pGeometry->SetFace( 11, 1, 7, 4 );
}



VOID BOX12::Create ( FLOAT _fWidth, FLOAT _fHeight, FLOAT _fLength, DWORD _nDX, DWORD _nDY, DWORD _nDZ, BOOLEAN bNormal, BOOLEAN bUVMap )
{
	if ( pGeometry ) delete pGeometry;
	pGeometry = new GEOMETRY12( pRender );
	pGeometry->SetVertexCount( 2L * ( (_nDX + 1) * (_nDY + 1) + (_nDY + 1) * (_nDZ + 1) + (_nDZ + 1) * (_nDX + 1) ) );
	pGeometry->SetFaceCount( 4L * ( _nDX * _nDY + _nDY * _nDZ + _nDZ * _nDX ) );

	DWORD i, j, k;

	FLOAT l = _fWidth / (FLOAT)_nDX;
	FLOAT m = _fHeight / (FLOAT)_nDY;
	FLOAT n = _fLength / (FLOAT)_nDZ;

	FLOAT p = 1.0f / (FLOAT)_nDX;
	FLOAT q = 1.0f / (FLOAT)_nDY;
	FLOAT r = 1.0f / (FLOAT)_nDZ;

	FLOAT u, v, w;
	FLOAT tu, tv;

	k = 0L;

	v = -0.5f * _fHeight;
	w = -0.5f * _fLength;
	tv = 1.0f;
	for ( DWORD y = 0L ; y <= _nDY ; y++ )
	{
		u = -0.5f * _fWidth;
		tu = 0.0f;
		for ( DWORD x = 0L ; x <= _nDX ; x++ )
		{
			pGeometry->SetVertexPoint( k, u, v, w );
			if ( bNormal )
				pGeometry->SetVertexNormal( k, 0.0f, 0.0f, -1.0f );
			if ( bUVMap )
				pGeometry->SetVertexUVMap( k, tu, tv );
			u += l;
			tu += p;
			k++;
		}
		v += m;
		tv -= q;
	}

	v = -0.5f * _fHeight;
	w = +0.5f * _fLength;
	tv = 1.0f;
	for ( DWORD y = 0L ; y <= _nDY ; y++ )
	{
		u = -0.5f * _fWidth;
		tu = 1.0f;
		for ( DWORD x = 0L ; x <= _nDX ; x++ )
		{
			pGeometry->SetVertexPoint( k, u, v, w );
			if ( bNormal )
				pGeometry->SetVertexNormal( k, 0.0f, 0.0f, +1.0f );
			if ( bUVMap )
				pGeometry->SetVertexUVMap( k, tu, tv );
			u += l;
			tu -= p;
			k++;
		}
		v += m;
		tv -= q;
	}

	u = -0.5f * _fWidth;
	w = -0.5f * _fLength;
	tv = 0.0f;
	for ( DWORD z = 0L ; z <= _nDZ ; z++ )
	{
		v = -0.5f * _fHeight;
		tu = 1.0f;
		for ( DWORD y = 0L ; y <= _nDY ; y++ )
		{
			pGeometry->SetVertexPoint( k, u, v, w );
			if ( bNormal )
				pGeometry->SetVertexNormal( k, -1.0f, 0.0f, 0.0f );
			if ( bUVMap )
				pGeometry->SetVertexUVMap( k, tv, tu );
			v += m;
			tu -= q;
			k++;
		}
		w += n;
		tv += r;
	}

	u = +0.5f * _fWidth;
	w = -0.5f * _fLength;
	tv = 1.0f;
	for ( DWORD z = 0L ; z <= _nDZ ; z++ )
	{
		v = -0.5f * _fHeight;
		tu = 1.0f;
		for ( DWORD y = 0L ; y <= _nDY ; y++ )
		{
			pGeometry->SetVertexPoint( k, u, v, w );
			if ( bNormal )
				pGeometry->SetVertexNormal( k, +1.0f, 0.0f, 0.0f );
			if ( bUVMap )
				pGeometry->SetVertexUVMap( k, tv, tu );
			v += m;
			tu -= q;
			k++;
		}
		w += n;
		tv -= r;
	}

	u = -0.5f * _fWidth;
	v = -0.5f * _fHeight;
	tv = 1.0f;
	for ( DWORD x = 0L ; x <= _nDX ; x++ )
	{
		w = -0.5f * _fLength;
		tu = 0.0f;
		for ( DWORD z = 0L ; z <= _nDZ ; z++ )
		{
			pGeometry->SetVertexPoint( k, u, v, w );
			if ( bNormal )
				pGeometry->SetVertexNormal( k, 0.0f, -1.0f, 0.0f );
			if ( bUVMap )
				pGeometry->SetVertexUVMap( k, tu, tv );
			w += n;
			tu += r;
			k++;
		}
		u += l;
		tv -= p;
	}

	u = -0.5f * _fWidth;
	v = +0.5f * _fHeight;
	tv = 1.0f;
	for ( DWORD x = 0L ; x <= _nDX ; x++ )
	{
		w = -0.5f * _fLength;
		tu = 1.0f;
		for ( DWORD z = 0L ; z <= _nDZ ; z++ )
		{
			pGeometry->SetVertexPoint( k, u, v, w );
			if ( bNormal )
				pGeometry->SetVertexNormal( k, 0.0f, +1.0f, 0.0f );
			if ( bUVMap )
				pGeometry->SetVertexUVMap( k, tu, tv );
			w += n;
			tu -= r;
			k++;
		}
		u += l;
		tv -= p;
	}

	k = 0L;

	j = 0L;
	for ( DWORD y = 0 ; y < _nDY ; y++ )
	{
		i = j;
		j += _nDX + 1;
		for ( DWORD x = 0 ; x < _nDX ; x++ )
		{
			pGeometry->SetFace( k, i + x, i + x + 1, j + x );
			k++;
			pGeometry->SetFace( k, j + x + 1, j + x, i + x + 1 );
			k++;
		}
	}

	j += _nDX + 1;
	for ( DWORD y = 0 ; y < _nDY ; y++ )
	{
		i = j;
		j += _nDX + 1;
		for ( DWORD x = 0 ; x < _nDX ; x++ )
		{
			pGeometry->SetFace( k, j + x, i + x + 1, i + x );
			k++;
			pGeometry->SetFace( k, i + x + 1, j + x, j + x + 1 );
			k++;
		}
	}

	j += _nDX + 1;
	for ( DWORD z = 0 ; z < _nDZ ; z++ )
	{
		i = j;
		j += _nDY + 1;
		for ( DWORD y = 0 ; y < _nDY ; y++ )
		{
			pGeometry->SetFace( k, i + y, i + y + 1, j + y );
			k++;
			pGeometry->SetFace( k, j + y + 1, j + y, i + y + 1 );
			k++;
		}
	}

	j += _nDY + 1;
	for ( DWORD z = 0 ; z < _nDZ ; z++ )
	{
		i = j;
		j += _nDY + 1;
		for ( DWORD y = 0 ; y < _nDY ; y++ )
		{
			pGeometry->SetFace( k, j + y, i + y + 1, i + y );
			k++;
			pGeometry->SetFace( k, i + y + 1, j + y, j + y + 1 );
			k++;
		}
	}

	j += _nDY + 1;
	for ( DWORD x = 0 ; x < _nDX ; x++ )
	{
		i = j;
		j += _nDZ + 1;
		for ( DWORD z = 0 ; z < _nDZ ; z++ )
		{
			pGeometry->SetFace( k, i + z, i + z + 1, j + z );
			k++;
			pGeometry->SetFace( k, j + z + 1, j + z, i + z + 1 );
			k++;
		}
	}

	j += _nDZ + 1;
	for ( DWORD x = 0 ; x < _nDX ; x++ )
	{
		i = j;
		j += _nDZ + 1;
		for ( DWORD z = 0 ; z < _nDZ ; z++ )
		{
			pGeometry->SetFace( k, j + z, i + z + 1, i + z );
			k++;
			pGeometry->SetFace( k, i + z + 1, j + z, j + z + 1 );
			k++;
		}
	}
}
