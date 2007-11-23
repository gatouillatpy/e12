
#pragma once



#include "util.h"

#include "entity.h"
#include "texture.h"
#include "resource.h"



typedef void ( CALLBACK *LPSHADERCALLBACK ) ( D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj, LPVOID pData ) ;



class DLL SHADER12 : public ENTITY12
{

	friend class OBJECT12;
	friend class RENDER12;
	friend class SURFACE12;
	friend class CYLINDER12;
	friend class BUFFER12;

private:

	LPSHADERCALLBACK lpSetupCallback ;
	LPVOID lpSetupData ;

	RENDER12* pRender ;

	LPDIRECT3DVERTEXSHADER9 lpVertexShader ;
	LPDIRECT3DPIXELSHADER9 lpPixelShader ;

	LPD3DXBUFFER lpError ;

	LPD3DXBUFFER lpVSCode ;
	LPD3DXBUFFER lpPSCode ;

	LPD3DXCONSTANTTABLE lpVSData ;
	LPD3DXCONSTANTTABLE lpPSData ;

public:

	SHADER12 ( RENDER12* _pRender ) ;
	virtual ~SHADER12 ( ) ;

	/* à faire */
	VOID Copy ( SHADER12* _pDestination ) ;
	SHADER12* Copy ( ) ;

	LPSTR GetError ( ) ;

	VOID CompileEffect ( LPSTR _sFile, LPSTR _sTechnique, UINT _nPass ) ;
	VOID CompileVSFile ( LPSTR _sFile, LPSTR _sProfile, LPSTR _sFunction ) ;
	VOID CompilePSFile ( LPSTR _sFile, LPSTR _sProfile, LPSTR _sFunction ) ;
	VOID CompileVSCode ( LPSTR _sCode, LPSTR _sProfile, LPSTR _sFunction ) ;
	VOID CompilePSCode ( LPSTR _sCode, LPSTR _sProfile, LPSTR _sFunction ) ;
	VOID AssembleVSFile ( LPSTR _sFile ) ;
	VOID AssemblePSFile ( LPSTR _sFile ) ;
	VOID AssembleVSCode ( LPSTR _sCode ) ;
	VOID AssemblePSCode ( LPSTR _sCode ) ;

	BOOLEAN CheckVSConstant ( LPSTR _sConstant ) ;
	VOID SetVSBool ( LPSTR _sConstant, BOOL _bValue ) ;
	VOID SetVSBoolArray ( LPSTR _sConstant, BOOL* _pValue, UINT _nCount ) ;
	VOID SetVSInt ( LPSTR _sConstant, INT _nValue ) ;
	VOID SetVSIntArray ( LPSTR _sConstant, INT* _pValue, UINT _nCount ) ;
	VOID SetVSFloat ( LPSTR _sConstant, FLOAT _fValue ) ;
	VOID SetVSFloatArray ( LPSTR _sConstant, FLOAT* _pValue, UINT _nCount ) ;
	VOID SetVSVector ( LPSTR _sConstant, D3DXVECTOR2* _pValue ) ;
	VOID SetVSVector ( LPSTR _sConstant, D3DXVECTOR3* _pValue ) ;
	VOID SetVSVector ( LPSTR _sConstant, D3DXVECTOR4* _pValue ) ;
	VOID SetVSVectorArray ( LPSTR _sConstant, D3DXVECTOR4* _pValue, UINT _nCount ) ;
	VOID SetVSMatrix ( LPSTR _sConstant, D3DXMATRIX* _pValue ) ;
	VOID SetVSMatrixArray ( LPSTR _sConstant, D3DXMATRIX* _pValue, UINT _nCount ) ;
	VOID SetVSDefault ( ) ;

	BOOLEAN CheckPSConstant ( LPSTR _sConstant ) ;
	VOID SetPSBool ( LPSTR _sConstant, BOOL _bValue ) ;
	VOID SetPSBoolArray ( LPSTR _sConstant, BOOL* _pValue, UINT _nCount ) ;
	VOID SetPSInt ( LPSTR _sConstant, INT _nValue ) ;
	VOID SetPSIntArray ( LPSTR _sConstant, INT* _pValue, UINT _nCount ) ;
	VOID SetPSFloat ( LPSTR _sConstant, FLOAT _fValue ) ;
	VOID SetPSFloatArray ( LPSTR _sConstant, FLOAT* _pValue, UINT _nCount ) ;
	VOID SetPSVector ( LPSTR _sConstant, D3DXVECTOR2* _pValue ) ;
	VOID SetPSVector ( LPSTR _sConstant, D3DXVECTOR3* _pValue ) ;
	VOID SetPSVector ( LPSTR _sConstant, D3DXVECTOR4* _pValue ) ;
	VOID SetPSVectorArray ( LPSTR _sConstant, D3DXVECTOR4* _pValue, UINT _nCount ) ;
	VOID SetPSMatrix ( LPSTR _sConstant, D3DXMATRIX* _pValue ) ;
	VOID SetPSMatrixArray ( LPSTR _sConstant, D3DXMATRIX* _pValue, UINT _nCount ) ;
	VOID SetPSTexture ( LPSTR _sConstant, LPDIRECT3DBASETEXTURE9 _pTexture ) ;
	VOID SetPSTexture ( LPSTR _sConstant, TEXTURE12* _pTexture ) ;
	VOID SetPSDefault ( ) ;

	/* A la différence de Load et Save, QuickLoad et QuickSave font appel au registre de ressources partagées */
	/* afin de vérifier que le fichier à charger n'est pas déjà en mémoire...                                 */
	/* Les ressources partagées par la classe SHADER12 sont :                                                 */
	/* - le code compilé et la table d'indexation des constantes du vertex shader et du pixel shader          */
	/* => Attention donc de ne pas modifier ces ressources sans quoi elles le seront pour toutes les entités  */
	/* ayant chargé un même fichier.                                                                          */
	BOOLEAN QuickLoad ( LPSTR _sFile ) ;
	BOOLEAN QuickSave ( LPSTR _sFile ) ;

	BOOLEAN Load ( LPSTR _sFile ) ;
	BOOLEAN Save ( LPSTR _sFile ) ;

	VOID SetSetupCallback ( LPSHADERCALLBACK _lpCallback ) ;
	VOID SetSetupData ( LPVOID _lpData ) ;

	VOID Setup ( D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj ) ;

	virtual VOID ProcessCommand ( LPSTR sCommand ) ;
	virtual VOID ProcessHelp ( ) ;

};