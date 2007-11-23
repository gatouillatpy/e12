
#include "object.h"
#include "scene.h"
#include "render.h"
#include "indexer.h"
#include "document.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



BOOLEAN OBJECT12::Load ( LPSTR _sFile )
{

	return 1;
}

BOOLEAN OBJECT12::Save ( LPSTR _sFile )
{
	DOCUMENT12* pRoot = new DOCUMENT12( pLog );

	pRoot->SetClass( "root" );
	
	if ( sName != NULL )
		pRoot->SetName( sName );

	if ( dwIndex != -1 )
		pRoot->SetIndex( dwIndex );

	// bComplex
	{
		DOCUMENT12* pValue = new DOCUMENT12( pRoot );
		pValue->SetClass( "iscomplex" );
		pValue->SetInteger( bComplex );
	}

	// vCenter
	{
		DOCUMENT12* pVector = new DOCUMENT12( pRoot );
		pVector->SetClass( "center" );

		{
			DOCUMENT12* pValueA = new DOCUMENT12( pVector );
			pValueA->SetClass( "x" );
			pValueA->SetFloat( vCenter.x );

			DOCUMENT12* pValueB = new DOCUMENT12( pVector );
			pValueB->SetClass( "y" );
			pValueB->SetFloat( vCenter.y );

			DOCUMENT12* pValueC = new DOCUMENT12( pVector );
			pValueC->SetClass( "z" );
			pValueC->SetFloat( vCenter.z );
		}
	}

	// vAngle
	{
		DOCUMENT12* pVector = new DOCUMENT12( pRoot );
		pVector->SetClass( "angle" );

		{
			DOCUMENT12* pValueA = new DOCUMENT12( pVector );
			pValueA->SetClass( "x" );
			pValueA->SetFloat( vAngle.x );

			DOCUMENT12* pValueB = new DOCUMENT12( pVector );
			pValueB->SetClass( "y" );
			pValueB->SetFloat( vAngle.y );

			DOCUMENT12* pValueC = new DOCUMENT12( pVector );
			pValueC->SetClass( "z" );
			pValueC->SetFloat( vAngle.z );
		}
	}

	// vSize
	{
		DOCUMENT12* pVector = new DOCUMENT12( pRoot );
		pVector->SetClass( "size" );

		{
			DOCUMENT12* pValueA = new DOCUMENT12( pVector );
			pValueA->SetClass( "x" );
			pValueA->SetFloat( vSize.x );

			DOCUMENT12* pValueB = new DOCUMENT12( pVector );
			pValueB->SetClass( "y" );
			pValueB->SetFloat( vSize.y );

			DOCUMENT12* pValueC = new DOCUMENT12( pVector );
			pValueC->SetClass( "z" );
			pValueC->SetFloat( vSize.z );
		}
	}

	pRoot->Save( _sFile );

	delete pRoot;

	return 1;
}
