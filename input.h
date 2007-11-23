
#pragma once



#include "entity.h"

#include "window.h"

#include "keyboard.h"
#include "mouse.h"

#include "util.h"



/************************************************************************/
/* INPUT12 : Classe motrice des entrées clavier/souris via DirectInput. */
/************************************************************************/

class DLL INPUT12 : public ENTITY12
{

	friend class ENGINE12 ;

	friend class MOUSE12 ;
	friend class KEYBOARD12 ;

private:

	DWORD dwKeyboardBufferSize ;
	DWORD dwMouseBufferSize ;

	WINDOW12* lpWindow ;

	INDEXER12* iKeyboardProfile ;
	KEYBOARD12* pKeyboardProfile ;

	INDEXER12* iMouseProfile ;
	MOUSE12* pMouseProfile ;

	BOOLEAN bKey[256] ;
	BOOLEAN bButton[8] ;

	LPDIRECTINPUT8 lpDI ;
	LPDIRECTINPUTDEVICE8 lpDIKeyboard ;
	LPDIRECTINPUTDEVICE8 lpDIMouse ;
	
public:

	INPUT12 ( ENGINE12* _pEngine ) ;
	~INPUT12 ( ) ;

	/* Initialise cette instance en tant que moteur d'entrées pour la fenêtre passée en paramètre. */
	/* -> Ne peut être appelée qu'une seule fois.                                                  */
	/* -> Doit l'être avant tout appel de la méthode Update.                                       */
	BOOLEAN Initialize ( WINDOW12* _pWindow ) ;

	/* Achève l'exécution du moteur d'entrées.                     */
	/* -> Doit être appelée avant l'arrêt complet de l'exécutable. */
	VOID Terminate ( ) ;

	/* Met à jour les paramètres dans ou à partir d'un fichier *.ini */
	/* -> N'a aucun effet après l'initialisation.                    */
	VOID WriteSettings ( LPSTR _sSection, LPSTR _sFile ) ;
	VOID ReadSettings ( LPSTR _sSection, LPSTR _sFile ) ;

	/* Met à jour les entrées clavier/souris en faisant appel à la mémoire tampon de DirectInput. */
	/* -> Doit être appelée avant chaque nouveau rendu. */
	VOID Update ( ) ;

	/* Renvoie les coordonnées relatives au déplacement de la souris (X,Y) et de la molette (Z) mises à jour par la méthode Update. */
	FLOAT X, Y, Z ;

	/* Indique si une touche du clavier est enfoncée ou non. */
	/* -> les valeurs pouvant être prises par _nKey sont référencées par les constantes de l'énumération Keyboard_Device. */
	BOOLEAN Key ( BYTE _nKey ) ;

	/* Indique si un bouton de la souris est enfoncé ou non. */
	/* -> les valeurs pouvant être prises par _nButton sont référencées par les constantes de l'énumération Mouse_Device. */
	BOOLEAN Button ( BYTE _nButton ) ;

	KEYBOARD12* AddKeyboardProfile ( ) ;
	VOID DelKeyboardProfile ( KEYBOARD12* _pKeyboardProfile ) ;
	KEYBOARD12* GetKeyboardProfile ( DWORD _dwIndex ) ;
	KEYBOARD12* GetKeyboardProfile ( LPSTR _sName ) ;

	/* Active un profil clavier */
	VOID SetKeyboardProfile ( KEYBOARD12* _pKeyboardProfile ) ;
	
	/* Renvoie un pointeur vers le profil clavier actif. */
	KEYBOARD12* KeyboardProfile ( ) ;

	MOUSE12* AddMouseProfile ( ) ;
	VOID DelMouseProfile ( MOUSE12* _pMouseProfile ) ;
	MOUSE12* GetMouseProfile ( DWORD _dwIndex ) ;
	MOUSE12* GetMouseProfile ( LPSTR _sName ) ;

	/* Active un profil souris */
	VOID SetMouseProfile ( MOUSE12* _pMouseProfile ) ;

	/* Renvoie un pointeur vers le profil souris actif. */
	MOUSE12* MouseProfile ( ) ;

	VOID ProcessCommand ( LPSTR sCommand ) ;
	VOID ProcessHelp ( ) ;

};