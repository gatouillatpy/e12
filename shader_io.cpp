
#include "shader.h"
#include "render.h"
#include "resource.h"
#include "engine.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



BOOLEAN SHADER12::QuickLoad ( LPSTR _sFile )
{
	if ( pResource )
		pResource->DelEntity( this );

	pResource = pEngine->GetResource( _sFile );

	if ( pResource )
	{
		pResource->AddEntity( this );

		if ( lpVertexShader )
			lpVertexShader->Release();

		if ( lpPixelShader )
			lpPixelShader->Release();

		if( lpVSCode )
			lpVSCode->Release(); 

		if( lpPSCode )
			lpPSCode->Release(); 

		if( lpVSData )
			lpVSData->Release(); 

		if( lpPSData )
			lpPSData->Release();

		SHADER12* pSource = (SHADER12*)pResource->Entity();

		pSource->AddRef();

		lpVertexShader = pSource->lpVertexShader;
		lpVertexShader->AddRef();

		lpPixelShader = pSource->lpPixelShader;
		lpPixelShader->AddRef();

		lpVSCode = pSource->lpVSCode;
		lpVSCode->AddRef();

		lpPSCode = pSource->lpPSCode;
		lpPSCode->AddRef();

		lpVSData = pSource->lpVSData;
		lpVSData->AddRef();

		lpPSData = pSource->lpPSData;
		lpPSData->AddRef();
	}
	else
	{
		Load( _sFile );

		pResource = pEngine->AddResource( this, _sFile );
	}

	return 1;
}

BOOLEAN SHADER12::QuickSave ( LPSTR _sFile )
{
	if ( pResource )
		pResource->DelEntity( this );

	pResource = pEngine->GetResource( _sFile );

	if ( pResource )
		pEngine->DelResource( _sFile );

	Save( _sFile );

	pResource = pEngine->AddResource( this, _sFile );

	return 1;
}



BOOLEAN SHADER12::Load ( LPSTR _sFile )
{
	if ( lpVertexShader )
		lpVertexShader->Release();

	if ( lpPixelShader )
		lpPixelShader->Release();

	if( lpVSCode )
		lpVSCode->Release(); 

	if( lpPSCode )
		lpPSCode->Release(); 

	if( lpVSData )
		lpVSData->Release(); 

	if( lpPSData )
		lpPSData->Release(); 

	if ( _sFile == NULL )
	{
		pLog->Push( __FILE__, __LINE__, CODE_ERROR, CODE_SHADER12, 0x0001, this, NULL, NULL ); return 0;
	}
	else if ( CheckFile( _sFile ) == 0 ) 
	{
		pLog->Push( __FILE__, __LINE__, CODE_ERROR, CODE_SHADER12, 0x0002, this, NULL, _sFile ); return 0;
	}

	FILE* pFile = NULL;

	fopen_s(&pFile, _sFile, "rb");

	fseek( pFile, 0, SEEK_SET );

	DWORD dwSize = 0;

	fread( &dwSize, sizeof(DWORD), 1, pFile );
	if ( dwSize )
	{
		D3DXCreateBuffer( dwSize, &lpVSCode );

		fread( lpVSCode->GetBufferPointer(), sizeof(BYTE), dwSize, pFile );

		pRender->lpD3DDevice->CreateVertexShader( (DWORD*)lpVSCode->GetBufferPointer(), &lpVertexShader );
		D3DXGetShaderConstantTable( (DWORD*)lpVSCode->GetBufferPointer(), &lpVSData );
	}

	fread( &dwSize, sizeof(DWORD), 1, pFile );
	if ( dwSize )
	{
		D3DXCreateBuffer( dwSize, &lpPSCode );

		fread( lpPSCode->GetBufferPointer(), sizeof(BYTE), dwSize, pFile );

		pRender->lpD3DDevice->CreatePixelShader( (DWORD*)lpPSCode->GetBufferPointer(), &lpPixelShader );
		D3DXGetShaderConstantTable( (DWORD*)lpPSCode->GetBufferPointer(), &lpPSData );
	}

	fclose( pFile );

	return 1;
}

