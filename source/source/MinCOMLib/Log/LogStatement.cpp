#include "Common/Common.h"

#include "LogStorage.h"

#include <fstream>

namespace MinCOM
{

	LogStatement::LogStatement(
		const std::string& statement, 
		const std::string& file /* = std::string() */,
		long line /* = 0 */)
		: statement_(statement)
		, file_(file)
		, line_(line)
	{
		int indent = LogStorage::Instance().GetIndent();
		PutLogRecord(indent);
	}

	void LogStatement::PutLogRecord(int indent)
	{
		std::stringstream str;
		str << IThread::GetSelfId();
		std::string threadId;
		str >> threadId;

		std::string logFileName = Log::GetLogFilePrefix() + threadId + std::string(".log");
		std::ofstream logFile(logFileName.c_str(), std::ios_base::app);
		if ( logFile.bad() )
			return;
	
		std::fill_n( std::ostream_iterator< char >(logFile, ""), indent, ' ' );

		logFile << statement_;
		logFile << std::endl;
	}

}
