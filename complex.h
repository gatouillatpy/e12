
#pragma once

#include "object.h"

#include "util.h"



CONST DWORD OPERATION_UNION = 0x00000000 ;
CONST DWORD OPERATION_SUBTRACTION = 0x00000001 ;
CONST DWORD OPERATION_INTERSECTION = 0x00000002 ;



/***************************************************************************************************************/
/* Rappels sur les arbres CSG normalisés : (U : union ; - : soustraction ; I : intersection)                   */
/*  (1) a – (x U y) -> (a – x) – y                                                                             */
/*  (2) a I (x U y) -> (a I x) U (a I y)                                                                       */
/*  (3) a – (x - y) -> (a – x) U (a I y)                                                                       */
/*  (4) a I (x - y) -> (a I x) – y                                                                             */
/*  (5) a – (x I y) -> (a - x) U (a - y)                                                                       */
/*  (6) a I (x I y) -> (a I x) I y                                                                             */
/*  (7) (a U b) - t -> (a - t) U (b - t)                                                                       */
/*  (8) (a U b) I t -> (a I t) U (b I t)                                                                       */
/*  (9) (a – b) I t -> (a I t) – b                                                                             */
/* (10) (a U b) - (x U y) -> ((a - x) - y) U ((b - x) - y)                                                     */
/* (11) (a U b) - (x - y) -> ((a - x) U (a I y)) U ((b - x) U (b I y))                                         */
/* (12) (a U b) - (x I y) -> ((a - x) U (a - y)) U ((b - x) U (b - y))                                         */
/* (13) (a U b) I (x U y) -> ((a I x) U (a I y)) U ((b I x) U (b I y))                                         */
/* (14) (a U b) I (x - y) -> ((a I x) - y) U ((b I x) - y)                                                     */
/* (15) (a U b) I (x I y) -> ((a I x) I y) U ((b I x) I y)                                                     */
/* (16) (a - b) - (x U y) -> ((a - b) - x) - y                                                                 */
/* (17) (a - b) - (x - y) -> ((a - b) - x) U ((a I y) - b)                                                     */
/* (18) (a - b) - (x I y) -> ((a - b) - x) U ((a - b) - y)                                                     */
/* (19) (a - b) I (x U y) -> ((a I x) - b) U ((a I y) - b)                                                     */
/* (20) (a - b) I (x - y) -> ((a I x) - y) - b                                                                 */
/* (21) (a - b) I (x I y) -> ((a I x) I y) - b                                                                 */
/* (22) (a I b) - (x U y) -> ((a I b) - x) - y                                                                 */
/* (23) (a I b) - (x - y) -> ((a I b) - x) U ((a I b) I y)                                                     */
/* (24) (a I b) - (x I y) -> ((a I b) - x) U ((a I b) - y)                                                     */
/* (25) (a I b) I (x U y) -> ((a I b) I x) U ((a I b) I y)                                                     */
/* (26) (a I b) I (x - y) -> ((a I b) I x) - y                                                                 */
/* (27) (a I b) I (x I y) -> ((a I b) I x) I y                                                                 */
/***************************************************************************************************************/



class DLL COMPLEX12 : public OBJECT12
{

private:

	OBJECT12* pA ;
	OBJECT12* pB ;
	
	DWORD dwOperation ;

public:

	COMPLEX12 ( RENDER12* _pRender ) ;

	virtual COMPLEX12* Copy( BOOLEAN bCopyGeometry = FALSE, BOOLEAN bCopyTexture = FALSE ) ;

	VOID SetScene ( SCENE12* _pScene ) ;

	VOID SetA ( OBJECT12* _pObject ) ;
	VOID SetB ( OBJECT12* _pObject ) ;

	VOID Union ( OBJECT12* _pObject ) ;
	VOID Subtraction ( OBJECT12* _pObject ) ;
	VOID Intersection ( OBJECT12* _pObject ) ;

	VOID Union ( COMPLEX12* _pComplex ) ;
	VOID Subtraction ( COMPLEX12* _pComplex ) ;
	VOID Intersection ( COMPLEX12* _pComplex ) ;

	_inline VOID SetOperation ( DWORD _dwOperation ) ;
	_inline DWORD GetOperation ( ) ;

	VOID Render ( CAMERA12* _pCamera ) ;

};