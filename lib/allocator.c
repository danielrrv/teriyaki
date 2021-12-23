#

#if defined(_WIN32)
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif
#include <windows.h>
#endif
#include <stdio.h>
#include <stdlib.h>

void *teriyaki_malloc(size_t size)
{
#if defined(_WIN32)
	return (void *)HeapAlloc(GetProcessHeap(), 0, size);
#else
	return (void *)malloc(size);
#endif
}