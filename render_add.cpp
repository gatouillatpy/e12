
#include "render.h"
#include "engine.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



CAMERA12* RENDER12::AddCamera ( )
{
	return new CAMERA12( this );
}



FRAME12* RENDER12::AddFrame ( )
{
	return new FRAME12( this );
}

TEXTBOX12* RENDER12::AddTextbox ( )
{
	return new TEXTBOX12( this );
}

CMDBOX12* RENDER12::AddCmdbox ( )
{
	return new CMDBOX12( this );
}

BUTTON12* RENDER12::AddButton ( )
{
	return new BUTTON12( this );
}

CURSOR12* RENDER12::AddCursor ( )
{
	return new CURSOR12( this );
}

IMAGE12* RENDER12::AddImage ( )
{
	return new IMAGE12( this );
}

LABEL12* RENDER12::AddLabel ( )
{
	return new LABEL12( this );
}

ALABEL12* RENDER12::AddALabel ( )
{
	return new ALABEL12( this );
}

CONTROL12* RENDER12::AddControl ( )
{
	return new CONTROL12( this );
}



CONSOLE12* RENDER12::AddConsole ( UINT _nLineCount )
{
	return new CONSOLE12( this, _nLineCount );
}

INTERFACE12* RENDER12::AddInterface ( )
{
	return new INTERFACE12( this );
}



BOX12* RENDER12::AddBox ( )
{
	return new BOX12( this );
}

COMPLEX12* RENDER12::AddComplex ( )
{
	return new COMPLEX12( this );
}

CYLINDER12* RENDER12::AddCylinder ( )
{
	return new CYLINDER12( this );
}

GRID12* RENDER12::AddGrid ( )
{
	return new GRID12( this );
}

MESH12* RENDER12::AddMesh ( )
{
	return new MESH12( this );
}

SPRITE12* RENDER12::AddSprite ( )
{
	return new SPRITE12( this );
}

SURFACE12* RENDER12::AddSurface ( )
{
	return new SURFACE12( this );
}

OBJECT12* RENDER12::AddObject ( )
{
	return new OBJECT12( this );
}



SCENE12* RENDER12::AddScene ( )
{
	return new SCENE12( this );
}



GEOMETRY12* RENDER12::AddGeometry ( )
{
	return new GEOMETRY12( this );
}



HITBOX12* RENDER12::AddHitbox ( ENTITY12* _pOwner )
{
	return new HITBOX12( this, _pOwner );
}



ANIMATION12* RENDER12::AddAnimation ( )
{
	return new ANIMATION12( this );
}

VOLUME12* RENDER12::AddVolume ( )
{
	return new VOLUME12( this );
}

TEXTURE12* RENDER12::AddTexture ( )
{
	return new TEXTURE12( this );
}



FONT12* RENDER12::AddFont ( )
{
	return new FONT12( this );
}



SHADER12* RENDER12::AddShader ( )
{
	return new SHADER12( this );
}
