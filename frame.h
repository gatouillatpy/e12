
#pragma once

#include "font.h"
#include "control.h"

#include "util.h"



struct BLENDSTATE12 ;



class DLL FRAME12 : public CONTROL12
{

public:

	enum STYLE : DWORD
	{
		STYLE_WIN9X	= 1,
	};

	enum BORDERSTYLE : DWORD
	{
		BS_WIN9X_FRONT	= 1,
		BS_WIN9X_BACK	= 2,
	};

protected:

	D3DXVECTOR4 vBackColor ;
	D3DXVECTOR4 vBorderColor ;

	BOOLEAN bBorder ;

	STYLE tStyle ;

	BORDERSTYLE tBorderStyle ;

	BLENDSTATE12* pBackBlendState ;
	BLENDSTATE12* pBorderBlendState ;

	VOID RenderBack ( ) ;
	VOID RenderBorder ( ) ;
	VOID RenderBorderWin9XFront ( ) ;
	VOID RenderBorderWin9XBack ( ) ;

public:

	FRAME12 ( RENDER12* _pRender ) ;

	D3DXVECTOR4 GetBackColor ( ) ;
	VOID SetBackColor ( D3DXVECTOR4 & _vColor ) ;
	VOID SetBackColor ( DWORD _dwColor ) ;
	VOID SetBackColor ( FLOAT _r, FLOAT _g, FLOAT _b, FLOAT _a ) ;

	D3DXVECTOR4 GetBorderColor ( ) ;
	VOID SetBorderColor ( D3DXVECTOR4 & _vColor ) ;
	VOID SetBorderColor ( DWORD _dwColor ) ;
	VOID SetBorderColor ( FLOAT _r, FLOAT _g, FLOAT _b, FLOAT _a ) ;

	VOID SetBackBlendState ( BLENDSTATE12* _pBackBlendState ) ;
	BLENDSTATE12* GetBackBlendState ( ) ;

	VOID SetBorderBlendState ( BLENDSTATE12* _pBorderBlendState ) ;
	BLENDSTATE12* GetBorderBlendState ( ) ;

	VOID ShowBorder ( ) ;
	VOID HideBorder ( ) ;

	virtual VOID SetStyle ( STYLE _tStyle ) ;
	virtual STYLE GetStyle ( ) ;

	VOID SetBorderStyle ( BORDERSTYLE _tBorderStyle ) ;
	BORDERSTYLE GetBorderStyle ( ) ;

	virtual VOID Render ( ) ;

};