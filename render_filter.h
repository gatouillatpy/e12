
#pragma once



#include "util.h"



enum FILTERTYPE : DWORD
{
	FT_NONE				=  0,
	FT_POINT			=  1,
	FT_LINEAR			=  2,
	FT_ANISOTROPIC		=  3,
	FT_PYRAMIDALQUAD	=  6,
	FT_GAUSSIANQUAD		=  7,
};

struct FILTERSTATE12
{
	FILTERTYPE	Magnification;
	FILTERTYPE	Minification;
	FILTERTYPE	MipmapFilter;
	INT			MipmapLevel;
	INT			LevelOfDetail;
};
