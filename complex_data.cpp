
#include "complex.h"
#include "scene.h"
#include "render.h"

#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



VOID COMPLEX12::SetOperation ( DWORD _dwOperation )
{
	dwOperation = _dwOperation;
}

_inline DWORD COMPLEX12::GetOperation ( )
{
	return dwOperation;
}