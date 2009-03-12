#include "Common/Common.h"

namespace MinCOM
{

	std::string Log::logFilePrefix_ = std::string();

	void Log::SetLogFilePrefix(const std::string& prefix)
	{
		logFilePrefix_ = prefix;
	}

	std::string Log::GetLogFilePrefix()
	{
		return logFilePrefix_;
	}

}
