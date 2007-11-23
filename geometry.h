
#pragma once



#include "util.h"

#include "entity.h"
#include "resource.h"



// c'est trop moche, de revérifier s'il y a une ressource ou non dans le detructeur, il vaudrait mieux coder des classes pour
// la gestion des vertices, faces et lignes, peut être basées sur des LPD3DXBUFFER ?



struct DLL VERTEX
{
	FLOAT x, y, z;
	FLOAT l, m, n;
	FLOAT r, g, b, a;
	FLOAT u, v;
};

struct DLL FACE
{
	DWORD a, b, c;
};

struct DLL LINE
{
	DWORD a, b;
};



class DLL GEOMETRY12 : public ENTITY12
{

	friend class RENDER12;

private:

	RENDER12* pRender ;

	BOOLEAN bGeometry ; // vrai si la géométrie est à jour, faux sinon

	/* attributs internes */
	
	D3DXVECTOR3 vMin ;
	D3DXVECTOR3 vMax ;

	LPDIRECT3DVERTEXBUFFER9 lpVertexBuffer ;
	LPDIRECT3DINDEXBUFFER9 lpIndexBuffer ;

	DWORD dwVertexSize ;
	DWORD dwIndexSize ;

	/* attributs externes */

	DWORD dwFVF ;

	DWORD dwVertex ;
	VERTEX** ppVertex ;
	
	DWORD dwFace ;
	FACE** ppFace ;

	DWORD dwLine ;
	LINE** ppLine ;

public:

	GEOMETRY12 ( RENDER12* _pRender ) ;
	virtual ~GEOMETRY12 ( ) ;

	VOID Copy ( GEOMETRY12* _pDestination ) ;
	GEOMETRY12* Copy ( ) ;

	/* geometry_data.cpp */

	VOID SetVertexCount ( DWORD _dwCount ) ;
	_inline DWORD VertexCount ( ) { return dwVertex; } ;

	VOID SetFaceCount ( DWORD _dwCount ) ;
	_inline DWORD FaceCount ( ) { return dwFace; } ;

	VOID SetLineCount ( DWORD _dwCount ) ;
	_inline DWORD LineCount ( ) { return dwFace; } ;

	VOID SetModifier ( FLOAT _x, FLOAT _y, FLOAT _z, FLOAT _nx, FLOAT _ny, FLOAT _nz, FLOAT _p ) ;
	VOID SetColor ( FLOAT _r, FLOAT _g, FLOAT _b, FLOAT _a ) ;
	VOID SetLight ( FLOAT _x, FLOAT _y, FLOAT _z, FLOAT _r, FLOAT _g, FLOAT _b, FLOAT _a, FLOAT _p ) ;

	VOID AddVertex ( DWORD _dwIndex ) ;
	VOID DelVertex ( DWORD _dwIndex ) ;
	VOID SetVertexPoint ( DWORD _dwIndex, FLOAT _x, FLOAT _y, FLOAT _z ) ;
	VOID SetVertexNormal ( DWORD _dwIndex, FLOAT _l, FLOAT _m, FLOAT _n ) ;
	VOID SetVertexColor ( DWORD _dwIndex, FLOAT _r, FLOAT _g, FLOAT _b, FLOAT _a ) ;
	VOID SetVertexUVMap ( DWORD _dwIndex, FLOAT _u, FLOAT _v ) ;
	VERTEX* GetVertex ( DWORD _dwIndex ) ;

	VOID AddFace ( DWORD _dwIndex, DWORD _a, DWORD _b, DWORD _c ) ;
	VOID DelFace ( DWORD _dwIndex ) ;
	VOID SetFace ( DWORD _dwIndex, DWORD _a, DWORD _b, DWORD _c ) ;
	FACE* GetFace ( DWORD _dwIndex ) ;

	VOID AddLine ( DWORD _dwIndex, DWORD _a, DWORD _b ) ;
	VOID DelLine ( DWORD _dwIndex ) ;
	VOID SetLine ( DWORD _dwIndex, DWORD _a, DWORD _b ) ;
	LINE* GetLine ( DWORD _dwIndex ) ;

	D3DXVECTOR3 Min ( ) ;
	D3DXVECTOR3 Max ( ) ;

	/* geometry_core.cpp */

	VOID UpdateGeometry ( ) ;

	VOID Render ( ) ;
	VOID Render ( DWORD dwFaceStart, DWORD dwFaceCount ) ;
	
	VOID DrawVertices ( ) ;
	VOID DrawFaces ( ) ;

	virtual VOID ProcessCommand ( LPSTR sCommand ) ;
	virtual VOID ProcessHelp ( ) ;

	/* Les ressources partagées par la classe GEOMETRY12 sont :                                               */
	/* - les tableaux de vertices, faces et lignes                                                            */
	/* - les vertex et index buffers                                                                          */
	BOOLEAN QuickLoad ( LPSTR _sFile ) ;
	BOOLEAN QuickSave ( LPSTR _sFile ) ;

	BOOLEAN Load ( LPSTR _sFile ) ;
	BOOLEAN Save ( LPSTR _sFile ) ;

};