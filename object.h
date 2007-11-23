
#pragma once

#include "geometry.h"
#include "texture.h"
#include "hitbox.h"
#include "shader.h"

#include "util.h"



struct STAGESTATE12 ;



class DLL OBJECT12 : public ENTITY12
{

	friend class RENDER12;
	friend class SCENE12;
	friend class CAMERA12;

protected:

	RENDER12* pRender ;

	BOOLEAN bComplex;

	INDEXER12* iChild ;

	SCENE12* pScene ;
	OBJECT12* pParent ;

	INDEXER12* iTexture ; 

	LPDIRECT3DTEXTURE9 pLightMap ;
	LPDIRECT3DCUBETEXTURE9 pCubeMap ;

	D3DXVECTOR3 vCenter ;
	D3DXVECTOR3 vAngle ;
	D3DXVECTOR3 vSize ;

	HITBOX12* pHitbox ;

	SHADER12* pShader ;
	
	D3DXMATRIX matCenter ;
	D3DXMATRIX matAngle ;
	D3DXMATRIX matSize ;
	D3DXMATRIX matObject ;
	
	GEOMETRY12* pGeometry ;
	DWORD dwFaceStart ;
	DWORD dwFaceCount ;

	BOOLEAN bHitbox ; // vrai si la hitbox est à jour, faux sinon
	BOOLEAN bMatrix ; // vrai si la matrice est à jour, faux sinon

	DWORD dwPass ;

	DWORD dwFrameCounter ;
	DWORD dwTotalCounter ;

	BOOLEAN bVisible ;

	BOOLEAN bWireframe ;
	BOOLEAN bLighting ;

	STAGESTATE12* pStageState ;

	DWORD dwPhase ;

	D3DMATERIAL9* pMaterial ;

	VOID SetupTextureStandard ( ) ;
	VOID RenderWired ( CAMERA12* _pCamera ) ;
	VOID RenderSolid ( CAMERA12* _pCamera ) ;

	VOID Copy ( OBJECT12* pObject, BOOLEAN bCopyGeometry, BOOLEAN bCopyTexture ) ;

public:

	OBJECT12 ( RENDER12* _pRender ) ;
	virtual ~OBJECT12 ( ) ;

	virtual OBJECT12* Copy ( BOOLEAN bCopyGeometry = FALSE, BOOLEAN bCopyTexture = FALSE ) ;

	DWORD GetFrameCounter ( ) ;
	DWORD GetTotalCounter ( ) ;
	VOID IncTotalCounter ( ) ;
	VOID IncFrameCounter ( ) ;
	VOID SetTotalCounter ( ) ;
	VOID SetFrameCounter ( ) ;

	BOOLEAN IsObject ( ) ;
	BOOLEAN IsComplex ( ) ;

	VOID Show ( ) ;
	VOID Hide ( ) ;

	VOID Pass ( DWORD _dwPass ) ;

	VOID SetGeometry ( GEOMETRY12* _pGeometry ) ;
	GEOMETRY12* GetGeometry ( ) ;

	VOID SetMaterial ( D3DMATERIAL9* _pMaterial ) ;
	D3DMATERIAL9* Material ( ) ;

	VOID SetShader ( SHADER12* _pShader ) ;
	SHADER12* GetShader ( ) ;

	VOID Move ( FLOAT _x, FLOAT _y, FLOAT _z ) ;
	VOID Rotate ( FLOAT _x, FLOAT _y, FLOAT _z ) ;
	VOID Grow ( FLOAT _x, FLOAT _y, FLOAT _z ) ;
	VOID Shrink ( FLOAT _x, FLOAT _y, FLOAT _z ) ;

	VOID SetCenter ( FLOAT _x, FLOAT _y, FLOAT _z ) ;
	VOID SetCenter ( D3DXVECTOR3 & _vCenter ) ;
	D3DXVECTOR3 GetCenter ( ) ;

	VOID SetAngle ( FLOAT _x, FLOAT _y, FLOAT _z ) ;
	VOID SetAngle ( D3DXVECTOR3 & _vAngle ) ;
	D3DXVECTOR3 GetAngle ( ) ;

	VOID SetSize ( FLOAT _x, FLOAT _y, FLOAT _z ) ;
	VOID SetSize ( D3DXVECTOR3 & _vSize ) ;
	D3DXVECTOR3 GetSize ( ) ;

	D3DXVECTOR3 AbsoluteCenter ( ) ;

	FLOAT width ( ) ;
	FLOAT height ( ) ;
	FLOAT length ( ) ;

	FLOAT pitch ( ) ;
	FLOAT yaw ( ) ;
	FLOAT roll ( ) ;

	FLOAT x ( ) ;
	FLOAT y ( ) ;
	FLOAT z ( ) ;

	virtual VOID SetScene ( SCENE12* _pScene ) ;
	SCENE12* GetScene ( ) ;

	VOID AddChild ( OBJECT12* _pChild ) ;
	VOID DelChild ( OBJECT12* _pChild ) ;

	INDEXER12* ChildIndexer ( ) ;

	VOID SetParent ( OBJECT12* _pParent ) ;
	OBJECT12* GetParent ( ) ;

	VOID SetPhase ( DWORD _dwPhase ) ;
	DWORD GetPhase ( ) ;

	VOID EnableWireframe ( ) ;
	VOID DisableWireframe ( ) ;

	VOID EnableLighting ( ) ;
	VOID DisableLighting ( ) ;

	STAGESTATE12* GetStageState ( ) ;
	VOID SetStageState ( DWORD _dwStage, STAGESTATE12* _pStageState ) ;

	VOID AddTexture ( TEXTURE12* _pTexture ) ;
	VOID DelTexture ( TEXTURE12* _pTexture ) ;

	virtual BOOLEAN	Intersect ( D3DXVECTOR3 & _vRayPos, D3DXVECTOR3 & _vRayDir ) ;

	VOID UpdateHitbox ( ) ;
	HITBOX12* Hitbox ( ) ;
	
	VOID UpdateMatrix ( ) ;
	D3DXMATRIX Matrix ( ) ;

	virtual VOID Update ( ) ;
	virtual VOID Render ( CAMERA12* _pCamera ) ;
	virtual VOID Render ( CAMERA12* _pCamera, DWORD _dwPass ) ;
	VOID Draft ( CAMERA12* _pCamera, DWORD _dwPass ) ;

	VOID Reset ( ) { dwPass = RANDOM; } ;

	virtual VOID ProcessCommand ( LPSTR sCommand ) ;
	virtual VOID ProcessHelp ( ) ;

	virtual BOOLEAN Load ( LPSTR _sFile ) ;
	virtual BOOLEAN Save ( LPSTR _sFile ) ;

};