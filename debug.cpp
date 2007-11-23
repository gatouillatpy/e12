
#include "debug.h"



void* operator new(size_t nSize, const char * lpszFileName, int nLine)
{
	return ::operator new(nSize, 1, lpszFileName, nLine);
}

void operator delete(void * p, const char * lpszFileName, int nLine)
{
	return ::operator delete(p, 1, lpszFileName, nLine);
}
