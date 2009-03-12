/*
 * File name   : Log.h
 *
 * Copyright (c) 2009 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-03-12  Egor Pushkin        Initial version
 */

#ifndef LOG_H__MINCOM__INCLUDED_
#define LOG_H__MINCOM__INCLUDED_

namespace MinCOM
{

	/**
	 * Provides advanced logging capabilities for client applications.
	 */
	class Log
	{
	public:

		/**
		 * 
		 */
		static void SetLogFilePrefix(const std::string& prefix);

		static std::string GetLogFilePrefix();

	private:

		static std::string logFilePrefix_;

	};

// Define portable MC_FUNCTION macro for later use.
#if defined(_MSC_VER)
#	define MC_FUNCTION __FUNCTION__
#elif defined(__MINGW32__) || defined(__GNUG__)
#	define MC_FUNCTION __PRETTY_FUNCTION__
#else
#	define MC_FUNCTION std::string()
#endif

}

#endif // !LOG_H__MINCOM__INCLUDED_
