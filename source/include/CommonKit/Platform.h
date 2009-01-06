#ifndef PLATFORM_H__MINCOM__COMMONKIT__INCLUDED_
#define PLATFORM_H__MINCOM__COMMONKIT__INCLUDED_

#ifdef WIN32

#define CINTERFACE
#include <Windows.h>

#else

#include <dlfcn.h>

#endif

#endif // !PLATFORM_H__MINCOM__COMMONKIT__INCLUDED_
