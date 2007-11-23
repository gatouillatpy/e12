
#pragma once

#include "frame_fadeout.h"

#include "util.h"



struct BLENDSTATE12 ;



class DLL LABEL12_FADEOUT : public FRAME12_FADEOUT
{

	friend class LABEL12 ;

protected:

	BLENDSTATE12* pFontBlendState ;

public:

	LABEL12_FADEOUT ( CONTROL12* pControl, DOUBLE _fDuration ) ;

	virtual VOID Create ( ) ;

	virtual VOID Destroy ( ) ;

};
