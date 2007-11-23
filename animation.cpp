
#include "animation.h"
#include "render.h"
#include "indexer.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



ANIMATION12::ANIMATION12 ( RENDER12* _pRender ) : TEXTURE12( _pRender )
{
	_pRender->iAnimation->Add( this );

	lpUpdateCallback = NULL;
	lpUpdateData = NULL;

	dwTexture = 0;
	ppTexture = NULL;

	dwFrameCount = 0;
	lpFrameStart = NULL;
	lpFrameStop = NULL;

	dwTime = 0;
	fSpeed = 1.0f;
}

ANIMATION12::~ANIMATION12 ( )
{
	pRender->iAnimation->Del( this );

	while ( lpFrameStart )
	{
		FRAME12* tFrame = lpFrameStart;

		lpFrameStart = lpFrameStart->pn;

		delete tFrame;
	}

	if ( ppTexture )
	{
		delete [] ppTexture;
		ppTexture = NULL;
	}

	lpD3DTexture = NULL;
}



ANIMATION12* ANIMATION12::Copy( BOOLEAN bCopyPixelData )
{
	/* creation de la texture */
	ANIMATION12* pAnimation = new ANIMATION12( pRender );

	/* copie de la callback */
	pAnimation->lpUpdateCallback = lpUpdateCallback;
	pAnimation->lpUpdateData = lpUpdateData;

	/* copie des textures */
	for ( DWORD k = 0 ; k < dwTexture ; k++ )
	{
		pAnimation->AddTexture( ppTexture[k]->Copy( bCopyPixelData ) );
	}

	/* copie des frames */
	FRAME12* tFrame = lpFrameStart;
	while ( tFrame )
	{
		pAnimation->AddFrame( -1, tFrame->pt, tFrame->dt, tFrame->tu, tFrame->tv, tFrame->su, tFrame->sv );

		tFrame = tFrame->pn;
	}

	/* copie de la vitesse */
	pAnimation->fSpeed = fSpeed;

	return pAnimation;
}




BOOLEAN ANIMATION12::Load ( LPSTR _sFile )
{
	if ( _sFile == NULL )
	{
		pLog->Push( __FILE__, __LINE__, CODE_ERROR, CODE_ANIMATION12, 0x0001, this, NULL, NULL ); return 0;
	}
	else if ( CheckFile( _sFile ) == 0 ) 
	{
		pLog->Push( __FILE__, __LINE__, CODE_ERROR, CODE_ANIMATION12, 0x0002, this, NULL, _sFile ); return 0;
	}

	// à faire

	return 1;
}



VOID ANIMATION12::AddTexture ( TEXTURE12* _pTexture )
{
	dwTexture++;
	ppTexture = (TEXTURE12**) realloc( ppTexture, dwTexture * sizeof(LPVOID) );
	ppTexture[dwTexture-1] = _pTexture;
}

VOID ANIMATION12::DelTexture ( TEXTURE12* _pTexture )
{
	for ( DWORD i = 0L ; i < dwTexture ; i++ )
	{
		if ( ppTexture[i] )
		{
			if ( ppTexture[i] == _pTexture )
			{
				ppTexture[i] = NULL;
			}
		}
	}
}



ANIMATION12::FRAME12* ANIMATION12::GetFrame ( DWORD _dwTime )
{
	DWORD tTime = 0;

	FRAME12* tFrame = lpFrameStart;
	while ( tFrame )
	{
		tTime += tFrame->dt;

		if ( tTime > _dwTime ) break;

		tFrame = tFrame->pn;
	}

	return tFrame;
}



