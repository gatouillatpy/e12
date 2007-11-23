
#pragma once

#include "util.h"



/****************************************************************************/
/* Constantes de codes :                                                    */
/* ° Niveau : (hex 0)                                                       */
/* ° Classe : (hex 1,2,3)                                                   */
/* ° Numero : (hex 4,5,6,7)													*/
/****************************************************************************/



const CODE CODE_INFO	= 0x10000000;
const CODE CODE_WARNING = 0x20000000;
const CODE CODE_ERROR	= 0x30000000;
const CODE CODE_CRASH	= 0x40000000;

const CODE CODE_INDEXER12		= 0x10000000;
const CODE CODE_DOCUMENT12		= 0x20000000;
const CODE CODE_INPUT12			= 0x01010000;
const CODE CODE_RENDER12		= 0x02010000;
const CODE CODE_OBJECT12		= 0x02020000;
const CODE CODE_COMPLEX12		= 0x02030000;
const CODE CODE_FONT12			= 0x02040000;
const CODE CODE_SHADER12		= 0x02050000;
const CODE CODE_ANIMATION12		= 0x02060000;
const CODE CODE_VOLUME12		= 0x02070000;
const CODE CODE_TEXTURE12		= 0x02080000;
const CODE CODE_MESH12			= 0x02090000;
const CODE CODE_GEOMETRY12		= 0x020A0000;



class DLL IMPULSE12
{

	friend class LOG12;

private:

	IMPULSE12* pParent ;

	LPSTR sFile ;
	DWORD nLine ;

	CODE nCode ;

	LPVOID pClass ;

	LPVOID pData ;

	LPSTR pComment ;

	/* Ecrit dans le journal le message d'erreur correspondant à cette instance. */
	VOID Report ( LOG12* _pLog ) ;

public:

	IMPULSE12 ( IMPULSE12* _pParent, LPSTR _sFile, DWORD _nLine, CODE _nType, CODE _nClass, CODE _nNumber, LPVOID _pClass = NULL, LPVOID _pData = NULL, LPSTR _pComment = NULL ) ;
	~IMPULSE12 ( ) ;

};
