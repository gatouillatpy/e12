
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



DWORD OBJECT12::GetFrameCounter ( )
{
	return dwFrameCounter;
}

DWORD OBJECT12::GetTotalCounter ( )
{
	return dwTotalCounter;
}

VOID OBJECT12::IncTotalCounter ( )
{
	dwTotalCounter += dwFrameCounter;
}

VOID OBJECT12::IncFrameCounter ( )
{
	dwFrameCounter++;
}

VOID OBJECT12::SetTotalCounter ( )
{
	dwTotalCounter = 0;
}

VOID OBJECT12::SetFrameCounter ( )
{
	dwFrameCounter = 0;
}



BOOLEAN OBJECT12::IsComplex ( )
{
	return bComplex;
}

BOOLEAN OBJECT12::IsObject ( )
{
	return !bComplex;
}



VOID OBJECT12::Show ( )
{
	bVisible = TRUE;
}

VOID OBJECT12::Hide ( )
{
	bVisible = FALSE;
}



VOID OBJECT12::Pass ( DWORD _dwPass )
{
	dwPass = _dwPass;
}



VOID OBJECT12::SetGeometry ( GEOMETRY12* _pGeometry )
{
	pGeometry = _pGeometry;
}

GEOMETRY12* OBJECT12::GetGeometry ( )
{
	return pGeometry;
}



VOID OBJECT12::SetShader ( SHADER12* _pShader )
{
	pShader = _pShader;
}

SHADER12* OBJECT12::GetShader ( )
{
	return pShader;
}



VOID OBJECT12::SetMaterial ( D3DMATERIAL9* _pMaterial )
{
	pMaterial = _pMaterial;
}

D3DMATERIAL9* OBJECT12::Material ( )
{
	return pMaterial;
}



VOID OBJECT12::SetCenter ( FLOAT _x, FLOAT _y, FLOAT _z )
{
	vCenter = D3DXVECTOR3(_x, _y, _z);

	bMatrix = FALSE;
	bHitbox = FALSE;
}

VOID OBJECT12::SetCenter ( D3DXVECTOR3 & _vCenter )
{
	vCenter = _vCenter;

	bMatrix = FALSE;
	bHitbox = FALSE;
}

D3DXVECTOR3 OBJECT12::GetCenter ( )
{
	return vCenter;
}



VOID OBJECT12::SetAngle ( FLOAT _x, FLOAT _y, FLOAT _z )
{
	vAngle = D3DXVECTOR3(_x, _y, _z);

	bMatrix = FALSE;
	bHitbox = FALSE;
}

VOID OBJECT12::SetAngle ( D3DXVECTOR3 & _vAngle )
{
	vAngle = _vAngle;

	bMatrix = FALSE;
	bHitbox = FALSE;
}

D3DXVECTOR3 OBJECT12::GetAngle ( )
{
	return vAngle;
}



VOID OBJECT12::SetSize ( FLOAT _x, FLOAT _y, FLOAT _z )
{
	vSize = D3DXVECTOR3(_x, _y, _z);

	bMatrix = FALSE;
	bHitbox = FALSE;
}

VOID OBJECT12::SetSize ( D3DXVECTOR3 & _vSize )
{
	vSize = _vSize;

	bMatrix = FALSE;
	bHitbox = FALSE;
}

D3DXVECTOR3 OBJECT12::GetSize ( )
{
	return vSize;
}



VOID OBJECT12::Move ( FLOAT _x, FLOAT _y, FLOAT _z )
{
	vCenter.x += _x;
	vCenter.y += _y;
	vCenter.z += _z;

	bMatrix = FALSE;
	bHitbox = FALSE;
}

VOID OBJECT12::Rotate ( FLOAT _x, FLOAT _y, FLOAT _z )
{
	vAngle.x += _x;
	vAngle.y += _y;
	vAngle.z += _z;

	bMatrix = FALSE;
	bHitbox = FALSE;
}

VOID OBJECT12::Grow ( FLOAT _x, FLOAT _y, FLOAT _z )
{
	vSize.x *= _x;
	vSize.y *= _y;
	vSize.z *= _z;

	bMatrix = FALSE;
	bHitbox = FALSE;
}

VOID OBJECT12::Shrink ( FLOAT _x, FLOAT _y, FLOAT _z )
{
	if ( _x != 0.0f ) vSize.x /= _x;
	if ( _y != 0.0f ) vSize.y /= _y;
	if ( _z != 0.0f ) vSize.z /= _z;

	bMatrix = FALSE;
	bHitbox = FALSE;
}



FLOAT OBJECT12::width ( )
{ 
	return vSize.x;
}

FLOAT OBJECT12::height ( )
{
	return vSize.y;
}

FLOAT OBJECT12::length ( )
{
	return vSize.z;
}

FLOAT OBJECT12::pitch ( )
{
	return vAngle.x;
}

FLOAT OBJECT12::yaw ( )
{
	return vAngle.y;
}

FLOAT OBJECT12::roll ( )
{
	return vAngle.z;
}

FLOAT OBJECT12::x ( )
{
	return vCenter.x;
}

FLOAT OBJECT12::y ( )
{
	return vCenter.y;
}

FLOAT OBJECT12::z ( )
{
	return vCenter.z;
}



VOID OBJECT12::EnableWireframe ( )
{
	bWireframe = TRUE;
}

VOID OBJECT12::DisableWireframe ( )
{
	bWireframe = FALSE;
}



VOID OBJECT12::EnableLighting ( )
{
	bLighting = TRUE;
}

VOID OBJECT12::DisableLighting ( )
{
	bLighting = FALSE;
}



D3DXVECTOR3 OBJECT12::AbsoluteCenter ( )
{
	D3DXMATRIX matWorld = Matrix() * pScene->Matrix();

	return D3DXVECTOR3( matWorld._41, matWorld._42, matWorld._43 );
}



VOID OBJECT12::SetPhase ( DWORD _dwPhase )
{
	if ( _dwPhase + 1 > pRender->dwPhaseCount )
		pRender->SetPhaseCount( _dwPhase + 1 );

	dwPhase = _dwPhase;
}

DWORD OBJECT12::GetPhase ( )
{
	return dwPhase;
}



STAGESTATE12* OBJECT12::GetStageState ( )
{
	return pStageState;
}

VOID OBJECT12::SetStageState ( DWORD _dwStage, STAGESTATE12* _pStageState )
{
	pStageState = _pStageState;
}