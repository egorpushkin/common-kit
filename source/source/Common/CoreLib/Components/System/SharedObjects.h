#ifndef SHAREDOBJECTS_H__COMPONENTS__COMMONKIT__INCLUDED_
#define SHAREDOBJECTS_H__COMPONENTS__COMMONKIT__INCLUDED_

// Standard routines for shared object management syntax replacement declaration
//////////////////////////////////////////////////////////////////////////

#ifdef WIN32
// Win32 replacements

#define SD_LoadLibrary(lib_name)										\
			LoadLibraryA(lib_name)

#define SD_GetProcAddress(lib_module, routine_name)						\
			GetProcAddress((HMODULE)lib_module, routine_name);

#define SD_FreeLibrary(lib_module)										\
			FreeLibrary((HMODULE)lib_module); lib_module = NULL

#define SO_LIB_EXT mc::StringA(".dll")

#else // WIN32
// Linux replacements

#define SD_LoadLibrary(lib_name)										\
			dlopen(lib_name, RTLD_LAZY)

#define SD_GetProcAddress(lib_module, routine_name)						\
			dlsym(lib_module, routine_name);

#define SD_FreeLibrary(lib_module)										\
			dlclose(lib_module); lib_module = NULL

#define SO_LIB_EXT mc::StringA(".so")

#endif // WIN32

#endif // !SHAREDOBJECTS_H__COMPONENTS__COMMONKIT__INCLUDED_
