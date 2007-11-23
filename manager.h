
#pragma once

#include "entity.h"
#include "resource.h"

#include "util.h"



class DLL MANAGER12
{

	friend class RESOURCE12;

private:

	LOG12* pLog ;

	struct NODE12
	{
		RESOURCE12* pResource;

		ENTITY12* pEntity;

		SHORT nHeight;
		SHORT nFactor;

		NODE12* pA;
		NODE12* pB;
	};

	NODE12* pResourceRoot ;
	NODE12* pEntityRoot ;
	NODE12* pFileRoot ;

	/* Supprime un noeud de l'arbre et tous ses descendents. */
	VOID Collapse ( NODE12* pNode ) ;

	/* Evalue la hauteur et la balance d'un noeud. */
	VOID Evaluate ( NODE12* _pNode ) ;

	/* Effectue une rotation vers la gauche de l'arbre ayant pour racine */
	/* le noeud passé en paramètre.                                      */
	VOID RotateLeft ( NODE12* & _pNode ) ;

	/* Effectue une rotation vers la droite de l'arbre ayant pour racine */
	/* le noeud passé en paramètre.                                      */
	VOID RotateRight ( NODE12* & _pNode ) ;

	/* Effectue les rotations nécessaires au rééquilibrage de l'arbre ayant */
	/* pour racine le noeud passé en paramètre.                             */
	VOID Normalize ( NODE12* & _pNode ) ;

	/* Extrait et renvoie le plus petit noeud du sous-arbre droit du noeud */
	/* passé en paramètre.                                                 */
	NODE12* Extract ( NODE12* & _pNode ) ;

	VOID AddResource ( NODE12* & _pNode, RESOURCE12* _pResource ) ;
	VOID AddEntity ( NODE12* & _pNode, RESOURCE12* _pResource, ENTITY12* _pEntity ) ;
	VOID AddFile ( NODE12* & _pNode, RESOURCE12* _pResource ) ;

	RESOURCE12* GetEntity ( NODE12* & _pNode, ENTITY12* _pEntity ) ;
	RESOURCE12* GetFile ( NODE12* & _pNode, LPSTR _sFile ) ;

	BOOLEAN DelResource ( NODE12* & _pNode, RESOURCE12* _pResource ) ;
	BOOLEAN DelEntity ( NODE12* & _pNode, RESOURCE12* _pResource ) ;
	BOOLEAN DelFile ( NODE12* & _pNode, RESOURCE12* _pResource ) ;

	VOID Free ( NODE12* _pNode ) ;

public:

	MANAGER12 ( LOG12* _pLog ) ;
	~MANAGER12 ( ) ;

	RESOURCE12* Set ( ENTITY12* _pEntity, LPSTR _sFile ) ;

	RESOURCE12* Get ( ENTITY12* _pEntity ) ;
	RESOURCE12* Get ( LPSTR _sFile ) ;

	VOID Del ( RESOURCE12* _pResource ) ;

};