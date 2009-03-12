/*
* File name   : LogRoutine.h
*
* Copyright (c) 2009 Scientific Software
*
* Modification History:
* Date        Name                Description
* 2009-03-12  Egor Pushkin        Initial version
*/

#ifndef LOGROUTINE_H__MINCOM__INCLUDED_
#define LOGROUTINE_H__MINCOM__INCLUDED_

namespace MinCOM
{

	/**
	 * Wraps any routine in a pair of statements.
	 */
	class LogRoutine
	{
	public:

		LogRoutine(
			const std::string& function, 
			const std::string& file = std::string(),
			long line = 0);

		~LogRoutine();

	private:

		void PutLogRecord(int indent, bool terminating);

	private:

		std::string function_; 
		std::string file_;
		long line_;

	};

}

// Define convenience macro for wrapping routines.
#if !defined(MC_DISABLE_LOG)
#	define MC_LOG_ROUTINE MinCOM::LogRoutine routine(MC_FUNCTION, __FILE__, __LINE__);
#	define MC_LOG_ROUTINE_NAMED(name) MinCOM::LogRoutine routine(name, __FILE__, __LINE__);
#else
#	define MC_LOG_ROUTINE
#	define MC_LOG_ROUTINE_NAMED
#endif

#endif // !LOGROUTINE_H__MINCOM__INCLUDED_
