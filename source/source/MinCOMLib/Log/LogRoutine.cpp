#include "Common/Common.h"

#include "LogStorage.h"

#include <fstream>

namespace MinCOM
{

	LogRoutine::LogRoutine(
		const std::string& function, 
		const std::string& file /* = std::string() */,
		long line /* = 0 */)
		: function_(function)
		, file_(file)
		, line_(line)
	{
		int indent = LogStorage::Instance().GetIndent();
		PutLogRecord(indent, false);
		LogStorage::Instance().IncreaseIndent();
	}

	LogRoutine::~LogRoutine()
	{
		LogStorage::Instance().DecreaseIndent();
		int indent = LogStorage::Instance().GetIndent();
		PutLogRecord(indent, true);
	}

	void LogRoutine::PutLogRecord(int indent, bool terminating)
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

		if ( terminating )
			logFile << "\\";
		logFile << function_;
		logFile << std::endl;
	}

}
