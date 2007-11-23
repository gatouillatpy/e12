
#pragma once



#include "entity.h"

#include "window.h"

#include "keyboard.h"
#include "mouse.h"

#include "util.h"



/************************************************************************/
/* INPUT12 : Classe motrice des entr�es clavier/souris via DirectInput. */
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

	/* Initialise cette instance en tant que moteur d'entr�es pour la fen�tre pass�e en param�tre. */
	/* -> Ne peut �tre appel�e qu'une seule fois.                                                  */
	/* -> Doit l'�tre avant tout appel de la m�thode Update.                                       */
	BOOLEAN Initialize ( WINDOW12* _pWindow ) ;

	/* Ach�ve l'ex�cution du moteur d'entr�es.                     */
	/* -> Doit �tre appel�e avant l'arr�t complet de l'ex�cutable. */
	VOID Terminate ( ) ;

	/* Met � jour les param�tres dans ou � partir d'un fichier *.ini */
	/* -> N'a aucun effet apr�s l'initialisation.                    */
	VOID WriteSettings ( LPSTR _sSection, LPSTR _sFile ) ;
	VOID ReadSettings ( LPSTR _sSection, LPSTR _sFile ) ;

	/* Met � jour les entr�es clavier/souris en faisant appel � la m�moire tampon de DirectInput. */
	/* -> Doit �tre appel�e avant chaque nouveau rendu. */
	VOID Update ( ) ;

	/* Renvoie les coordonn�es relatives au d�placement de la souris (X,Y) et de la molette (Z) mises � jour par la m�thode Update. */
	FLOAT X, Y, Z ;

	/* Indique si une touche du clavier est enfonc�e ou non. */
	/* -> les valeurs pouvant �tre prises par _nKey sont r�f�renc�es par les constantes de l'�num�ration Keyboard_Device. */
	BOOLEAN Key ( BYTE _nKey ) ;

	/* Indique si un bouton de la souris est enfonc� ou non. */
	/* -> les valeurs pouvant �tre prises par _nButton sont r�f�renc�es par les constantes de l'�num�ration Mouse_Device. */
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