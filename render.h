
#pragma once

#include "render_blend.h"
#include "render_filter.h"
#include "render_stage.h"

#include "window.h"

#include "geometry.h"
#include "texture.h"
#include "volume.h"
#include "animation.h"
#include "shader.h"
#include "font.h"
#include "buffer.h"

#include "hitbox.h"
#include "camera.h"
#include "object.h"
#include "cylinder.h"
#include "box.h"
#include "grid.h"
#include "mesh.h"
#include "surface.h"
#include "complex.h"
#include "sprite.h"

#include "scene.h"

#include "control.h"
#include "button.h"
#include "cursor.h"
#include "image.h"
#include "label.h"
#include "alabel.h"
#include "frame.h"
#include "textbox.h"
#include "cmdbox.h"

#include "interface.h"
#include "console.h"

#include "util.h"



#define TEXTURE_PHASE(n) (0xC0000000 + n)



CONST DWORD D3DCULLMODE_DEFAULT = D3DCULL_CW ;
CONST DWORD D3DLIGHTING_DEFAULT = FALSE ;
CONST DWORD D3DFILLMODE_DEFAULT = D3DFILL_SOLID ;
CONST DWORD D3DZFUNC_DEFAULT = D3DCMP_LESSEQUAL ;



const short DRAFT_NONE = 0; // ne pas faire de prérendu
const short DRAFT_BACK = 1; // donne la priorité d'affichage aux objets situés en arrière plan
const short DRAFT_FRONT = 2; // donne la priorité d'affichage aux objets situés au premier plan
const short DRAFT_CW = 4; // donne la priorité d'affichage aux objets pleins
const short DRAFT_CCW = 8; // donne la priorité d'affichage aux objets vides
const short DRAFT_FULL = 16; // faire un prérendu complet

/*************************************************************************************************************************/
/* Remarques générales concernant le prérendu :                                                                          */
/*  - cette méthode utilise les occlusion queries des gpu compatibles                                                    */
/*  - la logique veut que la priorité soit donnée à l'affichage des objets pleins situés au premier plan                 */
/*  - donner la priorité aux objets de l'arrière plan permettra d'éviter à de volumineux objets aux formes éfilées       */
/*    situés au premier plan d'occulter l'affichage                                                                      */
/*  - donner la priorité d'affichage aux objets vides permet lorsqu'on est à l'intérieur d'un objet troué de ne pouvoir  */
/*    voir au travers des trous                                                                                          */
/*  - faire un prérendu complet est plus efficace que de faire un prérendu avec l'ensemble des priorités                 */
/*  - le prérendu n'est pas toujours nécessaire, cela dépend de la complexité des scènes à afficher, forcer le rendu     */
/*    complet d'une scène simple est souvent plus performant que de passer par un prérendu                               */
/*************************************************************************************************************************/

class DLL RENDER12 : public ENTITY12
{

	friend class ENGINE12;

	friend class TEXTURE12;
	friend class VOLUME12;
	friend class ANIMATION12;
	friend class BUFFER12;
	friend class SHADER12;
	friend class FONT12;
	friend class CAMERA12;
	friend class GEOMETRY12;
	friend class HITBOX12;

	friend class SCENE12;
	friend class OBJECT12;
	friend class MESH12;
	friend class CYLINDER12;
	friend class SURFACE12;
	friend class SPRITE12;

	friend class INTERFACE12;
	friend class CONTROL12;
	friend class IMAGE12;
	friend class LABEL12;
	friend class CURSOR12;
	friend class BUTTON12;
	friend class TEXTBOX12;
	friend class CMDBOX12;
	friend class CONTROL12_EFFECT;

	friend DLL VOID UseCylinder ( RENDER12* pRender ) ;
	friend DLL VOID UseSurface ( RENDER12* pRender ) ;
	friend DLL VOID UseSprite ( RENDER12* pRender ) ;

	struct VERTEX {	FLOAT x, y, z; };
	struct LVERTEX { FLOAT x, y, z;	DWORD color; };
	struct TVERTEX { FLOAT x, y, z;	FLOAT tu, tv; };
	struct TLVERTEX { FLOAT x, y, z; DWORD color; FLOAT tu, tv; };

private:

	DWORD dwBackColor ; // couleur de l'arrière plan

