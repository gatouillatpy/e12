
#pragma once

#include "texture.h"

#include "util.h"



typedef void ( CALLBACK *LPANIMATIONCALLBACK ) ( LPVOID _lpData ) ;



class DLL ANIMATION12 : public TEXTURE12
{

private:

	LPANIMATIONCALLBACK lpUpdateCallback ;
	LPVOID lpUpdateData ;

	DWORD dwTexture ;
	TEXTURE12** ppTexture ;

	struct FRAME12
	{
		TEXTURE12* pt;
		DWORD dt;
		FLOAT tu, tv;
		FLOAT su, sv;
		FRAME12* pn;
	};

	DWORD dwFrameCount ;
	FRAME12* lpFrameStart ;
	FRAME12* lpFrameStop ;

	DWORD dwTime ;
	FLOAT fSpeed ;

	FRAME12* GetFrame ( DWORD _dwTime ) ;

public:

	ANIMATION12 ( RENDER12* _pRender ) ;
	virtual ~ANIMATION12 ( ) ;

	ANIMATION12* Copy ( BOOLEAN bCopyPixelData = FALSE ) ;

	// est-ce que ça sert vraiment finallement puisqu'on spécifie la texture dans AddFrame directement...
	VOID AddTexture ( TEXTURE12* _pTexture ) ;
	VOID DelTexture ( TEXTURE12* _pTexture ) ;
	VOID DelTexture ( DWORD _dwIndex ) ;
	TEXTURE12* GetTexture ( DWORD _dwIndex ) ;

	VOID AddFrame ( DWORD _dwTime = -1, TEXTURE12* pt = NULL, DWORD dt = 40, FLOAT tu = 0.0f, FLOAT tv = 0.0f, FLOAT su = 1.0f, FLOAT sv = 1.0f ) ;
	VOID DelFrame ( DWORD _dwTime ) ;
	TEXTURE12* GetFrameTexture ( DWORD _dwTime ) ;
	VOID SetFrameTexture ( DWORD _dwTime, TEXTURE12* pt ) ;
	DWORD GetFrameTime ( DWORD _dwTime ) ;
	VOID SetFrameTime ( DWORD _dwTime, DWORD dt ) ;

	_inline DWORD FrameCount ( ) ;
	_inline DWORD TimeCount ( ) ;

	VOID SetSpeed ( FLOAT _fSpeed ) ;
	_inline FLOAT GetSpeed ( ) ;

	VOID SetUpdateCallback ( LPANIMATIONCALLBACK _lpCallback ) ;
	VOID SetUpdateData ( LPVOID _lpData ) ;

	VOID Update ( ) ;

	BOOLEAN Load ( LPSTR _sFile ) ;

};