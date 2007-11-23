
#pragma once

#include "texture.h"
#include "font.h"

#include "util.h"



class DLL BUFFER12 : public TEXTURE12
{

	friend class RENDER12;

private:

	BYTE* pData ;

	LPDIRECT3DSURFACE9 lpD3DBackup ;

	LPDIRECT3DSURFACE9 lpD3DBuffer ;
	LPDIRECT3DSURFACE9 lpD3DSurface ;

public:

	BUFFER12 ( RENDER12* _pRender ) ;
	virtual ~BUFFER12 ( ) ;

	BUFFER12* Copy ( BOOLEAN bCopyPixelData = FALSE ) ;

	BOOLEAN Generate ( UINT _nWidth, UINT _nHeight ) ;

	VOID BeginDraw ( ) ;
	VOID EndDraw ( ) ;

	VOID Fill ( DWORD _dwColor ) ;
	VOID Fill ( FLOAT _r, FLOAT _g, FLOAT _b, FLOAT _a ) ;
	VOID Fill ( SHORT _nLeft, SHORT _nTop, SHORT _nWidth, SHORT _nHeight, DWORD _dwColor ) ;
	VOID Fill ( SHORT _nLeft, SHORT _nTop, SHORT _nWidth, SHORT _nHeight, FLOAT _r, FLOAT _g, FLOAT _b, FLOAT _a ) ;
	VOID Fill ( FLOAT _fLeft, FLOAT _fTop, FLOAT _fWidth, FLOAT _fHeight, DWORD _dwColor ) ;
	VOID Fill ( FLOAT _fLeft, FLOAT _fTop, FLOAT _fWidth, FLOAT _fHeight, FLOAT _r, FLOAT _g, FLOAT _b, FLOAT _a ) ;

	BYTE* Lock ( ) ;
	BYTE* Lock ( SHORT _nLeft, SHORT _nTop, SHORT _nWidth, SHORT _nHeight ) ;
	BYTE* Lock ( FLOAT _fLeft, FLOAT _fTop, FLOAT _fWidth, FLOAT _fHeight ) ;
	VOID Unlock ( ) ;

};