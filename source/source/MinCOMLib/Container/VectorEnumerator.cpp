#include "Common/Common.h"

#include "VectorEnumerator.h"

namespace MinCOM
{

	VectorEnumerator::VectorEnumerator(IVectorRef container, IReadWriteLockRef lock, size_t pos)
		: CommonImpl< IEnumerator >()
		, container_(container)
		, lock_(lock)
		, pos_(pos)
	{
	}

	// IEnumerator section
	ICommonPtr VectorEnumerator::GetCurrent() const
	{
		// Ensure that reading is allowed.
		IReadWriteLockPtr lock(lock_);
		if ( !lock_ )
			return NULL;
		IReadWriteLock::Reader_ locker(lock);
		// Check whether container is still alive.
		IVectorPtr container(container_);
		if ( !container )
			return NULL;
		// Get element at pos_ from container.
		return container->At(pos_);
	}

	bool VectorEnumerator::Next()
	{
		// TODO: 
		return false;
	}

	bool VectorEnumerator::Prev()
	{
		// TODO: 
		return false;
	}

	bool VectorEnumerator::HasNext() const
	{
		// TODO: 
		return false;
	}

	bool VectorEnumerator::HasPrev() const
	{
		// TODO: 
		return false;
	}

	bool VectorEnumerator::IsValid() const
	{
		IReadWriteLockPtr lock(lock_);
		if ( !lock_ )
			return false;
		IVectorPtr container(container_);
		if ( !container )
			return false;
		return true;
	}

	// Internal tools
	ICommonPtr VectorEnumerator::GetContainer()
	{
		return IVectorPtr(container_);
	}

}
