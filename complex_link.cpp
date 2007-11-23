
#include "complex.h"
#include "scene.h"
#include "render.h"
#include "indexer.h"
#include "log.h"
#include "impulse.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID COMPLEX12::SetScene ( SCENE12* _pScene )
{
	pScene = _pScene;

	ENTITY12 **ppEntity, **ppEnd;
	iChild->Vector( ppEntity, ppEnd );
	while ( ppEntity < ppEnd )
	{
		OBJECT12* pObject = (OBJECT12*)*ppEntity;
		pObject->SetScene( _pScene );
		ppEntity++;
	}

	pA->SetScene( _pScene );
	pB->SetScene( _pScene );
}



VOID COMPLEX12::SetA ( OBJECT12* _pObject )
{
	pA = _pObject;

	pA->SetParent( this );
}

VOID COMPLEX12::SetB ( OBJECT12* _pObject )
{
	pB = _pObject;

	pB->SetParent( this );
}



VOID COMPLEX12::Union ( OBJECT12* _pObject )
{
	if ( pA == NULL && pB == NULL )
	{
		SetA( _pObject );
		SetOperation( OPERATION_UNION );
	}
	else if ( pA == NULL )
	{
		pLog->Push( __FILE__, __LINE__, CODE_ERROR, CODE_COMPLEX12, 0x0001, this, NULL, NULL ); return;
	}
	else if ( pB == NULL )
	{
		SetB( _pObject );
		SetOperation( OPERATION_UNION );
	}
	else
	{
		COMPLEX12* pTA = new COMPLEX12( pRender );
		pTA->SetA( pA );
		pTA->SetB( pB );
		pTA->SetOperation( dwOperation );

		SetA( pTA );
		SetB( _pObject );
		SetOperation( OPERATION_UNION );
	}

	_pObject->Hide();
}

VOID COMPLEX12::Subtraction ( OBJECT12* _pObject )
{
	if ( pA == NULL && pB == NULL )
	{
		pLog->Push( __FILE__, __LINE__, CODE_ERROR, CODE_COMPLEX12, 0x0002, this, NULL, NULL ); return;
	}
	else if ( pA == NULL )
	{
		pLog->Push( __FILE__, __LINE__, CODE_ERROR, CODE_COMPLEX12, 0x0003, this, NULL, NULL ); return;
	}
	else if ( pB == NULL )
	{
		if ( pA->IsComplex() )
		{
			COMPLEX12* pTA = (COMPLEX12*)pA;

			/* (8) (a U b) - t -> (a - t) U (b - t) */
			if ( pTA->dwOperation == OPERATION_UNION )
			{
				COMPLEX12* pTB = new COMPLEX12( pRender );
				pTB->SetA( pTA->pB );
				pTB->SetB( _pObject );
				pTB->SetOperation( OPERATION_SUBTRACTION );

				pTA->SetB( _pObject );
				pTA->SetOperation( OPERATION_SUBTRACTION );

				SetB( pTB );
				SetOperation( OPERATION_UNION );
			}
			else
			{
				SetB( _pObject );
				SetOperation( OPERATION_SUBTRACTION );
			}
		}
		else
		{
			SetB( _pObject );
			SetOperation( OPERATION_SUBTRACTION );
		}
	}
	else
	{
		/* (8) (a U b) - t -> (a - t) U (b - t) */
		if ( dwOperation == OPERATION_UNION )
		{
			COMPLEX12* pTA = new COMPLEX12( pRender );
			pTA->SetA( pA );
			pTA->SetB( _pObject );
			pTA->SetOperation( OPERATION_SUBTRACTION );

			COMPLEX12* pTB = new COMPLEX12( pRender );
			pTB->SetA( pB);
			pTB->SetB( _pObject );
			pTB->SetOperation( OPERATION_SUBTRACTION );

			SetA( pTA );
			SetB( pTB );
			SetOperation( OPERATION_UNION );
		}
		else
		{
			COMPLEX12* pTA = new COMPLEX12( pRender );
			pTA->SetA( pA );
			pTA->SetB( pB );
			pTA->SetOperation( dwOperation );

			SetA( pTA );
			SetB( _pObject );
			SetOperation( OPERATION_SUBTRACTION );
		}
	}

	_pObject->Hide();
}

VOID COMPLEX12::Intersection ( OBJECT12* _pObject )
{
	if ( pA == NULL && pB == NULL )
	{
		pLog->Push( __FILE__, __LINE__, CODE_ERROR, CODE_COMPLEX12, 0x0004, this, NULL, NULL ); return;
	}
	else if ( pA == NULL )
	{
		pLog->Push( __FILE__, __LINE__, CODE_ERROR, CODE_COMPLEX12, 0x0005, this, NULL, NULL ); return;
	}
	else if ( pB == NULL )
	{
		if ( pA->IsComplex() )
		{
			COMPLEX12* pTA = (COMPLEX12*)pA;

			/* (7) (a U b) I t -> (a I t) U (b I t) */
			if ( pTA->dwOperation == OPERATION_UNION )
			{
				COMPLEX12* pTB = new COMPLEX12( pRender );
				pTB->SetA( pTA->pB );
				pTB->SetB( _pObject );
				pTB->SetOperation( OPERATION_INTERSECTION );

				pTA->SetB( _pObject );
				pTA->SetOperation( OPERATION_INTERSECTION );

				SetB( pTB );
				SetOperation( OPERATION_UNION );
			}
			/* (9) (a – b) I t -> (a I t) – b */
			else if ( pTA->dwOperation == OPERATION_SUBTRACTION )
			{
				SetB( pTA->pB );
				SetOperation( OPERATION_SUBTRACTION );

				pTA->SetB( _pObject );
				pTA->SetOperation( OPERATION_INTERSECTION );
			}
			else
			{
				SetB( _pObject );
				SetOperation( OPERATION_INTERSECTION );
			}
		}
		else
		{
			SetB( _pObject );
			SetOperation( OPERATION_INTERSECTION );
		}
	}
	else
	{
		/* (7) (a U b) I t -> (a I t) U (b I t) */
		if ( dwOperation == OPERATION_UNION )
		{
			COMPLEX12* pTA = new COMPLEX12( pRender );
			pTA->SetA( pA );
			pTA->SetB( _pObject );
			pTA->SetOperation( OPERATION_INTERSECTION );

			COMPLEX12* pTB = new COMPLEX12( pRender );
			pTB->SetA( pB);
			pTB->SetB( _pObject );
			pTB->SetOperation( OPERATION_INTERSECTION );

			SetA( pTA );
			SetB( pTB );
			SetOperation( OPERATION_UNION );
		}
		/* (9) (a – b) I t -> (a I t) – b */
		if ( dwOperation == OPERATION_SUBTRACTION )
		{
			COMPLEX12* pTA = new COMPLEX12( pRender );
			pTA->SetA( pA );
			pTA->SetB( _pObject );
			pTA->SetOperation( OPERATION_INTERSECTION );

			SetA( pTA );
			SetOperation( OPERATION_SUBTRACTION );
		}
		else
		{
			COMPLEX12* pTA = new COMPLEX12( pRender );
			pTA->SetA( pA );
			pTA->SetB( pB );
			pTA->SetOperation( dwOperation );

			SetA( pTA );
			SetB( _pObject );
			SetOperation( OPERATION_INTERSECTION );
		}
	}

	_pObject->Hide();
}



