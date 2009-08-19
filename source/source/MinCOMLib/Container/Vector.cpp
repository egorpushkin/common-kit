#include "Common/Common.h"

#include "Vector.h"
#include "VectorEnumerator.h"

namespace MinCOM
{

	Vector::Vector()
		: CommonImpl< IVector >()
		, APImpl()
		, stdVector_()
		, lock_( Library::ReadWriteLock() )
		, eventsSpreader_()
	{
	}

	Vector::Vector(size_t count)
		: CommonImpl< IVector >()
		, stdVector_(count)
	{
	}

	ICommonPtr Vector::At(size_t pos)
	{
		// Wait until container reading is allowed.
		IReadWriteLock::Reader_ locler(lock_);
		// Check whether position is valid.
		if ( !IsPositionValid(pos) )
			return NULL;
		// Provide caller with the object he/she is interested in.
		return stdVector_.at(pos);
	}

	void Vector::Clear()
	{
		// Wait until container modification is allowed.
		IReadWriteLock::Writer_ locler(lock_);
		// Clear the contents of the vector.
		stdVector_.clear();
		// Spread corresponding event.
		eventsSpreader_->ContainerModified( CommonImpl< IVector >::GetSelf( ) );
	}

	IEnumeratorPtr Vector::GetEnumerator(size_t pos /* = 0 */)
	{
		// Wait until container modification is allowed.
		IReadWriteLock::Writer_ locler(lock_);
		// Check whether position is correct.
		if ( !IsPositionValid(pos) )
			return NULL;
		// Construct enumerator.
		return Class< VectorEnumerator >::Create(CommonImpl< IVector >::GetSelf(), lock_, pos);
	}

	// ICommon section
	result Vector::PostInit()
	{
		// Register additional access point for events' delivery and configure 
		// events spreader.
		eventsSpreader_ = APImpl::AdviseAndThrow( TypeInfo< DCommands >::GetGuid() );
		return _S_OK;
	}

	inline bool Vector::IsPositionValid(size_t pos)
	{
		return ( pos < stdVector_.size() );
	}

}
