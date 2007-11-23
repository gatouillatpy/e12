
#pragma once



#include "util.h"

#include "manager.h"
#include "resource.h"
#include "impulse.h"
#include "entity.h"
#include "indexer.h"
#include "log.h"

#include "window.h"

#include "timer.h"

#include "keyboard.h"
#include "mouse.h"

#include "geometry.h"
#include "texture.h"
#include "shader.h"
#include "font.h"

#include "hitbox.h"
#include "camera.h"
#include "object.h"
#include "cylinder.h"
#include "box.h"
#include "grid.h"
#include "mesh.h"
#include "surface.h"
#include "scene.h"

#include "button.h"
#include "cursor.h"
#include "image.h"
#include "label.h"
#include "alabel.h"
#include "textbox.h"
#include "cmdbox.h"
#include "frame.h"
#include "control.h"
#include "interface.h"

#include "input.h"
#include "render.h"

#include "debug.h"



/***********************************************************************************************/
/* ENGINE12 : Classe principale de E12, permet l'instanciation de toutes les classes motrices. */
/***********************************************************************************************/

class DLL ENGINE12
{

	friend class RESOURCE12 ;
	friend class ENTITY12 ;
	friend class TIMER12 ;
	friend class WINDOW12 ;
	friend class INPUT12 ;
	friend class RENDER12 ;

private:

	DWORD nThreadCount ;
	HANDLE* ppThread ;

	MANAGER12* iResource ;
	INDEXER12* iWindow ;
	INDEXER12* iInput ;
	INDEXER12* iRender ;
	INDEXER12* iTimer ;

	LOG12* pLog ;

	DOUBLE fFrameTime ;
	DOUBLE fMarkTime ;
	DOUBLE fBeginTime ;
	DOUBLE fDelta ;

	LONGLONG nMarkCount ;
	LONGLONG nTotalCount ;

	DOUBLE fCurrentFramerate ;
	DOUBLE fAverageFramerate ;

	HANDLE hEvent ;

public:

	ENGINE12() ;
	~ENGINE12() ;

	/* Appelle la méthode Update() de l'ensemble des classes instanciées */
	/* ainsi que UpdateTime() dans l'ordre le plus approprié.            */
	VOID Update ( ) ;

/*************************/
/* Gestion des threads : */
/*************************/

	HANDLE* RegisterThread ( LPTHREAD_START_ROUTINE _pStartAddress, LPVOID _pParameter ) ;

/****************************/
/* Gestion des ressources : */
/****************************/

	RESOURCE12* AddResource ( ENTITY12* _pEntity, LPSTR _sFile ) ;
	VOID DelResource ( LPSTR _sFile ) ;
	RESOURCE12* GetResource ( LPSTR _sFile ) ;

/**********************************************/
/* Gestion des instances de classe WINDOW12 : */
/**********************************************/

	WINDOW12* AddWindow ( ) ;
	VOID DelWindow ( WINDOW12* _pWindow ) ;
	WINDOW12* GetWindow ( DWORD _dwIndex ) ;
	WINDOW12* GetWindow ( LPSTR _sName ) ;

/*********************************************/
/* Gestion des instances de classe INPUT12 : */
/*********************************************/

	INPUT12* AddInput ( ) ;
	VOID DelInput ( INPUT12* _pInput ) ;
	INPUT12* GetInput ( DWORD _dwIndex ) ;
	INPUT12* GetInput ( LPSTR _sName ) ;

/**********************************************/
/* Gestion des instances de classe RENDER12 : */
/**********************************************/

	RENDER12* AddRender ( ) ;
	VOID DelRender ( RENDER12* _pRender ) ;
	RENDER12* GetRender ( DWORD _dwIndex ) ;
	RENDER12* GetRender ( LPSTR _sName ) ;

/*********************************************/
/* Gestion des instances de classe TIMER12 : */
/*********************************************/

	TIMER12* AddTimer ( ) ;
	VOID DelTimer ( TIMER12* _pTimer ) ;
	TIMER12* GetTimer ( DWORD _dwIndex ) ;
	TIMER12* GetTimer ( LPSTR _sName ) ;

/**********************/
/* Gestion du temps : */
/**********************/

	/* Met le thread en attente et repasse la main au système un certain temps (en millisecondes). */
	VOID Wait ( DWORD dwTime ) ;

	/* Met à jour l'ensemble des variables temporelles. */
	/* -> Doit être appelée une fois à chaque frame.    */
	VOID UpdateTime ( ) ;

	/* Renvoie le nombre de secondes depuis le démarrage du CPU. */
	DOUBLE GetTime ( ) ;

	/* Renvoie le temps écoulé entre deux frames en secondes. */
	DOUBLE GetDelta ( ) ;

	/* Renvoie le nombre de frames calculées lors de la dernière seconde. */
	DOUBLE GetCurrentFramerate ( ) ;

	/* Renvoie le nombre moyen de frames calculées depuis l'instanciation de cette classe. */
	DOUBLE GetAverageFramerate ( ) ;

	/***************************/
	/* Gestion des commandes : */
	/***************************/

	VOID ProcessCommand ( LPSTR sCommand ) ;
	VOID ProcessHelp ( ) ;
};
