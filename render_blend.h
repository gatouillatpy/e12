
#pragma once



#include "util.h"



enum BLENDFACTOR : DWORD
{
	BF_ZERO			=  1, // (0.0f, 0.0f, 0.0f, 0.0f)
	BF_ONE			=  2, // (1.0f, 1.0f, 1.0f, 1.0f)
	BF_WTNCOLOR		=  3, // (w.r, w.g, w.b, w.a)
	BF_INVWTNCOLOR	=  4, // (1.0f - w.r, 1.0f - w.g, 1.0f - w.b, 1.0f - w.a)
	BF_WTNALPHA		=  5, // (w.a, w.a, w.a, w.a)
	BF_INVWTNALPHA	=  6, // (1.0f - w.a, 1.0f - w.a, 1.0f - w.a, 1.0f - w.a)
	BF_CURALPHA		=  7, // (c.a, c.a, c.a, c.a)
	BF_INVCURALPHA	=  8, // (1.0f - c.a, 1.0f - c.a, 1.0f - c.a, 1.0f - c.a)
	BF_CURCOLOR		=  9, // (c.r, c.g, c.b, c.a)
	BF_INVCURCOLOR	= 10, // (1.0f - c.r, 1.0f - c.g, 1.0f - c.b, 1.0f - c.a)
	BF_ALPHASAT		= 11, // (f, f, f, 1.0f) avec f = min(w.a, 1.0f - c.a)
	BF_CONSTANT		= 14, // (k.r, k.g, k.b, k.a)
	BF_INVCONSTANT	= 15, // (1.0f - k.r, 1.0f - k.g, 1.0f - k.b, 1.0f - k.a)
};

enum BLENDOP : DWORD
{
	BO_ADD			= 1, // FinalPixel = WaitingPixel * WaitingFactor + CurrentPixel * CurrentFactor
	BO_SUBTRACT		= 2, // FinalPixel = WaitingPixel * WaitingFactor - CurrentPixel * CurrentFactor
	BO_REVSUBTRACT	= 3, // FinalPixel = CurrentPixel * CurrentFactor - WaitingPixel * WaitingFactor
	BO_MIN			= 4, // FinalPixel = MIN(WaitingPixel * WaitingFactor, CurrentPixel * CurrentFactor)
	BO_MAX			= 5, // FinalPixel = MAX(WaitingPixel * WaitingFactor, CurrentPixel * CurrentFactor)
};

struct BLENDSTATE12
{
	BLENDFACTOR	Current;
	BLENDFACTOR	Waiting;
	BLENDOP		Operation;
	DWORD		Constant;
};