VOID ANIMATION12::AddFrame ( DWORD _dwTime, TEXTURE12* pt, DWORD dt, FLOAT tu, FLOAT tv, FLOAT su, FLOAT sv )
{
	/* la nouvelle frame doit être mise à la fin (NB : (DWORD)(-1) > dwTime) */
	if ( _dwTime >= dwTime )
	{
		/* s'il existe déjà au moins une frame alors on crée la nouvelle */
		/* après la dernière et on fait de celle-ci la nouvelle dernière */
		if ( lpFrameStart )
		{
			lpFrameStop->pn = new FRAME12;
			lpFrameStop = lpFrameStop->pn;
		}
		/* sinon on crée la première frame et on la repère comme étant aussi la dernière */
		else
		{
			lpFrameStart = new FRAME12;
			lpFrameStop = lpFrameStart;
		}

		/* ainsi on spécifie les attributs de la nouvelle dernière frame */
		lpFrameStop->pt = pt;
		lpFrameStop->dt = dt;
		lpFrameStop->tu = tu;
		lpFrameStop->tv = tv;
		lpFrameStop->su = su;
		lpFrameStop->sv = sv;
		lpFrameStop->pn = NULL;
	}
	/* sinon on recherche l'endroit à laquelle doit être créée la nouvelle frame */
	else
	{
		DWORD tTime = 0;

		FRAME12* tParent = NULL;
		FRAME12* tFrame = lpFrameStart;
		while ( tFrame )
		{
			tTime += tFrame->dt;

			if ( tTime > _dwTime ) break;

			tParent = tFrame;
			tFrame = tFrame->pn;
		}

		/* la nouvelle frame est ajoutée après la précédente */
		if ( tParent )
		{
			tFrame = new FRAME12;
			tFrame->pn = tParent->pn;

			tParent->pn = tFrame;
		}
		/* la nouvelle frame est insérée avant l'actuelle première */
		else
		{
			tFrame = new FRAME12;
			tFrame->pn = lpFrameStart;

			lpFrameStart = tFrame;
		}

		/* on spécifie les attributs de la nouvelle frame */
		tFrame->pt = pt;
		tFrame->dt = dt;
		tFrame->tu = tu;
		tFrame->tv = tv;
		tFrame->su = su;
		tFrame->sv = sv;
	}

	/* on ajoute le temps de la nouvelle frame au temps total */
	dwTime += dt;

	/* on décompte une frame de plus */
	dwFrameCount++;
}

VOID ANIMATION12::SetFrameTexture ( DWORD _dwTime, TEXTURE12* pt )
{
	FRAME12* tFrame = GetFrame( _dwTime );

	if ( tFrame )
		tFrame->pt = pt;
}

TEXTURE12* ANIMATION12::GetFrameTexture ( DWORD _dwTime )
{
	FRAME12* tFrame = GetFrame( _dwTime );

	if ( tFrame )
		return tFrame->pt;
	else
		return NULL;
}

VOID ANIMATION12::SetFrameTime ( DWORD _dwTime, DWORD dt )
{
	FRAME12* tFrame = GetFrame( _dwTime );

	if ( tFrame )
	{
		dwTime -= tFrame->dt;
		dwTime += dt;

		tFrame->dt = dt;
	}
}

DWORD ANIMATION12::GetFrameTime ( DWORD _dwTime )
{
	FRAME12* tFrame = GetFrame( _dwTime );

	if ( tFrame )
		return tFrame->dt;
	else
		return -1;
}

VOID ANIMATION12::DelFrame ( DWORD _dwTime )
{
	DWORD tTime = 0;

	FRAME12* tParent = NULL;
	FRAME12* tFrame = lpFrameStart;
	while ( tFrame )
	{
		tTime += tFrame->dt;

		if ( tTime > _dwTime ) break;

		tParent = tFrame;
		tFrame = tFrame->pn;
	}

	if ( tFrame == lpFrameStart )
	{
		lpFrameStart = lpFrameStart->pn;

		if ( lpFrameStop == tFrame )
			lpFrameStop = NULL;

		delete tFrame;
	}
	else
	{
		if ( tFrame )
		{
			tParent->pn = tFrame->pn;

			if ( lpFrameStop == tFrame )
				lpFrameStop = NULL;

			delete tFrame;
		}
	}
}



_inline DWORD ANIMATION12::FrameCount ( )
{
	return dwFrameCount;
}

_inline DWORD ANIMATION12::TimeCount ( )
{
	return dwTime;
}



VOID ANIMATION12::SetSpeed ( FLOAT _fSpeed )
{
	fSpeed = _fSpeed;
}

_inline FLOAT ANIMATION12::GetSpeed ( )
{
	return fSpeed;
}



VOID ANIMATION12::SetUpdateCallback ( LPANIMATIONCALLBACK _lpCallback )
{
	lpUpdateCallback = _lpCallback;
}

VOID ANIMATION12::SetUpdateData ( LPVOID _lpData )
{
	lpUpdateData = _lpData;
}



VOID ANIMATION12::Update ( )
{
	FLOAT fTime = (FLOAT)GetTickCount() * fSpeed;

	FRAME12* tFrame = GetFrame( (DWORD)(fTime) % dwTime );

	TEXTURE12* tTexture = tFrame->pt;
	lpD3DTexture = tTexture->lpD3DTexture;

	SetOffset( tFrame->tu, tFrame->tv );
	SetZoom( tFrame->su, tFrame->sv );

	if ( lpUpdateCallback )
		lpUpdateCallback( lpUpdateData );
}
