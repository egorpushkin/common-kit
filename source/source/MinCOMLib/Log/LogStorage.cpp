#include "Common/Common.h"

#include "LogStorage.h"

namespace MinCOM
{

	LogStorage& LogStorage::Instance()
	{
		return Loki::SingletonHolder< LogStorage >::Instance();
	}

	LogStorage::LogStorage()
		: lock_()
	{		
	}

	int LogStorage::GetIndent()
	{
		LogLocalData_ & data = GetLocalData();
		return data.indent_;
	}

	void LogStorage::IncreaseIndent()
	{
		LogLocalData_ & data = GetLocalData();
		++data.indent_;		
	}

	void LogStorage::DecreaseIndent()
	{
		LogLocalData_ & data = GetLocalData();
		--data.indent_;		
	}

	LogStorage::LogLocalData_& LogStorage::GetLocalData()
	{
		CoreMutexLock locker(lock_);

		int threadId = IThread::GetSelfId();
		// Check whether corresponding record already exists.
		LogData_::iterator iter = logData_.find(threadId);
		if ( iter == logData_.end() )
		{
			// Record corresponding to current thread has not been found. 
			// Configure it. 
			LogLocalData_ data;
			data.indent_ = 0;
			logData_[threadId] = data;
			return logData_[threadId];
		}
		return (*iter).second;
	}

}