BOOLEAN SHADER12::Save ( LPSTR _sFile )
{
	FILE* pFile = NULL;
	if ( fopen_s(&pFile, _sFile, "wb") )
		return 0;

	fseek( pFile, 0, SEEK_SET );

	DWORD dwSize = 0;

	if ( lpVertexShader )
	{
		dwSize = lpVSCode->GetBufferSize();
		fwrite( &dwSize, sizeof(DWORD), 1, pFile );
		fwrite( lpVSCode->GetBufferPointer(), sizeof(BYTE), dwSize, pFile );
	}
	else
	{
		dwSize = 0;
		fwrite( &dwSize, sizeof(DWORD), 1, pFile );
	}

	if ( lpPixelShader )
	{
		dwSize = lpPSCode->GetBufferSize();
		fwrite( &dwSize, sizeof(DWORD), 1, pFile );
		fwrite( lpPSCode->GetBufferPointer(), sizeof(BYTE), dwSize, pFile );
	}
	else
	{
		dwSize = 0;
		fwrite( &dwSize, sizeof(DWORD), 1, pFile );
	}

	fclose( pFile );

	return 1;
}



VOID SHADER12::AssembleVSFile ( LPSTR _sFile )
{
	if( lpVSCode )
		lpVSCode->Release(); 

	D3DXAssembleShaderFromFile( _sFile, NULL, NULL, NULL,	&lpVSCode, &lpError );

	if ( lpVertexShader )
		lpVertexShader->Release();

	pRender->lpD3DDevice->CreateVertexShader( (DWORD*)lpVSCode->GetBufferPointer(), &lpVertexShader );
}

VOID SHADER12::AssemblePSFile ( LPSTR _sFile )
{
	if( lpPSCode )
		lpPSCode->Release(); 

	D3DXAssembleShaderFromFile( _sFile, NULL, NULL, NULL,	&lpPSCode, &lpError );

	if ( lpPixelShader )
		lpPixelShader->Release();

	pRender->lpD3DDevice->CreatePixelShader( (DWORD*)lpPSCode->GetBufferPointer(), &lpPixelShader );
}

VOID SHADER12::AssembleVSCode ( LPSTR _sCode )
{
	if( lpVSCode )
		lpVSCode->Release(); 

	D3DXAssembleShader( _sCode, strlen(_sCode), NULL, NULL, NULL, &lpVSCode, &lpError );

	if ( lpVertexShader )
		lpVertexShader->Release();

	pRender->lpD3DDevice->CreateVertexShader( (DWORD*)lpVSCode->GetBufferPointer(), &lpVertexShader );
}

VOID SHADER12::AssemblePSCode ( LPSTR _sCode )
{
	if( lpPSCode )
		lpPSCode->Release(); 

	D3DXAssembleShader( _sCode, strlen(_sCode), NULL, NULL, NULL, &lpPSCode, &lpError );

	if ( lpPixelShader )
		lpPixelShader->Release();

	pRender->lpD3DDevice->CreatePixelShader( (DWORD*)lpPSCode->GetBufferPointer(), &lpPixelShader );
}

VOID SHADER12::CompileVSFile ( LPSTR _sFile, LPSTR _sProfile, LPSTR _sFunction )
{
	if( lpVSCode )
		lpVSCode->Release(); 

	if( lpVSData )
		lpVSData->Release(); 

#ifndef DEBUG_SHADER
	D3DXCompileShaderFromFile( _sFile, NULL, NULL, _sFunction, _sProfile, NULL, &lpVSCode, &lpError, &lpVSData );
#else
	D3DXCompileShaderFromFile( _sFile, NULL, NULL, _sFunction, _sProfile, D3DXSHADER_DEBUG | D3DXSHADER_SKIPOPTIMIZATION, &lpVSCode, &lpError, &lpVSData );
#endif

	if ( lpVSCode == NULL )	return;

	if ( lpVertexShader )
		lpVertexShader->Release();

	pRender->lpD3DDevice->CreateVertexShader( (DWORD*)lpVSCode->GetBufferPointer(), &lpVertexShader );
}

VOID SHADER12::CompilePSFile ( LPSTR _sFile, LPSTR _sProfile, LPSTR _sFunction )
{
	if( lpPSCode )
		lpPSCode->Release(); 

	if( lpPSData )
		lpPSData->Release(); 

#ifndef DEBUG_SHADER
	D3DXCompileShaderFromFile( _sFile, NULL, NULL, _sFunction, _sProfile, NULL, &lpPSCode, &lpError, &lpPSData );
#else
	D3DXCompileShaderFromFile( _sFile, NULL, NULL, _sFunction, _sProfile, D3DXSHADER_DEBUG | D3DXSHADER_SKIPOPTIMIZATION, &lpPSCode, &lpError, &lpPSData );
#endif

	if ( lpPSCode == NULL )	return;

	if ( lpPixelShader )
		lpPixelShader->Release();

	pRender->lpD3DDevice->CreatePixelShader( (DWORD*)lpPSCode->GetBufferPointer(), &lpPixelShader );
}

