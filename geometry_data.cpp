
#include "render.h"
#include "geometry.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



D3DXVECTOR3 GEOMETRY12::Min ( )
{
	if ( !bGeometry ) UpdateGeometry();

	return vMin;
}

D3DXVECTOR3 GEOMETRY12::Max ( )
{
	if ( !bGeometry ) UpdateGeometry();

	return vMax;
}



VOID GEOMETRY12::SetVertexCount ( DWORD _dwCount )
{
	if ( ppVertex )
	{
		for ( DWORD i = _dwCount ; i < dwVertex ; i++ )
			if ( ppVertex[i] ) 
				delete ppVertex[i];
	}
	dwVertex = _dwCount;
	ppVertex = (VERTEX**) realloc( ppVertex, dwVertex * sizeof(LPVOID) );
	for ( DWORD i = 0L ; i < dwVertex ; i++ )
		ppVertex[i] = new VERTEX;

	bGeometry = FALSE;
}



VOID GEOMETRY12::SetFaceCount ( DWORD _dwCount )
{
	if ( ppFace )
	{
		for ( DWORD i = _dwCount ; i < dwFace ; i++ )
			if ( ppFace[i] ) 
				delete ppFace[i];
	}
	dwFace = _dwCount;
	ppFace = (FACE**) realloc( ppFace, dwFace * sizeof(LPVOID) );
	for ( DWORD i = 0L ; i < dwFace ; i++ )
		ppFace[i] = new FACE;

	bGeometry = FALSE;
}



VOID GEOMETRY12::SetLineCount ( DWORD _dwCount )
{
	if ( ppLine )
	{
		for ( DWORD i = _dwCount ; i < dwLine ; i++ )
			if ( ppLine[i] ) 
				delete ppLine[i];
	}
	dwLine = _dwCount;
	ppLine = (LINE**) realloc( ppLine, dwLine * sizeof(LPVOID) );
	for ( DWORD i = 0L ; i < dwLine ; i++ )
		ppLine[i] = new LINE;

	bGeometry = FALSE;
}



VOID GEOMETRY12::AddVertex ( DWORD _dwIndex )
{
	if ( _dwIndex > dwVertex ) return;

	dwVertex++;
	ppVertex = (VERTEX**) realloc( ppVertex, dwVertex * sizeof(LPVOID) );
	ppVertex[dwVertex-1] = new VERTEX;
	for ( DWORD i = dwVertex-1 ; i > _dwIndex ; i-- )
		ppVertex[i] = ppVertex[i-1];

	bGeometry = FALSE;
}

// c'est catastrophique, on réarrange les vertices sans tenir compte des indices !!
VOID GEOMETRY12::DelVertex ( DWORD _dwIndex )
{
	if ( _dwIndex > dwVertex ) return;

	dwVertex--;
	for ( DWORD i = _dwIndex ; i < dwVertex ; i++ )
		ppVertex[i] = ppVertex[i+1];
	delete ppVertex[dwVertex];
	ppVertex = (VERTEX**) realloc( ppVertex, dwVertex * sizeof(LPVOID) );

	bGeometry = FALSE;
}

VOID GEOMETRY12::SetVertexPoint ( DWORD _dwIndex, FLOAT _x, FLOAT _y, FLOAT _z )
{
	if ( _dwIndex > dwVertex-1 ) return;

	ppVertex[_dwIndex]->x = _x;
	ppVertex[_dwIndex]->y = _y;
	ppVertex[_dwIndex]->z = _z;

	dwFVF |= D3DFVF_XYZ;

	bGeometry = FALSE;
}

VOID GEOMETRY12::SetVertexNormal ( DWORD _dwIndex, FLOAT _l, FLOAT _m, FLOAT _n )
{
	if ( _dwIndex > dwVertex-1 ) return;

	ppVertex[_dwIndex]->l = _l;
	ppVertex[_dwIndex]->m = _m;
	ppVertex[_dwIndex]->n = _n;

	dwFVF |= D3DFVF_NORMAL;

	bGeometry = FALSE;
}

VOID GEOMETRY12::SetVertexColor ( DWORD _dwIndex, FLOAT _r, FLOAT _g, FLOAT _b, FLOAT _a )
{
	if ( _dwIndex > dwVertex-1 ) return;

	ppVertex[_dwIndex]->r = _r > 1.0f ? 1.0f : _r;
	ppVertex[_dwIndex]->g = _g > 1.0f ? 1.0f : _g;
	ppVertex[_dwIndex]->b = _b > 1.0f ? 1.0f : _b;
	ppVertex[_dwIndex]->a = _a > 1.0f ? 1.0f : _a;

	dwFVF |= D3DFVF_DIFFUSE;

	bGeometry = FALSE;
}

VOID GEOMETRY12::SetVertexUVMap ( DWORD _dwIndex, FLOAT _u, FLOAT _v )
{
	if ( _dwIndex > dwVertex-1 ) return;

	ppVertex[_dwIndex]->u = _u;
	ppVertex[_dwIndex]->v = _v;

	dwFVF |= D3DFVF_TEX1;
}

VERTEX* GEOMETRY12::GetVertex ( DWORD _dwIndex )
{
	if ( _dwIndex > dwVertex-1 ) return NULL;
	return ppVertex[_dwIndex];
}



VOID GEOMETRY12::AddFace ( DWORD _dwIndex, DWORD _a, DWORD _b, DWORD _c )
{
	if ( _dwIndex > dwFace ) return;

	dwFace++;
	ppFace = (FACE**) realloc( ppFace, dwFace * sizeof(LPVOID) );
	ppFace[dwFace-1] = new FACE;
	for ( DWORD i = dwFace - 1 ; i > _dwIndex ; i-- )
		ppFace[i] = ppFace[i-1];

	ppFace[_dwIndex]->a = _a;
	ppFace[_dwIndex]->b = _b;
	ppFace[_dwIndex]->c = _c;

	bGeometry = FALSE;
}