	BOOLEAN bWindowMode ; // vrai pour le mode fenêtre, faux pour le mode plein écran
	SHORT nScreenWidth ; // résolution horizontale du rendu final
	SHORT nScreenHeight ; // résolution verticale du rendu final
	BOOLEAN bVSync ; // vrai pour activer la synchronisation verticale
	BOOLEAN bHardware ; // vrai pour faire les rendus à l'aide de la carte graphique
	SHORT nDraftWidth ; // résolution horizontale du prérendu
	SHORT nDraftHeight ; // résolution verticale du prérendu
	DWORD dwDraftFlags ; // configuration du prérendu
	BOOLEAN bShowDraft ; // vrai pour afficher en transparence le prérendu
	UINT nMaxCubemapMemory ; // quantité maximum de mémoire vidéo dédiée aux cubemaps (en mo)
	UINT nMaxCubemapResolution ; // résolution maximum des cubemaps
	UINT nMinCubemapResolution ; // résolution minimum des cubemaps
	UINT nMaxLightmapMemory ; // quantité maximum de mémoire vidéo dédiée aux lightmaps (en mo)
	UINT nMaxLightmapResolution ; // résolution maximum des lightmaps
	UINT nMinLightmapResolution ; // résolution minimum des lightmaps
	LPSTR sShaderPath ; // chemin d'accès aux shaders

	SHADER12* lpCylinderShader ;
	SHADER12* lpSurfaceShader ;
	SHADER12* lpFinalShader ;

	WINDOW12* lpWindow ;

	INDEXER12* iCamera ;
	INDEXER12* iControl ;
	INDEXER12* iInterface ;
	INDEXER12* iObject ;
	INDEXER12* iScene ;
	INDEXER12* iGeometry ;
	INDEXER12* iHitbox ;
	INDEXER12* iTexture ;
	INDEXER12* iFont ;
	INDEXER12* iShader ;

	INDEXER12* iAnimation ;

	SHORT nWidth ;
	SHORT nHeight ;

	LPDIRECT3D9 lpD3D ;
	LPDIRECT3DDEVICE9 lpD3DDevice ;

	LPDIRECT3DVERTEXBUFFER9 lpSpriteVB ;

	LPDIRECT3DQUERY9 lpDraftQuery ;
	LPDIRECT3DTEXTURE9 lpDraftTexture ;
	LPDIRECT3DSURFACE9 lpDraftBuffer ;
	LPDIRECT3DSURFACE9 lpDraftSurface ;

	VOID Draft ( CAMERA12* _pCamera, DWORD & dwPass ) ;

	LPDIRECT3DSURFACE9 lpBackBuffer ;
	LPDIRECT3DSURFACE9 lpDepthBuffer ;

	LPDIRECT3DTEXTURE9 lpComplexTexture ;
	LPDIRECT3DSURFACE9 lpComplexColor ;
	LPDIRECT3DSURFACE9 lpComplexDepth ;

	LPDIRECT3DTEXTURE9 lpRenderTexture ;
	LPDIRECT3DSURFACE9 lpRenderBuffer ;
	LPDIRECT3DSURFACE9 lpRenderSurface ;

	LPDIRECT3DTEXTURE9 lpRayTexture ;
	LPDIRECT3DSURFACE9 lpRayBuffer ;

	LPDIRECT3DTEXTURE9 lpSpaceTexture ;
	LPDIRECT3DSURFACE9 lpSpaceBuffer ;

	LPDIRECT3DTEXTURE9 lpLightTexture ;
	LPDIRECT3DSURFACE9 lpLightBuffer ;

	DWORD dwCubemapCount ; // nombre de textures allouées pour les cubemaps
	LPDIRECT3DCUBETEXTURE9* ppCubemapTexture ; // tableau des textures allouées pour les cubemaps

	DWORD dwLightmapCount ; // nombre de textures allouées pour les lightmaps
	LPDIRECT3DTEXTURE9* ppLightmapTexture ; // tableau des textures allouées pour les lightmaps

	LPDIRECT3DPIXELSHADER9 lpRayPS ;
	LPDIRECT3DVERTEXSHADER9 lpRayVS ;
	LPDIRECT3DVERTEXDECLARATION9 lpRayVD ;
	LPDIRECT3DVERTEXBUFFER9 lpRayVB ;
	LPDIRECT3DINDEXBUFFER9 lpRayIB ;

