
#pragma once

#include "util.h"

#include "log.h"
#include "impulse.h"



class DLL ENTITY12
{

	friend class DLL ENGINE12 ;
	friend class DLL INDEXER12 ;
	friend class DLL LOG12 ;
	friend class DLL RESOURCE12 ;

	friend class DLL CONSOLE12 ;

protected:

	RESOURCE12* pResource ;

	DWORD dwRefCount ;

	INDEXER12* iLocal ;

	ENGINE12* pEngine ;

	LOG12* pLog ;

	DWORD dwTick ;

	DWORD dwIndex ;

	LPSTR sName ;
	
public:

	ENTITY12 ( INDEXER12* _iLocal, ENGINE12* _pEngine ) ;
	virtual ~ENTITY12 ( ) ;

	/* Renvoie l'indice de cette entit� ou -1 si celui-ci n'a pas �t� d�fini. */
	DWORD GetIndex ( ) ;
	
	/* (Re)d�finit un indice pour cette entit� par rapport � l'indexeur local.  */
	/* -> Si l'indice sp�cifi� existe d�j� dans l'indexeur local alors celui-ci */
	/*    reste inchang� et une erreur est g�n�r�e dans le journal.             */
	VOID SetIndex ( DWORD _dwIndex ) ;

	/* Renvoie le nom de cette entit� ou NULL si celui-ci n'a pas �t� d�fini. */
	LPSTR GetName ( ) ;

	/* (Re)d�finit un nom pour cette entit� par rapport � l'indexeur local.   */
	/* -> Si le nom sp�cifi� existe d�j� dans l'indexeur local alors celui-ci */
	/*    reste inchang� et une erreur est g�n�r�e dans le journal.           */
	VOID SetName ( LPSTR _sName ) ;

	VOID AddRef ( ) ;

	VOID Release ( ) ;

};