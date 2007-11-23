
#pragma once



#include "util.h"



enum STAGECOORD : DWORD
{
	SC_CUSTOM		= 0x00000000, // les coordonn�es doivent �tre fournies par la g�om�trie
	SC_NORMAL		= 0x00010000, // les coordonn�es sont g�n�r�es � partir du vecteur normal projett� dans l'espace de la cam�ra
	SC_POSITION		= 0x00020000, // les coordonn�es sont g�n�r�es � partir du vecteur position projett� dans l'espace de la cam�ra
	SC_REFLECTION	= 0x00030000, // les coordonn�es sont g�n�r�es � partir du vecteur reflexion calcul� � partir de la position et de la norme puis projett� dans l'espace de la cam�ra
};

struct STAGESTATE12
{
	STAGECOORD	Input;
};
