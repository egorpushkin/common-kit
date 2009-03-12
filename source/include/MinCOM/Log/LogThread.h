/*
* File name   : LogThread.h
*
* Copyright (c) 2009 Scientific Software
*
* Modification History:
* Date        Name                Description
* 2009-03-12  Egor Pushkin        Initial version
*/

#ifndef LOGTHREAD_H__MINCOM__INCLUDED_
#define LOGTHREAD_H__MINCOM__INCLUDED_

namespace MinCOM
{

	/**
	 * Wraps any routine in a pair of statements.
	 */
	class LogThread
	{
	public:

		/* LogRoutine(
			const std::string& function, 
			const std::string& file = std::string(),
			const std::string& line = std::string());

		~LogRoutine();

	private:

		std::string function_; 
		std::string file_;
		std::string line_; */

	};

}
/* 
// Define convenience macro for wrapping routines.
#if !defined(MC_DISABLE_LOG)
#	define MC_LOG_ROUTINE MinCOM::LogRoutine routine##__LINE__(, __FILE__, __LINE__);
#else
#	define MC_LOG_ROUTINE
#endif
*/
#endif // !LOGTHREAD_H__MINCOM__INCLUDED_
