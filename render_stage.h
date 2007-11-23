
#pragma once



#include "util.h"



enum STAGECOORD : DWORD
{
	SC_CUSTOM		= 0x00000000, // les coordonnées doivent être fournies par la géométrie
	SC_NORMAL		= 0x00010000, // les coordonnées sont générées à partir du vecteur normal projetté dans l'espace de la caméra
	SC_POSITION		= 0x00020000, // les coordonnées sont générées à partir du vecteur position projetté dans l'espace de la caméra
	SC_REFLECTION	= 0x00030000, // les coordonnées sont générées à partir du vecteur reflexion calculé à partir de la position et de la norme puis projetté dans l'espace de la caméra
};

struct STAGESTATE12
{
	STAGECOORD	Input;
};
