#include "Common/Common.h"

namespace MinCOM
{

	SemaphoreScopeRelease::SemaphoreScopeRelease(ISemaphoreRef semaphore, long count /* = 1 */)
		: semaphore_(semaphore)
		, count_(count)
	{
	}

	SemaphoreScopeRelease::~SemaphoreScopeRelease()
	{
		if ( !semaphore_ )
			return;
		semaphore_->Release(count_);
	}

}
