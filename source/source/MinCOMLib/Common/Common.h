#ifndef COMMON_H__MINCOMLIB__INCLUDED_
#define COMMON_H__MINCOMLIB__INCLUDED_

// Boost ASIO 
//////////////////////////////////////////////////////////////////////////

#ifdef WIN32
// Required by Windows headers.
#define _WIN32_WINNT 0x0501
#endif 

// Disable warning (L1 unreferenced formal parameter).
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4100)
#endif

// This should be included before MinCOM. Because it (MinCOM) includes 
// WIN32_LEAN_AND_MEAN Windows itself.
#include <boost/asio.hpp>

#ifdef _MSC_VER
#pragma warning( pop ) 
#endif

// Additional Boost requirements
#include <boost/bind.hpp>

// Minimalist COM implementation
//////////////////////////////////////////////////////////////////////////

#include "MinCOM/MinCOM.h"

#endif // !COMMON_H__MINCOMLIB__INCLUDED_