	LPDIRECT3DPIXELSHADER9 lpHitboxPS ;
	LPDIRECT3DVERTEXSHADER9 lpHitboxVS ;
	LPDIRECT3DVERTEXDECLARATION9 lpHitboxVD ;
	LPDIRECT3DVERTEXBUFFER9 lpHitboxVB ;
	LPDIRECT3DINDEXBUFFER9 lpHitboxIB ;

	VOID DrawHitbox ( HITBOX12* _pHitbox, CAMERA12* _pCamera ) ;
	VOID DrawHitbox ( HITBOX12* _pHitbox, CAMERA12* _pCamera, SCENE12* _pScene ) ;

	LPDIRECT3DPIXELSHADER9 lpBufferPS ;
	LPDIRECT3DVERTEXSHADER9 lpBufferVS ;
	LPDIRECT3DVERTEXDECLARATION9 lpBufferVD ;
	LPDIRECT3DVERTEXBUFFER9 lpBufferVB ;
	LPDIRECT3DINDEXBUFFER9 lpBufferIB ;

	VOID DrawBuffer ( LPDIRECT3DTEXTURE9 _lpTexture ) ;

	D3DMATERIAL9* pMaterial ;

	BLENDSTATE12* pBlendState ;

	FILTERSTATE12* pFilterState ;

	STAGESTATE12* pStageState ;

	DWORD dwPhaseCount ;
	DWORD dwPhase ;

	BUFFER12** ppPhaseBuffer ;

	SHADER12* pColorShader ;
	SHADER12* pTextureShader ;
	SHADER12* pMaskShader ;
	SHADER12* pCharShader ;

	CONTROL12* pFocus ;

	BOOLEAN bWireframe ;

	BOOLEAN InitDirect3D( WINDOW12* _pWindow ) ;
	BOOLEAN InitComplex() ;
	BOOLEAN InitRender() ;
	BOOLEAN InitDraftSystem() ;
	BOOLEAN InitHitbox() ;
	BOOLEAN InitBuffer() ;
	BOOLEAN InitRay() ;
	BOOLEAN InitLightmap() ;
	BOOLEAN InitCubemap() ;

	// TEMPORAIRE : ce sont les viewports qui ont des caméras
	CAMERA12* lpCamera ;

public:

	// TEMPORAIRE : ce sont les viewports qui ont des caméras
	VOID SetCamera( CAMERA12* c )
	{
		lpCamera = c;
	}

	RENDER12 ( ENGINE12* _pEngine ) ;
	virtual ~RENDER12 ( ) ;

	BOOLEAN Initialize ( WINDOW12* _lpWindow ) ;
	VOID Terminate ( ) ;

	VOID WriteSettings ( LPSTR _sSection, LPSTR _sFile ) ;
	VOID ReadSettings ( LPSTR _sSection, LPSTR _sFile ) ;

	DWORD GetBackColor ( ) { return dwBackColor; } ;
	VOID SetBackColor ( DWORD _dwBackColor ) { dwBackColor = _dwBackColor; } ;
	VOID SetBackColor ( FLOAT _r, FLOAT _g, FLOAT _b, FLOAT _a ) { dwBackColor = D3DCOLOR_COLORVALUE(_r, _g, _b, _a); } ;

	VOID SetPhaseCount ( DWORD _dwPhaseCount ) ;
	DWORD GetPhaseCount ( ) ;

	SHORT GetWidth ( ) { return nWidth; } ;
	SHORT GetHeight ( ) { return nHeight; } ;

	VOID SetFocus ( CONTROL12* _pControl ) ;
	CONTROL12* GetFocus ( ) ;

	VOID EnableWireframe ( ) ;
	VOID DisableWireframe ( ) ;

	VOID Update ( ) ;

	VOID RayProjection ( CAMERA12* _pCamera ) ;

	VOID PickPoint ( FLOAT _fX, FLOAT _fY, SCENE12* & _pScene, OBJECT12* & _pObject, VERTEX* & _pVertex, FACE* & _pFace ) ;
	VOID PickRegion ( FLOAT _fX, FLOAT _fY, FLOAT _fW, FLOAT _fH, SCENE12** & _pScene, OBJECT12** & _pObject, VERTEX** & _pVertex, FACE** & _pFace ) ;