VOID SHADER12::CompileVSCode ( LPSTR _sCode, LPSTR _sProfile, LPSTR _sFunction )
{
	if( lpVSCode )
		lpVSCode->Release(); 

	if( lpVSData )
		lpVSData->Release(); 

#ifndef DEBUG_SHADER
	D3DXCompileShader( _sCode, strlen(_sCode), NULL, NULL, _sFunction, _sProfile, NULL, &lpVSCode, &lpError, &lpVSData );
#else
	D3DXCompileShader( _sCode, strlen(_sCode), NULL, NULL, _sFunction, _sProfile, D3DXSHADER_DEBUG | D3DXSHADER_SKIPOPTIMIZATION, &lpVSCode, &lpError, &lpVSData );
#endif

	if ( lpVertexShader )
		lpVertexShader->Release();

	pRender->lpD3DDevice->CreateVertexShader( (DWORD*)lpVSCode->GetBufferPointer(), &lpVertexShader );
}

VOID SHADER12::CompilePSCode ( LPSTR _sCode, LPSTR _sProfile, LPSTR _sFunction )
{
	if( lpPSCode )
		lpPSCode->Release(); 

	if( lpPSData )
		lpPSData->Release(); 

#ifndef DEBUG_SHADER
	D3DXCompileShader( _sCode, strlen(_sCode), NULL, NULL, _sFunction, _sProfile, NULL, &lpPSCode, &lpError, &lpPSData );
#else
	D3DXCompileShader( _sCode, strlen(_sCode), NULL, NULL, _sFunction, _sProfile, D3DXSHADER_DEBUG | D3DXSHADER_SKIPOPTIMIZATION, &lpPSCode, &lpError, &lpPSData );
#endif

	if ( lpPixelShader )
		lpPixelShader->Release();

	pRender->lpD3DDevice->CreatePixelShader( (DWORD*)lpPSCode->GetBufferPointer(), &lpPixelShader );
}



VOID SHADER12::CompileEffect ( LPSTR _sFile, LPSTR _sTechnique, UINT _nPass )
{
	LPD3DXEFFECT lpEffect = NULL;

#ifndef DEBUG_SHADER
	D3DXCreateEffectFromFile( pRender->lpD3DDevice, _sFile, NULL, NULL, D3DXSHADER_NO_PRESHADER, NULL, &lpEffect, &lpError );
#else
	D3DXCreateEffectFromFile( pRender->lpD3DDevice, _sFile, NULL, NULL, D3DXSHADER_DEBUG | D3DXSHADER_SKIPOPTIMIZATION | D3DXSHADER_NO_PRESHADER, NULL, &lpEffect, &lpError );
#endif

	UINT nSize;
	UINT nCount;

	if ( lpVertexShader )
		lpVertexShader->Release();

	if ( lpPixelShader )
		lpPixelShader->Release();

	pRender->lpD3DDevice->SetVertexShader( NULL );
	pRender->lpD3DDevice->SetPixelShader( NULL );

	lpEffect->SetTechnique( _sTechnique );
	lpEffect->Begin( &nCount, 0 );
	lpEffect->BeginPass( _nPass );
	pRender->lpD3DDevice->GetVertexShader( &lpVertexShader );
	pRender->lpD3DDevice->GetPixelShader( &lpPixelShader );
	lpEffect->EndPass();
	lpEffect->End();

	if( lpVSCode )
		lpVSCode->Release();

	lpVertexShader->GetFunction( NULL, &nSize );
	D3DXCreateBuffer( nSize, &lpVSCode );
	lpVertexShader->GetFunction( lpVSCode->GetBufferPointer(), &nSize );

	if( lpVSData )
		lpVSData->Release();

	D3DXGetShaderConstantTable( (DWORD*)lpVSCode->GetBufferPointer(), &lpVSData );

	if( lpPSCode )
		lpPSCode->Release();

	lpPixelShader->GetFunction( NULL, &nSize );
	D3DXCreateBuffer( nSize, &lpPSCode );
	lpPixelShader->GetFunction( lpPSCode->GetBufferPointer(), &nSize );

	if( lpPSData )
		lpPSData->Release();

	D3DXGetShaderConstantTable( (DWORD*)lpPSCode->GetBufferPointer(), &lpPSData );
}