VOID COMPLEX12::Union ( COMPLEX12* _pComplex )
{
	if ( pA == NULL && pB == NULL )
	{
		SetA( _pComplex );
		SetOperation( OPERATION_UNION );
	}
	else if ( pA == NULL )
	{
		pLog->Push( __FILE__, __LINE__, CODE_ERROR, CODE_COMPLEX12, 0x0001, this, NULL, NULL ); return;
	}
	else if ( pB == NULL )
	{
		SetB( _pComplex );
		SetOperation( OPERATION_UNION );
	}
	else
	{
		COMPLEX12* pTA = new COMPLEX12( pRender );
		pTA->SetA( pA );
		pTA->SetB( pB );
		pTA->SetOperation( dwOperation );

		SetA( pTA );
		SetB( _pComplex );
		SetOperation( OPERATION_UNION );
	}
}

VOID COMPLEX12::Subtraction ( COMPLEX12* _pComplex )
{
	if ( pA == NULL && pB == NULL )
	{
		pLog->Push( __FILE__, __LINE__, CODE_ERROR, CODE_COMPLEX12, 0x0002, this, NULL, NULL ); return;
	}
	else if ( pA == NULL )
	{
		pLog->Push( __FILE__, __LINE__, CODE_ERROR, CODE_COMPLEX12, 0x0003, this, NULL, NULL ); return;
	}
	else if ( pB == NULL )
	{
		if ( pA->IsComplex() )
		{
			COMPLEX12* pTA = (COMPLEX12*)pA;

			if ( pTA->dwOperation == OPERATION_UNION )
			{
				/* (10) (a U b) - (x U y) -> ((a - x) - y) U ((b - x) - y) */
				if ( _pComplex->dwOperation == OPERATION_UNION )
				{
					COMPLEX12* pTAA = new COMPLEX12( pRender );
					pTAA->SetA( pTA->pA );
					pTAA->SetB( _pComplex->pA );
					pTAA->SetOperation( OPERATION_SUBTRACTION );

					COMPLEX12* pTBA = new COMPLEX12( pRender );
					pTBA->SetA( pTA->pB );
					pTBA->SetB( _pComplex->pA );
					pTBA->SetOperation( OPERATION_SUBTRACTION );

					pTA->SetA( pTAA );
					pTA->SetB( _pComplex->pB );
					pTA->SetOperation( OPERATION_SUBTRACTION );

					COMPLEX12* pTB = new COMPLEX12( pRender );
					pTB->SetA( pTBA );
					pTB->SetB( _pComplex->pB );
					pTB->SetOperation( OPERATION_SUBTRACTION );

					SetA( pTA );
					SetB( pTB );
					SetOperation( OPERATION_UNION );
				}
				/* (11) (a U b) - (x - y) -> ((a - x) U (a I y)) U ((b - x) U (b I y)) */
				else if ( _pComplex->dwOperation == OPERATION_SUBTRACTION )
				{
					COMPLEX12* pTAA = new COMPLEX12( pRender );
					pTAA->SetA( pTA->pA );
					pTAA->SetB( _pComplex->pA );
					pTAA->SetOperation( OPERATION_SUBTRACTION );

					COMPLEX12* pTAB = new COMPLEX12( pRender );
					pTAB->SetA( pTA->pA );
					pTAB->SetB( _pComplex->pB );
					pTAB->SetOperation( OPERATION_INTERSECTION );

					COMPLEX12* pTBA = new COMPLEX12( pRender );
					pTBA->SetA( pTA->pB );
					pTBA->SetB( _pComplex->pA );
					pTBA->SetOperation( OPERATION_SUBTRACTION );

					COMPLEX12* pTBB = new COMPLEX12( pRender );
					pTBB->SetA( pTA->pB );
					pTBB->SetB( _pComplex->pB );
					pTBB->SetOperation( OPERATION_INTERSECTION );

					pTA->SetA( pTAA );
					pTA->SetB( pTAB );
					pTA->SetOperation( OPERATION_UNION );

					COMPLEX12* pTB = new COMPLEX12( pRender );
					pTB->SetA( pTBA );
					pTB->SetB( pTBB );
					pTB->SetOperation( OPERATION_UNION );

					SetA( pTA );
					SetB( pTB );
					SetOperation( OPERATION_UNION );
				}
				/* (12) (a U b) - (x I y) -> ((a - x) U (a - y)) U ((b - x) U (b - y)) */
				else if ( _pComplex->dwOperation == OPERATION_INTERSECTION )
				{
					COMPLEX12* pTAA = new COMPLEX12( pRender );
					pTAA->SetA( pTA->pA );
					pTAA->SetB( _pComplex->pA );
					pTAA->SetOperation( OPERATION_SUBTRACTION );

					COMPLEX12* pTAB = new COMPLEX12( pRender );
					pTAB->SetA( pTA->pA );
					pTAB->SetB( _pComplex->pB );
					pTAB->SetOperation( OPERATION_SUBTRACTION );

					COMPLEX12* pTBA = new COMPLEX12( pRender );
					pTBA->SetA( pTA->pB );
					pTBA->SetB( _pComplex->pA );
					pTBA->SetOperation( OPERATION_SUBTRACTION );

					COMPLEX12* pTBB = new COMPLEX12( pRender );
					pTBB->SetA( pTA->pB );
					pTBB->SetB( _pComplex->pB );
					pTBB->SetOperation( OPERATION_SUBTRACTION );

					pTA->SetA( pTAA );
					pTA->SetB( pTAB );
					pTA->SetOperation( OPERATION_UNION );

					COMPLEX12* pTB = new COMPLEX12( pRender );
					pTB->SetA( pTBA );
					pTB->SetB( pTBB );
					pTB->SetOperation( OPERATION_UNION );

					SetA( pTA );
					SetB( pTB );
					SetOperation( OPERATION_UNION );
				}
			}
			else if ( pTA->dwOperation == OPERATION_SUBTRACTION )
			{
				/* (16) (a - b) - (x U y) -> ((a - b) - x) - y */
				if ( _pComplex->dwOperation == OPERATION_UNION )
				{
					COMPLEX12* pTAA = new COMPLEX12( pRender );
					pTAA->SetA( pTA->pA );
					pTAA->SetB( pTA->pB );
					pTAA->SetOperation( OPERATION_SUBTRACTION );

					pTA->SetA( pTAA );
					pTA->SetB( _pComplex->pA );
					pTA->SetOperation( OPERATION_SUBTRACTION );

					SetA( pTA );
					SetB( _pComplex->pB );
					SetOperation( OPERATION_SUBTRACTION );
				}
				/* (17) (a - b) - (x - y) -> ((a - b) - x) U ((a I y) - b) */
				else if ( _pComplex->dwOperation == OPERATION_SUBTRACTION )
				{
					COMPLEX12* pTAA = new COMPLEX12( pRender );
					pTAA->SetA( pTA->pA );
					pTAA->SetB( pTA->pB );
					pTAA->SetOperation( OPERATION_SUBTRACTION );

					COMPLEX12* pTBA = new COMPLEX12( pRender );
					pTBA->SetA( pTA->pA );
					pTBA->SetB( _pComplex->pB );
					pTBA->SetOperation( OPERATION_INTERSECTION );

					COMPLEX12* pTB = new COMPLEX12( pRender );
					pTB->SetA( pTBA );
					pTB->SetB( pTA->pB );
					pTB->SetOperation( OPERATION_SUBTRACTION );

					pTA->SetA( pTAA );
					pTA->SetB( _pComplex->pA );
					pTA->SetOperation( OPERATION_SUBTRACTION );

					SetA( pTA );
					SetB( pTB );
					SetOperation( OPERATION_UNION );
				}
				/* (18) (a - b) - (x I y) -> ((a - b) - x) U ((a - b) - y) */
				else if ( _pComplex->dwOperation == OPERATION_INTERSECTION )
				{
					COMPLEX12* pTAA = new COMPLEX12( pRender );
					pTAA->SetA( pTA->pA );
					pTAA->SetB( pTA->pB );
					pTAA->SetOperation( OPERATION_SUBTRACTION );

					COMPLEX12* pTBA = new COMPLEX12( pRender );
					pTBA->SetA( pTA->pA );
					pTBA->SetB( pTA->pB );
					pTBA->SetOperation( OPERATION_SUBTRACTION );

					pTA->SetA( pTAA );
					pTA->SetB( _pComplex->pA );
					pTA->SetOperation( OPERATION_SUBTRACTION );

					COMPLEX12* pTB = new COMPLEX12( pRender );
					pTB->SetA( pTBA );
					pTB->SetB( _pComplex->pB );
					pTB->SetOperation( OPERATION_SUBTRACTION );

					SetA( pTA );
					SetB( pTB );
					SetOperation( OPERATION_UNION );
				}
			}
			else if ( pTA->dwOperation == OPERATION_INTERSECTION )
			{
				/* (22) (a I b) - (x U y) -> ((a I b) - x) - y */
				if ( _pComplex->dwOperation == OPERATION_UNION )
				{
					COMPLEX12* pTAA = new COMPLEX12( pRender );
					pTAA->SetA( pTA->pA );
					pTAA->SetB( pTA->pB );
					pTAA->SetOperation( OPERATION_INTERSECTION );

					pTA->SetA( pTAA );
					pTA->SetB( _pComplex->pA );
					pTA->SetOperation( OPERATION_SUBTRACTION );

					SetA( pTA );
					SetB( _pComplex->pB );
					SetOperation( OPERATION_SUBTRACTION );
				}
				/* (23) (a I b) - (x - y) -> ((a I b) - x) U ((a I b) I y) */
				else if ( _pComplex->dwOperation == OPERATION_SUBTRACTION )
				{
					COMPLEX12* pTAA = new COMPLEX12( pRender );
					pTAA->SetA( pTA->pA );
					pTAA->SetB( pTA->pB );
					pTAA->SetOperation( OPERATION_INTERSECTION );

					COMPLEX12* pTBA = new COMPLEX12( pRender );
					pTBA->SetA( pTA->pA );
					pTBA->SetB( pTA->pB );
					pTBA->SetOperation( OPERATION_INTERSECTION );

					pTA->SetA( pTAA );
					pTA->SetB( _pComplex->pA );
					pTA->SetOperation( OPERATION_SUBTRACTION );

					COMPLEX12* pTB = new COMPLEX12( pRender );
					pTB->SetA( pTBA );
					pTB->SetB( _pComplex->pB );
					pTB->SetOperation( OPERATION_INTERSECTION );

					SetA( pTA );
					SetB( pTB );
					SetOperation( OPERATION_UNION );
				}
				/* (24) (a I b) - (x I y) -> ((a I b) - x) U ((a I b) - y) */
				else if ( _pComplex->dwOperation == OPERATION_INTERSECTION )
				{
					COMPLEX12* pTAA = new COMPLEX12( pRender );
					pTAA->SetA( pTA->pA );
					pTAA->SetB( pTA->pB );
					pTAA->SetOperation( OPERATION_INTERSECTION );

					COMPLEX12* pTBA = new COMPLEX12( pRender );
					pTBA->SetA( pTA->pA );
					pTBA->SetB( pTA->pB );
					pTBA->SetOperation( OPERATION_INTERSECTION );

					pTA->SetA( pTAA );
					pTA->SetB( _pComplex->pA );
					pTA->SetOperation( OPERATION_SUBTRACTION );

					COMPLEX12* pTB = new COMPLEX12( pRender );
					pTB->SetA( pTBA );
					pTB->SetB( _pComplex->pB );
					pTB->SetOperation( OPERATION_SUBTRACTION );

					SetA( pTA );
					SetB( pTB );
					SetOperation( OPERATION_UNION );
				}
			}
		}
		else
		{
			/* (1) a – (x U y) -> (a – x) – y */
			if ( _pComplex->dwOperation == OPERATION_UNION )
			{
				COMPLEX12* pTA = new COMPLEX12( pRender );
				pTA->SetA( pA );
				pTA->SetB( _pComplex->pA );
				pTA->SetOperation( OPERATION_SUBTRACTION );

				SetA( pTA );
				SetB( _pComplex->pB );
				SetOperation( OPERATION_SUBTRACTION );
			}
			/* (3) a – (x - y) -> (a – x) U (a I y) */
			else if ( _pComplex->dwOperation == OPERATION_SUBTRACTION )
			{
				COMPLEX12* pTA = new COMPLEX12( pRender );
				pTA->SetA( pA );
				pTA->SetB( _pComplex->pA );
				pTA->SetOperation( OPERATION_SUBTRACTION );

				COMPLEX12* pTB = new COMPLEX12( pRender );
				pTB->SetA( pA );
				pTB->SetB( _pComplex->pB );
				pTB->SetOperation( OPERATION_INTERSECTION );

				SetA( pTA );
				SetB( pTB );
				SetOperation( OPERATION_UNION );
			}
			/* (5) a – (x I y) -> (a - x) U (a - y) */
			else if ( _pComplex->dwOperation == OPERATION_INTERSECTION )
			{
				COMPLEX12* pTA = new COMPLEX12( pRender );
				pTA->SetA( pA );
				pTA->SetB( _pComplex->pA );
				pTA->SetOperation( OPERATION_SUBTRACTION );

				COMPLEX12* pTB = new COMPLEX12( pRender );
				pTB->SetA( pA );
				pTB->SetB( _pComplex->pB );
				pTB->SetOperation( OPERATION_SUBTRACTION );

				SetA( pTA );
				SetB( pTB );
				SetOperation( OPERATION_UNION );
			}
		}
	}
	else
	{
		if ( dwOperation == OPERATION_UNION )
		{
			/* (10) (a U b) - (x U y) -> ((a - x) - y) U ((b - x) - y) */
			if ( _pComplex->dwOperation == OPERATION_UNION )
			{
				COMPLEX12* pTAA = new COMPLEX12( pRender );
				pTAA->SetA( pA );
				pTAA->SetB( _pComplex->pA );
				pTAA->SetOperation( OPERATION_SUBTRACTION );

				COMPLEX12* pTBA = new COMPLEX12( pRender );
				pTBA->SetA( pB );
				pTBA->SetB( _pComplex->pA );
				pTBA->SetOperation( OPERATION_SUBTRACTION );

				COMPLEX12* pTA = new COMPLEX12( pRender );
				pTA->SetA( pTAA );
				pTA->SetB( _pComplex->pB );
				pTA->SetOperation( OPERATION_SUBTRACTION );

				COMPLEX12* pTB = new COMPLEX12( pRender );
				pTB->SetA( pTBA );
				pTB->SetB( _pComplex->pB );
				pTB->SetOperation( OPERATION_SUBTRACTION );

				SetA( pTA );
				SetB( pTB );
				SetOperation( OPERATION_UNION );
			}
			/* (11) (a U b) - (x - y) -> ((a - x) U (a I y)) U ((b - x) U (b I y)) */
			else if ( _pComplex->dwOperation == OPERATION_SUBTRACTION )
			{
				COMPLEX12* pTAA = new COMPLEX12( pRender );
				pTAA->SetA( pA );
				pTAA->SetB( _pComplex->pA );
				pTAA->SetOperation( OPERATION_SUBTRACTION );

				COMPLEX12* pTAB = new COMPLEX12( pRender );
				pTAB->SetA( pA );
				pTAB->SetB( _pComplex->pB );
				pTAB->SetOperation( OPERATION_INTERSECTION );

				COMPLEX12* pTBA = new COMPLEX12( pRender );
				pTBA->SetA( pB );
				pTBA->SetB( _pComplex->pA );
				pTBA->SetOperation( OPERATION_SUBTRACTION );

				COMPLEX12* pTBB = new COMPLEX12( pRender );
				pTBB->SetA( pB );
				pTBB->SetB( _pComplex->pB );
				pTBB->SetOperation( OPERATION_INTERSECTION );

				COMPLEX12* pTA = new COMPLEX12( pRender );
				pTA->SetA( pTAA );
				pTA->SetB( pTAB );
				pTA->SetOperation( OPERATION_UNION );

				COMPLEX12* pTB = new COMPLEX12( pRender );
				pTB->SetA( pTBA );
				pTB->SetB( pTBB );
				pTB->SetOperation( OPERATION_UNION );

				SetA( pTA );
				SetB( pTB );
				SetOperation( OPERATION_UNION );
			}
			/* (12) (a U b) - (x I y) -> ((a - x) U (a - y)) U ((b - x) U (b - y)) */
			else if ( _pComplex->dwOperation == OPERATION_INTERSECTION )
			{
				COMPLEX12* pTAA = new COMPLEX12( pRender );
				pTAA->SetA( pA );
				pTAA->SetB( _pComplex->pA );
				pTAA->SetOperation( OPERATION_SUBTRACTION );

				COMPLEX12* pTAB = new COMPLEX12( pRender );
				pTAB->SetA( pA );
				pTAB->SetB( _pComplex->pB );
				pTAB->SetOperation( OPERATION_SUBTRACTION );

				COMPLEX12* pTBA = new COMPLEX12( pRender );
				pTBA->SetA( pB );
				pTBA->SetB( _pComplex->pA );
				pTBA->SetOperation( OPERATION_SUBTRACTION );

				COMPLEX12* pTBB = new COMPLEX12( pRender );
				pTBB->SetA( pB );
				pTBB->SetB( _pComplex->pB );
				pTBB->SetOperation( OPERATION_SUBTRACTION );

				COMPLEX12* pTA = new COMPLEX12( pRender );
				pTA->SetA( pTAA );
				pTA->SetB( pTAB );
				pTA->SetOperation( OPERATION_UNION );

				COMPLEX12* pTB = new COMPLEX12( pRender );
				pTB->SetA( pTBA );
				pTB->SetB( pTBB );
				pTB->SetOperation( OPERATION_UNION );

				SetA( pTA );
				SetB( pTB );
				SetOperation( OPERATION_UNION );
			}
		}
		else if ( dwOperation == OPERATION_SUBTRACTION )
		{
			/* (16) (a - b) - (x U y) -> ((a - b) - x) - y */
			if ( _pComplex->dwOperation == OPERATION_UNION )
			{
				COMPLEX12* pTAA = new COMPLEX12( pRender );
				pTAA->SetA( pA );
				pTAA->SetB( pB );
				pTAA->SetOperation( OPERATION_SUBTRACTION );

				COMPLEX12* pTA = new COMPLEX12( pRender );
				pTA->SetA( pTAA );
				pTA->SetB( _pComplex->pA );
				pTA->SetOperation( OPERATION_SUBTRACTION );

				SetA( pTA );
				SetB( _pComplex->pB );
				SetOperation( OPERATION_SUBTRACTION );
			}
			/* (17) (a - b) - (x - y) -> ((a - b) - x) U ((a I y) - b) */
			else if ( _pComplex->dwOperation == OPERATION_SUBTRACTION )
			{
				COMPLEX12* pTAA = new COMPLEX12( pRender );
				pTAA->SetA( pA );
				pTAA->SetB( pB );
				pTAA->SetOperation( OPERATION_SUBTRACTION );

				COMPLEX12* pTBA = new COMPLEX12( pRender );
				pTBA->SetA( pA );
				pTBA->SetB( _pComplex->pB );
				pTBA->SetOperation( OPERATION_INTERSECTION );

				COMPLEX12* pTA = new COMPLEX12( pRender );
				pTA->SetA( pTAA );
				pTA->SetB( _pComplex->pA );
				pTA->SetOperation( OPERATION_SUBTRACTION );

				COMPLEX12* pTB = new COMPLEX12( pRender );
				pTB->SetA( pTBA );
				pTB->SetB( pB );
				pTB->SetOperation( OPERATION_SUBTRACTION );

				SetA( pTA );
				SetB( pTB );
				SetOperation( OPERATION_UNION );
			}
			/* (18) (a - b) - (x I y) -> ((a - b) - x) U ((a - b) - y) */
			else if ( _pComplex->dwOperation == OPERATION_INTERSECTION )
			{
				COMPLEX12* pTAA = new COMPLEX12( pRender );
				pTAA->SetA( pA );
				pTAA->SetB( pB );
				pTAA->SetOperation( OPERATION_SUBTRACTION );

				COMPLEX12* pTBA = new COMPLEX12( pRender );
				pTBA->SetA( pA );
				pTBA->SetB( pB );
				pTBA->SetOperation( OPERATION_SUBTRACTION );

				COMPLEX12* pTA = new COMPLEX12( pRender );
				pTA->SetA( pTAA );
				pTA->SetB( _pComplex->pA );
				pTA->SetOperation( OPERATION_SUBTRACTION );

				COMPLEX12* pTB = new COMPLEX12( pRender );
				pTB->SetA( pTBA );
				pTB->SetB( _pComplex->pB );
				pTB->SetOperation( OPERATION_SUBTRACTION );

				SetA( pTA );
				SetB( pTB );
				SetOperation( OPERATION_UNION );
			}
		}
		else if ( dwOperation == OPERATION_INTERSECTION )
		{
			/* (22) (a I b) - (x U y) -> ((a I b) - x) - y */
			if ( _pComplex->dwOperation == OPERATION_UNION )
			{
				COMPLEX12* pTAA = new COMPLEX12( pRender );
				pTAA->SetA( pA );
				pTAA->SetB( pB );
				pTAA->SetOperation( OPERATION_INTERSECTION );

				COMPLEX12* pTA = new COMPLEX12( pRender );
				pTA->SetA( pTAA );
				pTA->SetB( _pComplex->pA );
				pTA->SetOperation( OPERATION_SUBTRACTION );

				SetA( pTA );
				SetB( _pComplex->pB );
				SetOperation( OPERATION_SUBTRACTION );
			}
			/* (23) (a I b) - (x - y) -> ((a I b) - x) U ((a I b) I y) */
			else if ( _pComplex->dwOperation == OPERATION_SUBTRACTION )
			{
				COMPLEX12* pTAA = new COMPLEX12( pRender );
				pTAA->SetA( pA );
				pTAA->SetB( pB );
				pTAA->SetOperation( OPERATION_INTERSECTION );

				COMPLEX12* pTBA = new COMPLEX12( pRender );
				pTBA->SetA( pA );
				pTBA->SetB( pB );
				pTBA->SetOperation( OPERATION_INTERSECTION );

				COMPLEX12* pTA = new COMPLEX12( pRender );
				pTA->SetA( pTAA );
				pTA->SetB( _pComplex->pA );
				pTA->SetOperation( OPERATION_SUBTRACTION );

				COMPLEX12* pTB = new COMPLEX12( pRender );
				pTB->SetA( pTBA );
				pTB->SetB( _pComplex->pB );
				pTB->SetOperation( OPERATION_INTERSECTION );

				SetA( pTA );
				SetB( pTB );
				SetOperation( OPERATION_UNION );
			}
			/* (24) (a I b) - (x I y) -> ((a I b) - x) U ((a I b) - y) */
			else if ( _pComplex->dwOperation == OPERATION_INTERSECTION )
			{
				COMPLEX12* pTAA = new COMPLEX12( pRender );
				pTAA->SetA( pA );
				pTAA->SetB( pB );
				pTAA->SetOperation( OPERATION_INTERSECTION );

				COMPLEX12* pTBA = new COMPLEX12( pRender );
				pTBA->SetA( pA );
				pTBA->SetB( pB );
				pTBA->SetOperation( OPERATION_INTERSECTION );

				COMPLEX12* pTA = new COMPLEX12( pRender );
				pTA->SetA( pTAA );
				pTA->SetB( _pComplex->pA );
				pTA->SetOperation( OPERATION_SUBTRACTION );

				COMPLEX12* pTB = new COMPLEX12( pRender );
				pTB->SetA( pTBA );
				pTB->SetB( _pComplex->pB );
				pTB->SetOperation( OPERATION_SUBTRACTION );

				SetA( pTA );
				SetB( pTB );
				SetOperation( OPERATION_UNION );
			}
		}
	}
}