	CAMERA12* AddCamera ( ) ;
	VOID DelCamera ( CAMERA12* _pCamera ) ;
	CAMERA12* GetCamera ( DWORD _dwIndex ) ;
	CAMERA12* GetCamera ( LPSTR _sName ) ;

	FRAME12* AddFrame ( ) ;
	TEXTBOX12* AddTextbox ( ) ;
	CMDBOX12* AddCmdbox ( ) ;
	BUTTON12* AddButton ( ) ;
	CURSOR12* AddCursor ( ) ;
	IMAGE12* AddImage ( ) ;
	LABEL12* AddLabel ( ) ;
	ALABEL12* AddALabel ( ) ;
	CONTROL12* AddControl ( ) ;
	VOID DelControl ( CONTROL12* _pControl ) ;
	CONTROL12* GetControl ( DWORD _dwIndex ) ;
	CONTROL12* GetControl ( LPSTR _sName ) ;

	CONSOLE12* AddConsole ( UINT _nLineCount ) ;
	INTERFACE12* AddInterface ( ) ;
	VOID DelInterface ( INTERFACE12* _pInterface ) ;
	INTERFACE12* GetInterface ( DWORD _dwIndex ) ;
	INTERFACE12* GetInterface ( LPSTR _sName ) ;

	BOX12* AddBox ( ) ;
	COMPLEX12* AddComplex ( ) ;
	CYLINDER12* AddCylinder ( ) ;
	GRID12* AddGrid ( ) ;
	MESH12* AddMesh ( ) ;
	SPRITE12* AddSprite ( ) ;
	SURFACE12* AddSurface ( ) ;
	OBJECT12* AddObject ( ) ;
	VOID DelObject ( OBJECT12* _pObject ) ;
	OBJECT12* GetObject ( DWORD _dwIndex ) ;
	OBJECT12* GetObject ( LPSTR _sName ) ;

	SCENE12* AddScene ( ) ;
	VOID DelScene ( SCENE12* _pScene ) ;
	SCENE12* GetScene ( DWORD _dwIndex ) ;
	SCENE12* GetScene ( LPSTR _sName ) ;

	GEOMETRY12* AddGeometry ( ) ;
	VOID DelGeometry ( GEOMETRY12* _pGeometry ) ;
	GEOMETRY12* GetGeometry ( DWORD _dwIndex ) ;
	GEOMETRY12* GetGeometry ( LPSTR _sName ) ;

	HITBOX12* AddHitbox ( ENTITY12* _pOwner ) ;
	VOID DelHitbox ( HITBOX12* _pHitbox ) ;
	HITBOX12* GetHitbox ( DWORD _dwIndex ) ;
	HITBOX12* GetHitbox ( LPSTR _sName ) ;

	ANIMATION12* AddAnimation ( ) ;
	VOLUME12* AddVolume ( ) ;
	TEXTURE12* AddTexture ( ) ;
	VOID DelTexture ( TEXTURE12* _pTexture ) ;
	TEXTURE12* GetTexture ( DWORD _dwIndex ) ;
	TEXTURE12* GetTexture ( LPSTR _sName ) ;

	FONT12* AddFont ( ) ;
	VOID DelFont ( FONT12* _pFont ) ;
	FONT12* GetFont ( DWORD _dwIndex ) ;
	FONT12* GetFont ( LPSTR _sName ) ;

	SHADER12* AddShader ( ) ;
	VOID DelShader ( SHADER12* _pShader ) ;
	SHADER12* GetShader ( DWORD _dwIndex ) ;
	SHADER12* GetShader ( LPSTR _sName ) ;

	VOID DrawChar ( D3DXVECTOR2 & _vOffset, D3DXVECTOR2 & _vScale, D3DXVECTOR2 & _vMin, D3DXVECTOR2 & _vMax, FONT12* _pFont, D3DXVECTOR4 & _vMaskColor, D3DXVECTOR4 & _vTestColor, UCHAR _c ) ;

