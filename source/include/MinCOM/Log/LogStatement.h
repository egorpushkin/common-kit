/*
* File name   : LogStatement.h
*
* Copyright (c) 2009 Scientific Software
*
* Modification History:
* Date        Name                Description
* 2009-03-12  Egor Pushkin        Initial version
*/

#ifndef LOGSTATEMENT_H__MINCOM__INCLUDED_
#define LOGSTATEMENT_H__MINCOM__INCLUDED_

namespace MinCOM
{

	/**
	 * Puts single statement to the log.
	 */
	class LogStatement
	{
	public:

		LogStatement(
			const std::string& statement, 
			const std::string& file = std::string(),
			long line = 0);

	private:

		void PutLogRecord(int indent);

	private:

		std::string statement_; 
		std::string file_;
		long line_;

	};

}

// Define convenience macro for wrapping routines.
#if !defined(MC_DISABLE_LOG)
#	define MC_LOG_STATEMENT(name) { MinCOM::LogStatement statement(name, __FILE__, __LINE__); }
#else
#	define MC_LOG_STATEMENT
#endif

#endif // !LOGSTATEMENT_H__MINCOM__INCLUDED_
