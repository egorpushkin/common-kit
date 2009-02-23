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
		// Ensure that reading is allowed.
		IReadWriteLockPtr lock(lock_);
		if ( !lock_ )
			return false;
		// Check whether container is still alive.
		IVectorPtr container(container_);
		if ( !container )
			return false;	
		// Move to next element if it is possible.
		if ( HasNextInternal(container) )
		{
			if ( pos_ != (size_t)-1 )
				++pos_;
			else
				pos_ = 0;
			return true;
		}
		else
		{
			pos_ = (size_t)-1;
			return false;
		}
	}

	bool VectorEnumerator::Prev()
	{
		// Ensure that reading is allowed.
		IReadWriteLockPtr lock(lock_);
		if ( !lock_ )
			return false;
		// Check whether container is still alive.
		IVectorPtr container(container_);
		if ( !container )
			return false;	
		// Move to previous element if it is possible.
		if ( HasPrevInternal(container) )
		{
			if ( pos_ != (size_t)-1 )
				--pos_;
			else
				pos_ = container->Size() - 1;
			return true;
		}
		else
		{
			pos_ = (size_t)-1;
			return false;
		}
	}

	bool VectorEnumerator::HasNext() const
	{
		// Ensure that reading is allowed.
		IReadWriteLockPtr lock(lock_);
		if ( !lock_ )
			return false;
		// Check whether container is still alive.
		IVectorPtr container(container_);
		if ( !container )
			return false;
		// Delegate actual work to unsafe internal tool.
		return HasNextInternal(container);
	}

	bool VectorEnumerator::HasPrev() const
	{
		// Ensure that reading is allowed.
		IReadWriteLockPtr lock(lock_);
		if ( !lock_ )
			return false;
		// Check whether container is still alive.
		IVectorPtr container(container_);
		if ( !container )
			return false;
		// Delegate actual work to unsafe internal tool.
		return HasPrevInternal(container);
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
	bool VectorEnumerator::HasNextInternal(IVectorRef container) const
	{
		size_t size = container->Size();
		if ( (size_t)-1 == pos_  )
		{
			if ( size > 0 )
				return true;
			else
				return false;
		}
		else if ( ( size > 0 ) && ( pos_ < size - 1 ) )
		{
			return true;
		}
		return false;
	}

	bool VectorEnumerator::HasPrevInternal(IVectorRef container) const
	{
		size_t size = container->Size();
		if ( (size_t)-1 == pos_ )
		{
			if ( size > 0 )
				return true;
			else
				return false;
		}
		else if ( ( size > 0 ) && ( pos_ > 0 ) )
		{
			return true;
		}
		return false;
	}

}
