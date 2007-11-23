
#include "shader.h"
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



LPSTR SHADER12::GetError ( )
{
	return (LPSTR)lpError->GetBufferPointer();
}



VOID SHADER12::SetVSBool ( LPSTR _sConstant, BOOL _bValue )
{
	lpVSData->SetBool( pRender->lpD3DDevice, _sConstant, _bValue );
}

VOID SHADER12::SetVSBoolArray ( LPSTR _sConstant, BOOL* _pValue, UINT _nCount )
{
	lpVSData->SetBoolArray( pRender->lpD3DDevice, _sConstant, _pValue, _nCount );
}

VOID SHADER12::SetVSInt ( LPSTR _sConstant, INT _nValue )
{
	lpVSData->SetInt( pRender->lpD3DDevice, _sConstant, _nValue );
}

VOID SHADER12::SetVSIntArray ( LPSTR _sConstant, INT* _pValue, UINT _nCount )
{
	lpVSData->SetIntArray( pRender->lpD3DDevice, _sConstant, _pValue, _nCount );
}

VOID SHADER12::SetVSFloat ( LPSTR _sConstant, FLOAT _fValue )
{
	lpVSData->SetFloat( pRender->lpD3DDevice, _sConstant, _fValue );
}

VOID SHADER12::SetVSFloatArray ( LPSTR _sConstant, FLOAT* _pValue, UINT _nCount )
{
	lpVSData->SetFloatArray( pRender->lpD3DDevice, _sConstant, _pValue, _nCount );
}

VOID SHADER12::SetVSVector ( LPSTR _sConstant, D3DXVECTOR2* _pValue ) 
{ 
	D3DXVECTOR4 pValue = D3DXVECTOR4( _pValue->x, _pValue->y, 0.0f, 1.0f );

	lpVSData->SetVector( pRender->lpD3DDevice, _sConstant, &pValue );
}

VOID SHADER12::SetVSVector ( LPSTR _sConstant, D3DXVECTOR3* _pValue ) 
{ 
	D3DXVECTOR4 pValue = D3DXVECTOR4( _pValue->x, _pValue->y, _pValue->z, 1.0f );

	lpVSData->SetVector( pRender->lpD3DDevice, _sConstant, &pValue );
}

VOID SHADER12::SetVSVector ( LPSTR _sConstant, D3DXVECTOR4* _pValue ) 
{
	lpVSData->SetVector( pRender->lpD3DDevice, _sConstant, _pValue );
}

VOID SHADER12::SetVSVectorArray ( LPSTR _sConstant, D3DXVECTOR4* _pValue, UINT _nCount )
{
	lpVSData->SetVectorArray( pRender->lpD3DDevice, _sConstant, _pValue, _nCount );
}

VOID SHADER12::SetVSMatrix ( LPSTR _sConstant, D3DXMATRIX* _pValue )
{
	lpVSData->SetMatrix( pRender->lpD3DDevice, _sConstant, _pValue );
}

VOID SHADER12::SetVSMatrixArray ( LPSTR _sConstant, D3DXMATRIX* _pValue, UINT _nCount )
{
	lpVSData->SetMatrixArray( pRender->lpD3DDevice, _sConstant, _pValue, _nCount );
}

VOID SHADER12::SetVSDefault ( )
{
	lpVSData->SetDefaults( pRender->lpD3DDevice );
}

BOOLEAN SHADER12::CheckVSConstant ( LPSTR _sConstant )
{
	// à vérifier, peut-être qu'un handle est tout de même renvoyé même si la constante n'existe pas, mais normalement on doit obtenir NULL
	return (BOOLEAN)(lpVSData->GetConstantByName( NULL, _sConstant ) != NULL);
}



VOID SHADER12::SetPSBool ( LPSTR _sConstant, BOOL _bValue )
{
	lpPSData->SetBool( pRender->lpD3DDevice, _sConstant, _bValue );
}

VOID SHADER12::SetPSBoolArray ( LPSTR _sConstant, BOOL* _pValue, UINT _nCount )
{
	lpPSData->SetBoolArray( pRender->lpD3DDevice, _sConstant, _pValue, _nCount );
}

