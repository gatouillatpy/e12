
#pragma once

#include "frame_fadein.h"

#include "util.h"



struct BLENDSTATE12 ;



class DLL LABEL12_FADEIN : public FRAME12_FADEIN
{

	friend class LABEL12 ;

protected:

	BLENDSTATE12* pFontBlendState ;

public:

	LABEL12_FADEIN ( CONTROL12* pControl, DOUBLE _fDuration ) ;

	virtual VOID Create ( ) ;

	virtual VOID Destroy ( ) ;

};