	VOID DrawTexture ( D3DXVECTOR2 & _vPA, D3DXVECTOR2 & _vPB, D3DXVECTOR2 & _vTA, D3DXVECTOR2 & _vTB, D3DXVECTOR2 & _vMin, D3DXVECTOR2 & _vMax, TEXTURE12* _pTexture, D3DXVECTOR4 & _vMaskColor, D3DXVECTOR4 & _vTestColor ) ;

	VOID DrawCircle ( D3DXVECTOR2 & _vPC, FLOAT _fRadius, D3DXVECTOR4 & _vColor ) ;
	VOID DrawCircle ( D3DXVECTOR2 & _vPC, FLOAT _fRadius, DWORD _dwColor ) ;
	VOID DrawCircle ( D3DXVECTOR2 & _vPC, FLOAT _fRadius, FLOAT _r, FLOAT _g, FLOAT _b, FLOAT _a ) ;
	VOID DrawCircle ( SHORT _nxC, SHORT _nyC, SHORT _nRadius, D3DXVECTOR4 & _vColor ) ;
	VOID DrawCircle ( SHORT _nxC, SHORT _nyC, SHORT _nRadius, DWORD _dwColor ) ;
	VOID DrawCircle ( SHORT _nxC, SHORT _nyC, SHORT _nRadius, FLOAT _r, FLOAT _g, FLOAT _b, FLOAT _a ) ;
	VOID DrawCircle ( FLOAT _xC, FLOAT _yC, FLOAT _fRadius, D3DXVECTOR4 & _vColor ) ;
	VOID DrawCircle ( FLOAT _xC, FLOAT _yC, FLOAT _fRadius, DWORD _dwColor ) ;
	VOID DrawCircle ( FLOAT _xC, FLOAT _yC, FLOAT _fRadius, FLOAT _r, FLOAT _g, FLOAT _b, FLOAT _a ) ;

	VOID DrawArea ( D3DXVECTOR2 & _vPA, D3DXVECTOR2 & _vPB, D3DXVECTOR4 & _vColor ) ;
	VOID DrawArea ( D3DXVECTOR2 & _vPA, D3DXVECTOR2 & _vPB, DWORD _dwColor ) ;
	VOID DrawArea ( D3DXVECTOR2 & _vPA, D3DXVECTOR2 & _vPB, FLOAT _r, FLOAT _g, FLOAT _b, FLOAT _a ) ;
	VOID DrawArea ( SHORT _nxA, SHORT _nyA, SHORT _nxB, SHORT _nyB, D3DXVECTOR4 & _vColor ) ;
	VOID DrawArea ( SHORT _nxA, SHORT _nyA, SHORT _nxB, SHORT _nyB, DWORD _dwColor ) ;
	VOID DrawArea ( SHORT _nxA, SHORT _nyA, SHORT _nxB, SHORT _nyB, FLOAT _r, FLOAT _g, FLOAT _b, FLOAT _a ) ;
	VOID DrawArea ( FLOAT _xA, FLOAT _yA, FLOAT _xB, FLOAT _yB, D3DXVECTOR4 & _vColor ) ;
	VOID DrawArea ( FLOAT _xA, FLOAT _yA, FLOAT _xB, FLOAT _yB, DWORD _dwColor ) ;
	VOID DrawArea ( FLOAT _xA, FLOAT _yA, FLOAT _xB, FLOAT _yB, FLOAT _r, FLOAT _g, FLOAT _b, FLOAT _a ) ;

	VOID DrawRect ( D3DXVECTOR2 & _vPA, D3DXVECTOR2 & _vPB, D3DXVECTOR4 & _vColor ) ;
	VOID DrawRect ( D3DXVECTOR2 & _vPA, D3DXVECTOR2 & _vPB, DWORD _dwColor ) ;
	VOID DrawRect ( D3DXVECTOR2 & _vPA, D3DXVECTOR2 & _vPB, FLOAT _r, FLOAT _g, FLOAT _b, FLOAT _a ) ;
	VOID DrawRect ( SHORT _nxA, SHORT _nyA, SHORT _nxB, SHORT _nyB, D3DXVECTOR4 & _vColor ) ;
	VOID DrawRect ( SHORT _nxA, SHORT _nyA, SHORT _nxB, SHORT _nyB, DWORD _dwColor ) ;
	VOID DrawRect ( SHORT _nxA, SHORT _nyA, SHORT _nxB, SHORT _nyB, FLOAT _r, FLOAT _g, FLOAT _b, FLOAT _a ) ;
	VOID DrawRect ( FLOAT _xA, FLOAT _yA, FLOAT _xB, FLOAT _yB, D3DXVECTOR4 & _vColor ) ;
	VOID DrawRect ( FLOAT _xA, FLOAT _yA, FLOAT _xB, FLOAT _yB, DWORD _dwColor ) ;
	VOID DrawRect ( FLOAT _xA, FLOAT _yA, FLOAT _xB, FLOAT _yB, FLOAT _r, FLOAT _g, FLOAT _b, FLOAT _a ) ;

