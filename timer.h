
#pragma once

#include "entity.h"
#include "register.h"

#include "util.h"



class DLL TIMER12 : public ENTITY12
{

	typedef VOID ( CALLBACK *LPTIMERCALLBACK ) ( LPVOID _lpData ) ;

	friend DWORD WINAPI TimerThread( LPVOID lpParam ) ;

	friend class ENGINE12 ;

private:

	REGISTER12* mTimer ;

	DWORD nInterval ;
	
	DWORD nLoop ;
	DWORD nCount ;

	HANDLE* pThread ;

	BOOLEAN bEnabled ;

	/* Appelle la callback. */
	VOID OnTimer ( ) ;

public:

	TIMER12 ( ENGINE12* _pEngine ) ;
	virtual ~TIMER12 ( ) ;

	/* Renvoie le temps s'écoulant entre deux appels de la callback en millisecondes. */
	DWORD GetInterval ( ) ;
	
	/* Définit le nombre de millisecondes s'écoulant entre deux appels de la callback. */
	VOID SetInterval ( DWORD _nTime ) ;

	/* Renvoie le nombre maximum d'appels à la callback devant être exécutés. */
	DWORD GetCount ( ) ;

	/* Définit le nombre maximum d'appels à la callback devant être exécutés. */
	/* -> Passer -1 pour définir un nombre maximum infini.                    */
	VOID SetCount ( DWORD _nCount ) ;

	/* Réinitialise le compteur d'appels à la callback.                       */
	/* -> Doit être appelée lorsque le nombre maximum d'appels a été atteint. */
	VOID Reset ( ) ;

	/* Crée un nouveau thread permettant l'exécution séparée du timer. */
	/* -> Ne remet pas le compteur d'appels à la callback à zéro!      */
	VOID Start ( ) ;

	/* Termine l'exécution du thread séparé sans réinitialiser le compteur */
	/* d'appels à la callback.                                             */
	VOID Stop ( ) ;

	/* Ajoute une callback devant être appelée à intervalles de temps réguliers. */
	VOID RegisterTimerCallback ( LPTIMERCALLBACK _pCallback, LPVOID _pData = NULL ) ;

	/* Supprime une callback. */
	VOID UnregisterTimerCallback ( LPTIMERCALLBACK _pCallback ) ;

	VOID ProcessCommand ( LPSTR sCommand ) ;
	VOID ProcessHelp ( ) ;

};
