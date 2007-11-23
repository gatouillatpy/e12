
#pragma once

#include "engine.h"
#include "control.h"

#include "util.h"



class DLL CONTROL12_EFFECT
{

	friend class CONTROL12 ;

protected:

	ENGINE12* pEngine ;

	CONTROL12* pControl ;

	DOUBLE fDuration ;

	DOUBLE fStartTime ;
	DOUBLE fStopTime ;

	CONTROL12_EFFECT* pNext ;

public:

	CONTROL12_EFFECT ( CONTROL12* pControl, DOUBLE _fDuration ) ;

	VOID ApplyNext ( CONTROL12_EFFECT* _pEffect ) ;

	virtual VOID Create ( ) ;

	virtual VOID Update ( ) ;

	virtual VOID Destroy ( ) ;

};