	VOID DrawLineGrad ( D3DXVECTOR2 & _vPA, D3DXVECTOR4 & _vCA, D3DXVECTOR2 & _vPB, D3DXVECTOR4 & _vCB ) ;

	VOID DrawLine ( D3DXVECTOR2 & _vPA, D3DXVECTOR2 & _vPB, D3DXVECTOR4 & _vColor ) ;
	VOID DrawLine ( D3DXVECTOR2 & _vPA, D3DXVECTOR2 & _vPB, DWORD _dwColor ) ;
	VOID DrawLine ( D3DXVECTOR2 & _vPA, D3DXVECTOR2 & _vPB, FLOAT _r, FLOAT _g, FLOAT _b, FLOAT _a ) ;
	VOID DrawLine ( SHORT _nxA, SHORT _nyA, SHORT _nxB, SHORT _nyB, D3DXVECTOR4 & _vColor ) ;
	VOID DrawLine ( SHORT _nxA, SHORT _nyA, SHORT _nxB, SHORT _nyB, DWORD _dwColor ) ;
	VOID DrawLine ( SHORT _nxA, SHORT _nyA, SHORT _nxB, SHORT _nyB, FLOAT _r, FLOAT _g, FLOAT _b, FLOAT _a ) ;
	VOID DrawLine ( FLOAT _xA, FLOAT _yA, FLOAT _xB, FLOAT _yB, D3DXVECTOR4 & _vColor ) ;
	VOID DrawLine ( FLOAT _xA, FLOAT _yA, FLOAT _xB, FLOAT _yB, DWORD _dwColor ) ;
	VOID DrawLine ( FLOAT _xA, FLOAT _yA, FLOAT _xB, FLOAT _yB, FLOAT _r, FLOAT _g, FLOAT _b, FLOAT _a ) ;

	VOID DrawPoint ( D3DXVECTOR2 & _vPoint, D3DXVECTOR4 & _vColor ) ;
	VOID DrawPoint ( D3DXVECTOR2 & _vPoint, DWORD _dwColor ) ;
	VOID DrawPoint ( D3DXVECTOR2 & _vPoint, FLOAT _r, FLOAT _g, FLOAT _b, FLOAT _a ) ;
	VOID DrawPoint ( SHORT _nx, SHORT _ny, D3DXVECTOR4 & _vColor ) ;
	VOID DrawPoint ( SHORT _nx, SHORT _ny, DWORD _dwColor ) ;
	VOID DrawPoint ( SHORT _nx, SHORT _ny, FLOAT _r, FLOAT _g, FLOAT _b, FLOAT _a ) ;
	VOID DrawPoint ( FLOAT _x, FLOAT _y, D3DXVECTOR4 & _vColor ) ;
	VOID DrawPoint ( FLOAT _x, FLOAT _y, DWORD _dwColor ) ;
	VOID DrawPoint ( FLOAT _x, FLOAT _y, FLOAT _r, FLOAT _g, FLOAT _b, FLOAT _a ) ;

	BLENDSTATE12* GetBlendState ( ) ;
	VOID SetBlendState ( BLENDSTATE12* _pBlendState ) ;

	FILTERSTATE12* GetFilterState ( ) ;
	VOID SetFilterState ( FILTERSTATE12* _pFilterState ) ;

	STAGESTATE12* GetStageState ( ) ;
	VOID SetStageState ( DWORD _dwStage, STAGESTATE12* _pStageState ) ;

	VOID ProcessCommand ( LPSTR sCommand ) ;
	VOID ProcessHelp ( ) ;

};