VOID GEOMETRY12::DelFace ( DWORD _dwIndex )
{
	if ( _dwIndex > dwFace ) return;

	dwFace--;
	for ( DWORD i = _dwIndex ; i < dwFace ; i++ )
		ppFace[i] = ppFace[i+1];
	delete ppFace[dwFace];
	ppFace = (FACE**) realloc( ppFace, dwFace * sizeof(LPVOID) );

	bGeometry = FALSE;
}

VOID GEOMETRY12::SetFace ( DWORD _dwIndex, DWORD _a, DWORD _b, DWORD _c )
{
	if ( _dwIndex > dwFace - 1 ) return;

	ppFace[_dwIndex]->a = _a;
	ppFace[_dwIndex]->b = _b;
	ppFace[_dwIndex]->c = _c;

	bGeometry = FALSE;
}

FACE* GEOMETRY12::GetFace ( DWORD _dwIndex )
{
	if ( _dwIndex > dwFace - 1 ) return NULL;
	return ppFace[_dwIndex];
}



VOID GEOMETRY12::SetModifier ( FLOAT _x, FLOAT _y, FLOAT _z, FLOAT _nx, FLOAT _ny, FLOAT _nz, FLOAT _p )
{
	for ( DWORD k = 0L ; k < dwVertex ; k++ )
	{
		D3DXVECTOR3 vLength = D3DXVECTOR3( ppVertex[k]->x - _x, ppVertex[k]->y - _y, ppVertex[k]->z - _z );
		FLOAT fLength = D3DXVec3LengthSq( &vLength );
		FLOAT fFactor = 1.0f / powf(fLength, 1.0f / _p);

		ppVertex[k]->x += (_nx - ppVertex[k]->x) * fFactor;
		ppVertex[k]->y += (_ny - ppVertex[k]->y) * fFactor;
		ppVertex[k]->z += (_nz - ppVertex[k]->z) * fFactor;
	}

	bGeometry = FALSE;
}

VOID GEOMETRY12::SetColor ( FLOAT _r, FLOAT _g, FLOAT _b, FLOAT _a )
{
	for ( DWORD k = 0L ; k < dwVertex ; k++ )
	{
		ppVertex[k]->r = _r;
		ppVertex[k]->g = _g;
		ppVertex[k]->b = _b;
		ppVertex[k]->a = _a;
	}

	dwFVF |= D3DFVF_DIFFUSE;

	bGeometry = FALSE;
}

VOID GEOMETRY12::SetLight ( FLOAT _x, FLOAT _y, FLOAT _z, FLOAT _r, FLOAT _g, FLOAT _b, FLOAT _a, FLOAT _p )
{
	for ( DWORD k = 0L ; k < dwVertex ; k++ )
	{
		D3DXVECTOR3 vLength = D3DXVECTOR3( ppVertex[k]->x - _x, ppVertex[k]->y - _y, ppVertex[k]->z - _z );
		FLOAT fLength = D3DXVec3LengthSq( &vLength );
		FLOAT fFactor = 1.0f / powf(fLength, 1.0f / _p);

		ppVertex[k]->r += _r * fFactor;
		if ( ppVertex[k]->r > 1.0f ) ppVertex[k]->r = 1.0f;
		ppVertex[k]->g += _g * fFactor;
		if ( ppVertex[k]->g > 1.0f ) ppVertex[k]->g = 1.0f;
		ppVertex[k]->b += _b * fFactor;
		if ( ppVertex[k]->b > 1.0f ) ppVertex[k]->b = 1.0f;
		ppVertex[k]->a += _a * fFactor;
		if ( ppVertex[k]->a > 1.0f ) ppVertex[k]->a = 1.0f;
	}

	dwFVF |= D3DFVF_DIFFUSE;

	bGeometry = FALSE;
}


VOID GEOMETRY12::AddLine ( DWORD _dwIndex, DWORD _a, DWORD _b )
{
	if ( _dwIndex > dwLine ) return;

	dwLine++;
	ppLine = (LINE**) realloc( ppLine, dwLine * sizeof(LPVOID) );
	ppLine[dwLine-1] = new LINE;
	for ( DWORD i = dwLine - 1 ; i > _dwIndex ; i-- )
		ppLine[i] = ppLine[i-1];

	ppLine[_dwIndex]->a = _a;
	ppLine[_dwIndex]->b = _b;

	bGeometry = FALSE;
}

VOID GEOMETRY12::DelLine ( DWORD _dwIndex )
{
	if ( _dwIndex > dwLine ) return;

	dwLine--;
	for ( DWORD i = _dwIndex ; i < dwLine ; i++ )
		ppLine[i] = ppLine[i+1];
	delete ppLine[dwLine];
	ppLine = (LINE**) realloc( ppLine, dwLine * sizeof(LPVOID) );

	bGeometry = FALSE;
}

VOID GEOMETRY12::SetLine ( DWORD _dwIndex, DWORD _a, DWORD _b )
{
	if ( _dwIndex > dwLine - 1 ) return;

	ppLine[_dwIndex]->a = _a;
	ppLine[_dwIndex]->b = _b;

	bGeometry = FALSE;
}

LINE* GEOMETRY12::GetLine ( DWORD _dwIndex )
{
	if ( _dwIndex > dwLine - 1 ) return NULL;
	return ppLine[_dwIndex];
}
