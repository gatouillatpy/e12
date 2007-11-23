
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

	/* Renvoie l'indice de cette entité ou -1 si celui-ci n'a pas été défini. */
	DWORD GetIndex ( ) ;
	
	/* (Re)définit un indice pour cette entité par rapport à l'indexeur local.  */
	/* -> Si l'indice spécifié existe déjà dans l'indexeur local alors celui-ci */
	/*    reste inchangé et une erreur est générée dans le journal.             */
	VOID SetIndex ( DWORD _dwIndex ) ;

	/* Renvoie le nom de cette entité ou NULL si celui-ci n'a pas été défini. */
	LPSTR GetName ( ) ;

	/* (Re)définit un nom pour cette entité par rapport à l'indexeur local.   */
	/* -> Si le nom spécifié existe déjà dans l'indexeur local alors celui-ci */
	/*    reste inchangé et une erreur est générée dans le journal.           */
	VOID SetName ( LPSTR _sName ) ;

	VOID AddRef ( ) ;

	VOID Release ( ) ;

};