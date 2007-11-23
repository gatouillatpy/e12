
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

	/* Renvoie le temps s'�coulant entre deux appels de la callback en millisecondes. */
	DWORD GetInterval ( ) ;
	
	/* D�finit le nombre de millisecondes s'�coulant entre deux appels de la callback. */
	VOID SetInterval ( DWORD _nTime ) ;

	/* Renvoie le nombre maximum d'appels � la callback devant �tre ex�cut�s. */
	DWORD GetCount ( ) ;

	/* D�finit le nombre maximum d'appels � la callback devant �tre ex�cut�s. */
	/* -> Passer -1 pour d�finir un nombre maximum infini.                    */
	VOID SetCount ( DWORD _nCount ) ;

	/* R�initialise le compteur d'appels � la callback.                       */
	/* -> Doit �tre appel�e lorsque le nombre maximum d'appels a �t� atteint. */
	VOID Reset ( ) ;

	/* Cr�e un nouveau thread permettant l'ex�cution s�par�e du timer. */
	/* -> Ne remet pas le compteur d'appels � la callback � z�ro!      */
	VOID Start ( ) ;

	/* Termine l'ex�cution du thread s�par� sans r�initialiser le compteur */
	/* d'appels � la callback.                                             */
	VOID Stop ( ) ;

	/* Ajoute une callback devant �tre appel�e � intervalles de temps r�guliers. */
	VOID RegisterTimerCallback ( LPTIMERCALLBACK _pCallback, LPVOID _pData = NULL ) ;

	/* Supprime une callback. */
	VOID UnregisterTimerCallback ( LPTIMERCALLBACK _pCallback ) ;

	VOID ProcessCommand ( LPSTR sCommand ) ;
	VOID ProcessHelp ( ) ;

};
