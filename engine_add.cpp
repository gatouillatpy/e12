
#include "engine.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



RESOURCE12* ENGINE12::AddResource ( ENTITY12* _pEntity, LPSTR _sFile )
{
	return iResource->Set( _pEntity, _sFile );
}



WINDOW12* ENGINE12::AddWindow ( )
{
	return new WINDOW12( this );
}



INPUT12* ENGINE12::AddInput ( )
{
	return new INPUT12( this );
}



RENDER12* ENGINE12::AddRender ( )
{
	return new RENDER12( this );
}



TIMER12* ENGINE12::AddTimer ( )
{
	return new TIMER12( this );
}
