
#include "object.h"
#include "scene.h"
#include "render.h"
#include "indexer.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



_inline VOID OBJECT12::SetParent ( OBJECT12* _pParent )
{
	pParent = _pParent;

	if ( pParent )
		SetScene( pParent->pScene );
}

_inline OBJECT12* OBJECT12::GetParent ( )
{
	return pParent;
}



VOID OBJECT12::SetScene ( SCENE12* _pScene )
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
}

SCENE12* OBJECT12::GetScene ( )
{
	return pScene;
}



VOID OBJECT12::AddChild ( OBJECT12* _pChild )
{
	_pChild->SetParent( this );

	iChild->Add( _pChild );

	bHitbox = FALSE;
}

VOID OBJECT12::DelChild ( OBJECT12* _pChild )
{
	_pChild->SetParent( NULL );

	iChild->Del( _pChild );

	bHitbox = FALSE;
}



VOID OBJECT12::AddTexture ( TEXTURE12* _pTexture )
{
	iTexture->Add( _pTexture );
}

VOID OBJECT12::DelTexture ( TEXTURE12* _pTexture )
{
	iTexture->Del( _pTexture );
}
