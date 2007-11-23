
#pragma once

#include "control_effect.h"

#include "util.h"



struct BLENDSTATE12 ;



class DLL FRAME12_FADEIN : public CONTROL12_EFFECT
{

	friend class FRAME12 ;

protected:

	BLENDSTATE12* pFadeBlendState ;

	BLENDSTATE12* pBackBlendState ;
	BLENDSTATE12* pBorderBlendState ;

public:

	FRAME12_FADEIN ( CONTROL12* pControl, DOUBLE _fDuration ) ;

	virtual VOID Create ( ) ;

	virtual VOID Update ( ) ;

	virtual VOID Destroy ( ) ;

};
