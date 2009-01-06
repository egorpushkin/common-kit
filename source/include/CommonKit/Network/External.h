#ifndef EXTERNAL_H__NETWORK__COMMONKIT__INCLUDED_
#define EXTERNAL_H__NETWORK__COMMONKIT__INCLUDED_

// MinCOM library
//////////////////////////////////////////////////////////////////////////
#include "../MinCOM.h"


// asio requirements
//////////////////////////////////////////////////////////////////////////
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4127)
#pragma warning(disable: 4267)
#pragma warning(disable: 4512)
#pragma warning(disable: 4311)
#pragma warning(disable: 4312)
#pragma warning(disable: 4100)
#endif

#define _WIN32_WINNT 0x0501

#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>

#include <boost/asio.hpp>

namespace asio
{
	using namespace boost::asio;
	using boost::system::error_code;
}

#ifdef _MSC_VER
#pragma warning( pop ) 
#endif

#endif // !EXTERNAL_H__NETWORK__COMMONKIT__INCLUDED_
