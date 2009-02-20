#include "Common/Common.h"

#include "ReadWriteLock.h"

namespace MinCOM
{

	ReadWriteLock::ReadWriteLock()
		: mc::CommonImpl< IReadWriteLock >()
		, resourceMutex_( Library::Mutex() )
		, countersMutex_( Library::Mutex() )
		, writersCount_(0)
		, readersCount_(0)
	{
	}

	// IJobsQueue section
	result ReadWriteLock::WaitToWrite()
	{
		countersMutex_->Wait();
		++writersCount_;
		countersMutex_->Release();
		resourceMutex_->Wait();

		return _S_OK;
	}

	result ReadWriteLock::DoneWriting()
	{
		countersMutex_->Wait();
		--writersCount_;
		countersMutex_->Release();
		resourceMutex_->Release();

		return _S_OK;
	}

	result ReadWriteLock::WaitToRead()
	{
		countersMutex_->Wait();
		if ( ( writersCount_ > 0 ) || ( readersCount_ == 0 ) )
		{
			countersMutex_->Release();
			resourceMutex_->Wait();
			countersMutex_->Wait();
		}
		++readersCount_;
		countersMutex_->Release();

		return _S_OK;
	}

	result ReadWriteLock::DoneReading()
	{
		countersMutex_->Wait();
		--readersCount_;
		if ( 0 == readersCount_ )
		{
			resourceMutex_->Release();
		}
		countersMutex_->Release();

		return _S_OK;
	}

}
