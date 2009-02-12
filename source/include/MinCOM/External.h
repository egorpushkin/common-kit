#ifndef EXTERNAL_H__MINCOM__COMMONKIT__INCLUDED_
#define EXTERNAL_H__MINCOM__COMMONKIT__INCLUDED_

// Include it to determine platform correctly.
#include <stddef.h>

// Platform dependencies
//////////////////////////////////////////////////////////////////////////
#if defined(WIN32)
 #define WIN32_LEAN_AND_MEAN	
 #include <Windows.h>
#elif defined(__GNUC__)
 #ifndef POSIX
  #define POSIX 0
 #endif
 #include <pthread.h>
#endif

// Standard library requirements
//////////////////////////////////////////////////////////////////////////
// #include <stdio.h>

#ifdef _MSC_VER
#include <tchar.h>
#elif WIN32 // MinGW or something else	
#include <tchar.h>
#elif POSIX // any Posix macro
#include <tchar.h>
#elif __MACH__
// unknown header or not required at all
#endif // _MSC_VER

#include <string.h>

// C++ STD requirements
//////////////////////////////////////////////////////////////////////////
#include <string>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <istream>

// Loki library dependencies.
//////////////////////////////////////////////////////////////////////////
 
// Some MSVC++ warnings related to some known internal library issues 
// should be disabled.
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4541)
#endif

// Enable internal synchronization support.
#define LOKI_OBJECT_LEVEL_THREADING

#include "loki/SmartPtr.h"
// #include "../../../sdk/include/loki/RefToValue.h"
// #include "../../../sdk/include/loki/TypeManip.h"
// #include "../../../sdk/include/loki/Singleton.h"

#ifdef _MSC_VER
#pragma warning( pop ) 
#endif

// Calling conventions
//////////////////////////////////////////////////////////////////////////
#ifdef _MSC_VER
#define mc_stdcall __stdcall
#elif WIN32 // MinGW or something else	
#elif POSIX // any Posix macro
#elif __MACH__
#define mc_stdcall
#endif // _MSC_VER

#endif // !EXTERNAL_H__MINCOM__COMMONKIT__INCLUDED_