VOID SHADER12::SetPSInt ( LPSTR _sConstant, INT _nValue )
{
	lpPSData->SetInt( pRender->lpD3DDevice, _sConstant, _nValue );
}

VOID SHADER12::SetPSIntArray ( LPSTR _sConstant, INT* _pValue, UINT _nCount )
{
	lpPSData->SetIntArray( pRender->lpD3DDevice, _sConstant, _pValue, _nCount );
}

VOID SHADER12::SetPSFloat ( LPSTR _sConstant, FLOAT _fValue )
{
	lpPSData->SetFloat( pRender->lpD3DDevice, _sConstant, _fValue );
}

VOID SHADER12::SetPSFloatArray ( LPSTR _sConstant, FLOAT* _pValue, UINT _nCount )
{
	lpPSData->SetFloatArray( pRender->lpD3DDevice, _sConstant, _pValue, _nCount );
}

VOID SHADER12::SetPSVector ( LPSTR _sConstant, D3DXVECTOR2* _pValue ) 
{ 
	D3DXVECTOR4 pValue = D3DXVECTOR4( _pValue->x, _pValue->y, 0.0f, 1.0f );

	lpPSData->SetVector( pRender->lpD3DDevice, _sConstant, &pValue );
}

VOID SHADER12::SetPSVector ( LPSTR _sConstant, D3DXVECTOR3* _pValue ) 
{ 
	D3DXVECTOR4 pValue = D3DXVECTOR4( _pValue->x, _pValue->y, _pValue->z, 1.0f );

	lpPSData->SetVector( pRender->lpD3DDevice, _sConstant, &pValue );
}

VOID SHADER12::SetPSVector ( LPSTR _sConstant, D3DXVECTOR4* _pValue ) 
{ 
	lpPSData->SetVector( pRender->lpD3DDevice, _sConstant, _pValue );
}

VOID SHADER12::SetPSVectorArray ( LPSTR _sConstant, D3DXVECTOR4* _pValue, UINT _nCount )
{
	lpPSData->SetVectorArray( pRender->lpD3DDevice, _sConstant, _pValue, _nCount );
}

VOID SHADER12::SetPSMatrix ( LPSTR _sConstant, D3DXMATRIX* _pValue )
{
	lpPSData->SetMatrix( pRender->lpD3DDevice, _sConstant, _pValue );
}

VOID SHADER12::SetPSMatrixArray ( LPSTR _sConstant, D3DXMATRIX* _pValue, UINT _nCount )
{
	lpPSData->SetMatrixArray( pRender->lpD3DDevice, _sConstant, _pValue, _nCount );
}

VOID SHADER12::SetPSTexture ( LPSTR _sConstant, LPDIRECT3DBASETEXTURE9 _pTexture )
{
	D3DXHANDLE handle;

	if( handle = lpPSData->GetConstantByName( NULL, _sConstant ) )
	{
		D3DXCONSTANT_DESC constDesc;
		UINT count;

		lpPSData->GetConstantDesc( handle, &constDesc, &count );

		if( constDesc.RegisterSet == D3DXRS_SAMPLER )
			pRender->lpD3DDevice->SetTexture( constDesc.RegisterIndex, _pTexture );
	}
}

VOID SHADER12::SetPSTexture ( LPSTR _sConstant, TEXTURE12* _pTexture )
{
	SetPSTexture( _sConstant, _pTexture->lpD3DTexture );
}

VOID SHADER12::SetPSDefault ( )
{
	lpPSData->SetDefaults( pRender->lpD3DDevice );
}

BOOLEAN SHADER12::CheckPSConstant ( LPSTR _sConstant )
{
	return (BOOLEAN)lpPSData->GetConstantByName( NULL, _sConstant );
}



VOID SHADER12::SetSetupCallback ( LPSHADERCALLBACK _lpCallback )
{
	lpSetupCallback = _lpCallback;
}

VOID SHADER12::SetSetupData ( LPVOID _lpData )
{
	lpSetupData = _lpData;
}

VOID SHADER12::Setup ( D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj )
{
	if ( lpSetupCallback )
		lpSetupCallback( pWorld, pView, pProj, lpSetupData );
}