VOID COMPLEX12::Intersection ( COMPLEX12* _pComplex )
{
	if ( pA == NULL && pB == NULL )
	{
		pLog->Push( __FILE__, __LINE__, CODE_ERROR, CODE_COMPLEX12, 0x0004, this, NULL, NULL ); return;
	}
	else if ( pA == NULL )
	{
		pLog->Push( __FILE__, __LINE__, CODE_ERROR, CODE_COMPLEX12, 0x0005, this, NULL, NULL ); return;
	}
	else if ( pB == NULL )
	{
		if ( pA->IsComplex() )
		{
			COMPLEX12* pTA = (COMPLEX12*)pA;

			if ( pTA->dwOperation == OPERATION_UNION )
			{
				/* (13) (a U b) I (x U y) -> ((a I x) U (a I y)) U ((b I x) U (b I y)) */
				if ( _pComplex->dwOperation == OPERATION_UNION )
				{
					COMPLEX12* pTAA = new COMPLEX12( pRender );
					pTAA->SetA( pTA->pA );
					pTAA->SetB( _pComplex->pA );
					pTAA->SetOperation( OPERATION_INTERSECTION );

					COMPLEX12* pTAB = new COMPLEX12( pRender );
					pTAB->SetA( pTA->pA );
					pTAB->SetB( _pComplex->pB );
					pTAB->SetOperation( OPERATION_INTERSECTION );

					COMPLEX12* pTBA = new COMPLEX12( pRender );
					pTBA->SetA( pTA->pB );
					pTBA->SetB( _pComplex->pA );
					pTBA->SetOperation( OPERATION_INTERSECTION );

					COMPLEX12* pTBB = new COMPLEX12( pRender );
					pTBB->SetA( pTA->pB );
					pTBB->SetB( _pComplex->pB );
					pTBB->SetOperation( OPERATION_INTERSECTION );

					pTA->SetA( pTAA );
					pTA->SetB( pTAB );
					pTA->SetOperation( OPERATION_UNION );

					COMPLEX12* pTB = new COMPLEX12( pRender );
					pTB->SetA( pTBA );
					pTB->SetB( pTBB );
					pTB->SetOperation( OPERATION_UNION );

					SetA( pTA );
					SetB( pTB );
					SetOperation( OPERATION_UNION );
				}
				/* (14) (a U b) I (x - y) -> ((a I x) - y) U ((b I x) - y) */
				else if ( _pComplex->dwOperation == OPERATION_SUBTRACTION )
				{
					COMPLEX12* pTAA = new COMPLEX12( pRender );
					pTAA->SetA( pTA->pA );
					pTAA->SetB( _pComplex->pA );
					pTAA->SetOperation( OPERATION_INTERSECTION );

					COMPLEX12* pTBA = new COMPLEX12( pRender );
					pTBA->SetA( pTA->pB );
					pTBA->SetB( _pComplex->pA );
					pTBA->SetOperation( OPERATION_INTERSECTION );

					pTA->SetA( pTAA );
					pTA->SetB( _pComplex->pB );
					pTA->SetOperation( OPERATION_SUBTRACTION );

					COMPLEX12* pTB = new COMPLEX12( pRender );
					pTB->SetA( pTBA );
					pTB->SetB( _pComplex->pB );
					pTB->SetOperation( OPERATION_SUBTRACTION );

					SetA( pTA );
					SetB( pTB );
					SetOperation( OPERATION_UNION );
				}
				/* (15) (a U b) I (x I y) -> ((a I x) I y) U ((b I x) I y) */
				else if ( _pComplex->dwOperation == OPERATION_INTERSECTION )
				{
					COMPLEX12* pTAA = new COMPLEX12( pRender );
					pTAA->SetA( pTA->pA );
					pTAA->SetB( _pComplex->pA );
					pTAA->SetOperation( OPERATION_INTERSECTION );

					COMPLEX12* pTBA = new COMPLEX12( pRender );
					pTBA->SetA( pTA->pB );
					pTBA->SetB( _pComplex->pA );
					pTBA->SetOperation( OPERATION_INTERSECTION );

					pTA->SetA( pTAA );
					pTA->SetB( _pComplex->pB );
					pTA->SetOperation( OPERATION_INTERSECTION );

					COMPLEX12* pTB = new COMPLEX12( pRender );
					pTB->SetA( pTBA );
					pTB->SetB( _pComplex->pB );
					pTB->SetOperation( OPERATION_INTERSECTION );

					SetA( pTA );
					SetB( pTB );
					SetOperation( OPERATION_UNION );
				}
			}
			else if ( pTA->dwOperation == OPERATION_SUBTRACTION )
			{
				/* (19) (a - b) I (x U y) -> ((a I x) - b) U ((a I y) - b) */
				if ( _pComplex->dwOperation == OPERATION_UNION )
				{
					COMPLEX12* pTAA = new COMPLEX12( pRender );
					pTAA->SetA( pTA->pA );
					pTAA->SetB( _pComplex->pA );
					pTAA->SetOperation( OPERATION_INTERSECTION );

					COMPLEX12* pTBA = new COMPLEX12( pRender );
					pTBA->SetA( pTA->pA );
					pTBA->SetB( _pComplex->pB );
					pTBA->SetOperation( OPERATION_INTERSECTION );

					pTA->SetA( pTAA );
					pTA->SetB( pTA->pB );
					pTA->SetOperation( OPERATION_SUBTRACTION );

					COMPLEX12* pTB = new COMPLEX12( pRender );
					pTB->SetA( pTBA );
					pTB->SetB( pTA->pB );
					pTB->SetOperation( OPERATION_SUBTRACTION );

					SetA( pTA );
					SetB( pTB );
					SetOperation( OPERATION_UNION );
				}
				/* (20) (a - b) I (x - y) -> ((a I x) - y) - b */
				else if ( _pComplex->dwOperation == OPERATION_SUBTRACTION )
				{
					COMPLEX12* pTAA = new COMPLEX12( pRender );
					pTAA->SetA( pTA->pA );
					pTAA->SetB( _pComplex->pA );
					pTAA->SetOperation( OPERATION_INTERSECTION );

					SetA( pTA );
					SetB( pTA->pB );
					SetOperation( OPERATION_SUBTRACTION );

					pTA->SetA( pTAA );
					pTA->SetB( _pComplex->pB );
					pTA->SetOperation( OPERATION_SUBTRACTION );
				}
				/* (21) (a - b) I (x I y) -> ((a I x) I y) - b */
				else if ( _pComplex->dwOperation == OPERATION_INTERSECTION )
				{
					COMPLEX12* pTAA = new COMPLEX12( pRender );
					pTAA->SetA( pTA->pA );
					pTAA->SetB( _pComplex->pA );
					pTAA->SetOperation( OPERATION_INTERSECTION );

					SetA( pTA );
					SetB( pTA->pB );
					SetOperation( OPERATION_SUBTRACTION );

					pTA->SetA( pTAA );
					pTA->SetB( _pComplex->pB );
					pTA->SetOperation( OPERATION_INTERSECTION );
				}
			}
			else if ( pTA->dwOperation == OPERATION_INTERSECTION )
			{
				/* (25) (a I b) I (x U y) -> ((a I b) I x) U ((a I b) I y) */
				if ( _pComplex->dwOperation == OPERATION_UNION )
				{
					COMPLEX12* pTAA = new COMPLEX12( pRender );
					pTAA->SetA( pTA->pA );
					pTAA->SetB( pTA->pB );
					pTAA->SetOperation( OPERATION_INTERSECTION );

					COMPLEX12* pTBA = new COMPLEX12( pRender );
					pTBA->SetA( pTA->pA );
					pTBA->SetB( pTA->pB );
					pTBA->SetOperation( OPERATION_INTERSECTION );

					pTA->SetA( pTAA );
					pTA->SetB( _pComplex->pA );
					pTA->SetOperation( OPERATION_INTERSECTION );

					COMPLEX12* pTB = new COMPLEX12( pRender );
					pTB->SetA( pTBA );
					pTB->SetB( _pComplex->pB );
					pTB->SetOperation( OPERATION_INTERSECTION );

					SetA( pTA );
					SetB( pTB );
					SetOperation( OPERATION_UNION );
				}
				/* (26) (a I b) I (x - y) -> ((a I b) I x) - y */
				else if ( _pComplex->dwOperation == OPERATION_SUBTRACTION )
				{
					COMPLEX12* pTAA = new COMPLEX12( pRender );
					pTAA->SetA( pTA->pA );
					pTAA->SetB( pTA->pB );
					pTAA->SetOperation( OPERATION_INTERSECTION );

					pTA->SetA( pTAA );
					pTA->SetB( _pComplex->pA );
					pTA->SetOperation( OPERATION_INTERSECTION );

					SetA( pTA );
					SetB( _pComplex->pB );
					SetOperation( OPERATION_SUBTRACTION );
				}
				/* (27) (a I b) I (x I y) -> ((a I b) I x) I y */
				else if ( _pComplex->dwOperation == OPERATION_INTERSECTION )
				{
					COMPLEX12* pTAA = new COMPLEX12( pRender );
					pTAA->SetA( pTA->pA );
					pTAA->SetB( pTA->pB );
					pTAA->SetOperation( OPERATION_INTERSECTION );

					pTA->SetA( pTAA );
					pTA->SetB( _pComplex->pA );
					pTA->SetOperation( OPERATION_INTERSECTION );

					SetA( pTA );
					SetB( _pComplex->pB );
					SetOperation( OPERATION_INTERSECTION );
				}
			}
		}
		else
		{
			/* (2) a I (x U y) -> (a I x) U (a I y) */
			if ( _pComplex->dwOperation == OPERATION_UNION )
			{
				COMPLEX12* pTA = new COMPLEX12( pRender );
				pTA->SetA( pA );
				pTA->SetB( _pComplex->pA );
				pTA->SetOperation( OPERATION_INTERSECTION );

				COMPLEX12* pTB = new COMPLEX12( pRender );
				pTB->SetA( pA );
				pTB->SetB( _pComplex->pB );
				pTB->SetOperation( OPERATION_INTERSECTION );

				SetA( pTA );
				SetB( pTB );
				SetOperation( OPERATION_UNION );
			}
			/* (4) a I (x - y) -> (a I x) – y */
			else if ( _pComplex->dwOperation == OPERATION_SUBTRACTION )
			{
				COMPLEX12* pTA = new COMPLEX12( pRender );
				pTA->SetA( pA );
				pTA->SetB( _pComplex->pA );
				pTA->SetOperation( OPERATION_INTERSECTION );

				SetA( pTA );
				SetB( _pComplex->pB );
				SetOperation( OPERATION_SUBTRACTION );
			}
			/* (6) a I (x I y) -> (a I x) I y */
			else if ( _pComplex->dwOperation == OPERATION_INTERSECTION )
			{
				COMPLEX12* pTA = new COMPLEX12( pRender );
				pTA->SetA( pA );
				pTA->SetB( _pComplex->pA );
				pTA->SetOperation( OPERATION_INTERSECTION );

				SetA( pTA );
				SetB( _pComplex->pB );
				SetOperation( OPERATION_INTERSECTION );
			}
		}
	}
	else
	{
		if ( dwOperation == OPERATION_UNION )
		{
			/* (13) (a U b) I (x U y) -> ((a I x) U (a I y)) U ((b I x) U (b I y)) */
			if ( _pComplex->dwOperation == OPERATION_UNION )
			{
				COMPLEX12* pTAA = new COMPLEX12( pRender );
				pTAA->SetA( pA );
				pTAA->SetB( _pComplex->pA );
				pTAA->SetOperation( OPERATION_INTERSECTION );

				COMPLEX12* pTAB = new COMPLEX12( pRender );
				pTAB->SetA( pA );
				pTAB->SetB( _pComplex->pB );
				pTAB->SetOperation( OPERATION_INTERSECTION );

				COMPLEX12* pTBA = new COMPLEX12( pRender );
				pTBA->SetA( pB );
				pTBA->SetB( _pComplex->pA );
				pTBA->SetOperation( OPERATION_INTERSECTION );

				COMPLEX12* pTBB = new COMPLEX12( pRender );
				pTBB->SetA( pB );
				pTBB->SetB( _pComplex->pB );
				pTBB->SetOperation( OPERATION_INTERSECTION );

				COMPLEX12* pTA = new COMPLEX12( pRender );
				pTA->SetA( pTAA );
				pTA->SetB( pTAB );
				pTA->SetOperation( OPERATION_UNION );

				COMPLEX12* pTB = new COMPLEX12( pRender );
				pTB->SetA( pTBA );
				pTB->SetB( pTBB );
				pTB->SetOperation( OPERATION_UNION );

				SetA( pTA );
				SetB( pTB );
				SetOperation( OPERATION_UNION );
			}
			/* (14) (a U b) I (x - y) -> ((a I x) - y) U ((b I x) - y) */
			else if ( _pComplex->dwOperation == OPERATION_SUBTRACTION )
			{
				COMPLEX12* pTAA = new COMPLEX12( pRender );
				pTAA->SetA( pA );
				pTAA->SetB( _pComplex->pA );
				pTAA->SetOperation( OPERATION_INTERSECTION );

				COMPLEX12* pTBA = new COMPLEX12( pRender );
				pTBA->SetA( pB );
				pTBA->SetB( _pComplex->pA );
				pTBA->SetOperation( OPERATION_INTERSECTION );

				COMPLEX12* pTA = new COMPLEX12( pRender );
				pTA->SetA( pTAA );
				pTA->SetB( _pComplex->pB );
				pTA->SetOperation( OPERATION_SUBTRACTION );

				COMPLEX12* pTB = new COMPLEX12( pRender );
				pTB->SetA( pTBA );
				pTB->SetB( _pComplex->pB );
				pTB->SetOperation( OPERATION_SUBTRACTION );

				SetA( pTA );
				SetB( pTB );
				SetOperation( OPERATION_UNION );
			}
			/* (15) (a U b) I (x I y) -> ((a I x) I y) U ((b I x) I y) */
			else if ( _pComplex->dwOperation == OPERATION_INTERSECTION )
			{
				COMPLEX12* pTAA = new COMPLEX12( pRender );
				pTAA->SetA( pA );
				pTAA->SetB( _pComplex->pA );
				pTAA->SetOperation( OPERATION_INTERSECTION );

				COMPLEX12* pTBA = new COMPLEX12( pRender );
				pTBA->SetA( pB );
				pTBA->SetB( _pComplex->pA );
				pTBA->SetOperation( OPERATION_INTERSECTION );

				COMPLEX12* pTA = new COMPLEX12( pRender );
				pTA->SetA( pTAA );
				pTA->SetB( _pComplex->pB );
				pTA->SetOperation( OPERATION_INTERSECTION );

				COMPLEX12* pTB = new COMPLEX12( pRender );
				pTB->SetA( pTBA );
				pTB->SetB( _pComplex->pB );
				pTB->SetOperation( OPERATION_INTERSECTION );

				SetA( pTA );
				SetB( pTB );
				SetOperation( OPERATION_UNION );
			}
		}
		else if ( dwOperation == OPERATION_SUBTRACTION )
		{
			/* (19) (a - b) I (x U y) -> ((a I x) - b) U ((a I y) - b) */
			if ( _pComplex->dwOperation == OPERATION_UNION )
			{
				COMPLEX12* pTAA = new COMPLEX12( pRender );
				pTAA->SetA( pA );
				pTAA->SetB( _pComplex->pA );
				pTAA->SetOperation( OPERATION_INTERSECTION );

				COMPLEX12* pTBA = new COMPLEX12( pRender );
				pTBA->SetA( pA );
				pTBA->SetB( _pComplex->pB );
				pTBA->SetOperation( OPERATION_INTERSECTION );

				COMPLEX12* pTA = new COMPLEX12( pRender );
				pTA->SetA( pTAA );
				pTA->SetB( pB );
				pTA->SetOperation( OPERATION_SUBTRACTION );

				COMPLEX12* pTB = new COMPLEX12( pRender );
				pTB->SetA( pTBA );
				pTB->SetB( pB );
				pTB->SetOperation( OPERATION_SUBTRACTION );

				SetA( pTA );
				SetB( pTB );
				SetOperation( OPERATION_UNION );
			}
			/* (20) (a - b) I (x - y) -> ((a I x) - y) - b */
			else if ( _pComplex->dwOperation == OPERATION_SUBTRACTION )
			{
				COMPLEX12* pTAA = new COMPLEX12( pRender );
				pTAA->SetA( pA );
				pTAA->SetB( _pComplex->pA );
				pTAA->SetOperation( OPERATION_INTERSECTION );

				COMPLEX12* pTA = new COMPLEX12( pRender );
				pTA->SetA( pTAA );
				pTA->SetB( _pComplex->pB );
				pTA->SetOperation( OPERATION_SUBTRACTION );

				SetA( pTA );
				SetB( pB );
				SetOperation( OPERATION_SUBTRACTION );
			}
			/* (21) (a - b) I (x I y) -> ((a I x) I y) - b */
			else if ( _pComplex->dwOperation == OPERATION_INTERSECTION )
			{
				COMPLEX12* pTAA = new COMPLEX12( pRender );
				pTAA->SetA( pA );
				pTAA->SetB( _pComplex->pA );
				pTAA->SetOperation( OPERATION_INTERSECTION );

				COMPLEX12* pTA = new COMPLEX12( pRender );
				pTA->SetA( pTAA );
				pTA->SetB( _pComplex->pB );
				pTA->SetOperation( OPERATION_INTERSECTION );

				SetA( pTA );
				SetB( pB );
				SetOperation( OPERATION_SUBTRACTION );
			}
		}
		else if ( dwOperation == OPERATION_INTERSECTION )
		{
			/* (25) (a I b) I (x U y) -> ((a I b) I x) U ((a I b) I y) */
			if ( _pComplex->dwOperation == OPERATION_UNION )
			{
				COMPLEX12* pTAA = new COMPLEX12( pRender );
				pTAA->SetA( pA );
				pTAA->SetB( pB );
				pTAA->SetOperation( OPERATION_INTERSECTION );

				COMPLEX12* pTBA = new COMPLEX12( pRender );
				pTBA->SetA( pA );
				pTBA->SetB( pB );
				pTBA->SetOperation( OPERATION_INTERSECTION );

				COMPLEX12* pTA = new COMPLEX12( pRender );
				pTA->SetA( pTAA );
				pTA->SetB( _pComplex->pA );
				pTA->SetOperation( OPERATION_INTERSECTION );

				COMPLEX12* pTB = new COMPLEX12( pRender );
				pTB->SetA( pTBA );
				pTB->SetB( _pComplex->pB );
				pTB->SetOperation( OPERATION_INTERSECTION );

				SetA( pTA );
				SetB( pTB );
				SetOperation( OPERATION_UNION );
			}
			/* (26) (a I b) I (x - y) -> ((a I b) I x) - y */
			else if ( _pComplex->dwOperation == OPERATION_SUBTRACTION )
			{
				COMPLEX12* pTAA = new COMPLEX12( pRender );
				pTAA->SetA( pA );
				pTAA->SetB( pB );
				pTAA->SetOperation( OPERATION_INTERSECTION );

				COMPLEX12* pTA = new COMPLEX12( pRender );
				pTA->SetA( pTAA );
				pTA->SetB( _pComplex->pA );
				pTA->SetOperation( OPERATION_INTERSECTION );

				SetA( pTA );
				SetB( _pComplex->pB );
				SetOperation( OPERATION_SUBTRACTION );
			}
			/* (27) (a I b) I (x I y) -> ((a I b) I x) I y */
			else if ( _pComplex->dwOperation == OPERATION_INTERSECTION )
			{
				COMPLEX12* pTAA = new COMPLEX12( pRender );
				pTAA->SetA( pA );
				pTAA->SetB( pB );
				pTAA->SetOperation( OPERATION_INTERSECTION );

				COMPLEX12* pTA = new COMPLEX12( pRender );
				pTA->SetA( pTAA );
				pTA->SetB( _pComplex->pA );
				pTA->SetOperation( OPERATION_INTERSECTION );

				SetA( pTA );
				SetB( _pComplex->pB );
				SetOperation( OPERATION_INTERSECTION );
			}
		}
	}
}