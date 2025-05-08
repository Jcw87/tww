
#ifndef _MINIMAL_WINDOWS_H
#define _MINIMAL_WINDOWS_H

#if defined(_M_IX86) || defined(__i386__) || defined(__i486__) || defined(__i586__) || defined(__i686__)
#define _X86_
#elif defined(_M_AMD64) || defined(__amd64__)
#define _AMD64_
#elif defined(__ppc__) || defined(__POWERPC__) || defined(__PPCGECKO__) || defined(_M_PPC)
#define _PPC_
#endif

#define NOMINMAX

#include <windef.h>
#include <minwinbase.h>
#include <synchapi.h>
#undef far
#undef near
#undef EXCEPTION_BREAKPOINT
#undef IN

#endif
