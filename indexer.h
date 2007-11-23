
#pragma once

#include "entity.h"

#include "util.h"



class DLL INDEXER12
{

	friend class ENTITY12;
	friend class OBJECT12;
	friend class SCENE12;
	friend class INTERFACE12;
	friend class ANIMATION12;

private:

	BOOLEAN bLock ;

	LOG12* pLog ;

	DWORD dwCount ;
	DWORD dwTick ;

	ENTITY12** ppEntity ;

	BOOLEAN bVector ;

	struct NODE12
	{
		ENTITY12* pEntity;

		SHORT nHeight;
		SHORT nFactor;

		NODE12* pA;
		NODE12* pB;
	};

	NODE12* pEntityRoot ;
	NODE12* pIndexRoot ;
	NODE12* pNameRoot ;
	NODE12* pTickRoot ;

	/* Supprime un noeud de l'arbre et tous ses descendents. */
	VOID Collapse ( NODE12* pNode ) ;

	/* Evalue la hauteur et la balance d'un noeud. */
	VOID Evaluate ( NODE12* _pNode ) ;

	/* Effectue une rotation vers la gauche de l'arbre ayant pour racine */
	/* le noeud pass� en param�tre.                                      */
	VOID RotateLeft ( NODE12* & _pNode ) ;

	/* Effectue une rotation vers la droite de l'arbre ayant pour racine */
	/* le noeud pass� en param�tre.                                      */
	VOID RotateRight ( NODE12* & _pNode ) ;

	/* Effectue les rotations n�cessaires au r��quilibrage de l'arbre ayant */
	/* pour racine le noeud pass� en param�tre.                             */
	VOID Normalize ( NODE12* & _pNode ) ;

	/* Extrait et renvoie le plus petit noeud du sous-arbre droit du noeud */
	/* pass� en param�tre.                                                 */
	NODE12* Extract ( NODE12* & _pNode ) ;

	VOID AddEntity ( NODE12* & _pNode, ENTITY12* _pEntity ) ;
	VOID AddIndex ( NODE12* & _pNode, ENTITY12* _pEntity ) ;
	VOID AddName ( NODE12* & _pNode, ENTITY12* _pEntity ) ;
	VOID AddTick ( NODE12* & _pNode, ENTITY12* _pEntity ) ;

	ENTITY12* GetIndex ( NODE12* & _pNode, DWORD _dwIndex ) ;
	ENTITY12* GetName ( NODE12* & _pNode, LPSTR _sName ) ;

	BOOLEAN DelEntity ( NODE12* & _pNode, ENTITY12* _pEntity ) ;
	BOOLEAN DelIndex ( NODE12* & _pNode, ENTITY12* _pEntity ) ;
	BOOLEAN DelName ( NODE12* & _pNode, ENTITY12* _pEntity ) ;
	BOOLEAN DelTick ( NODE12* & _pNode, ENTITY12* _pEntity ) ;

	VOID FillVector ( NODE12* _pNode, DWORD & k ) ;

	/* Met � jour le vecteur en le remplissant � partir de la racine de */
	/* l'arbre de recherche chronologique. */
	VOID UpdateVector ( ) ;

	VOID Free ( NODE12* _pNode ) ;
	
	VOID Set ( ENTITY12* _pEntity, DWORD _dwIndex ) ;
	VOID Set ( ENTITY12* _pEntity, LPSTR _sName ) ;

	VOID Add ( ENTITY12* _pEntity ) ;
	VOID Del ( ENTITY12* _pEntity ) ;

public:

	INDEXER12 ( LOG12* _pLog ) ;
	~INDEXER12 ( ) ;

	/* Renvoie le pointeur de l'entit� ayant cet indice.          */
	/* -> Renvoie NULL et g�n�re un avertissement dans le journal */
	/*    si l'indice n'a pas �t� trouv�.                         */
	ENTITY12* Get ( DWORD _dwIndex ) ;

	/* Renvoie le pointeur de l'entit� portant ce nom.            */
	/* -> Renvoie NULL et g�n�re un avertissement dans le journal */
	/*    si le nom n'a pas �t� trouv�.                           */
	ENTITY12* Get ( LPSTR _sName ) ;

	/* R�cup�re l'adresse des pointeurs de la 1� et de la n+1� entit�s ajout�es. */
	VOID Vector ( ENTITY12** & ppStart, ENTITY12** & ppStop ) ;

	/* Renvoie le poiteur de la k� entit� ajout�e. */
	ENTITY12* operator[] ( DWORD k ) ;

	/* Supprime toutes les entit�s de l'arbre puis s'auto-detruit. */
	VOID Free ( ) ;

};