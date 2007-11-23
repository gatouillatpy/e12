
#include "engine.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



RESOURCE12* ENGINE12::GetResource ( LPSTR _sFile )
{
	return iResource->Get( _sFile );
}



WINDOW12* ENGINE12::GetWindow ( DWORD _dwIndex )
{
	return (WINDOW12*)iWindow->Get( _dwIndex );
}

WINDOW12* ENGINE12::GetWindow ( LPSTR _sName )
{
	return (WINDOW12*)iWindow->Get( _sName );
}



INPUT12* ENGINE12::GetInput ( DWORD _dwIndex )
{
	return (INPUT12*)iInput->Get( _dwIndex );
}

INPUT12* ENGINE12::GetInput ( LPSTR _sName )
{
	return (INPUT12*)iInput->Get( _sName );
}



RENDER12* ENGINE12::GetRender ( DWORD _dwIndex )
{
	return (RENDER12*)iRender->Get( _dwIndex );
}

RENDER12* ENGINE12::GetRender ( LPSTR _sName )
{
	return (RENDER12*)iRender->Get( _sName );
}



TIMER12* ENGINE12::GetTimer ( DWORD _dwIndex )
{
	return (TIMER12*)iTimer->Get( _dwIndex );
}

TIMER12* ENGINE12::GetTimer ( LPSTR _sName )
{
	return (TIMER12*)iTimer->Get( _sName );
}
