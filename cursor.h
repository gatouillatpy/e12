
#pragma once

#include "control.h"
#include "texture.h"

#include "util.h"



class DLL CURSOR12 : public CONTROL12
{

private:

	TEXTURE12* pTexture ;

	LPDIRECT3DPIXELSHADER9 lpPixelShader ;
	LPDIRECT3DVERTEXSHADER9 lpVertexShader ;
	LPDIRECT3DVERTEXDECLARATION9 lpVertexDeclaration ;
	LPDIRECT3DVERTEXBUFFER9 lpVertexBuffer ;
	LPDIRECT3DINDEXBUFFER9 lpIndexBuffer ;

public:

	CURSOR12 ( RENDER12* _pRender ) ;
	virtual ~CURSOR12 ( ) ;

	VOID SetTexture ( TEXTURE12* _pTexture ) { pTexture = _pTexture; } ;
	TEXTURE12* GetTexture ( ) { return pTexture; } ;

	VOID Update ( ) ;
	VOID Render ( ) ;

};