#include "Common/Common.h"

#include "Vector.h"

namespace MinCOM
{

	Vector::Vector()
		: CommonImpl< IVector >()
		, APImpl()
		, stdVector_()
		, eventsSpreader_()
	{
	}

	Vector::Vector(size_t count)
		: CommonImpl< IVector >()
		, stdVector_(count)
	{
	}

	void Vector::Assign(size_t count, ICommonRef value)
	{
		CoreMutexLock locker(CommonImpl< IVector >::GetLock());

		stdVector_.assign(count, value);
	}

	void Vector::Assign(IIteratorRef first, IIteratorRef last)
	{
		CoreMutexLock locker(CommonImpl< IVector >::GetLock());

		IPrivateIteratorPtr_ firstIter(first);
		IPrivateIteratorPtr_ lastIter(last);

		if ( !firstIter || !lastIter )
			return;

		stdVector_.assign(firstIter->GetStdIterator(), lastIter->GetStdIterator());
	}

	IIteratorPtr Vector::Begin()
	{			
		CoreMutexLock locker(CommonImpl< IVector >::GetLock());

		return Class< Iterator_ >::Create(CommonImpl< IVector >::GetSelf(), stdVector_.begin());
	}

	IIteratorPtr Vector::End()
	{	
		CoreMutexLock locker(CommonImpl< IVector >::GetLock());

		return Class< Iterator_ >::Create(CommonImpl< IVector >::GetSelf(), stdVector_.begin());
	}


	void Vector::PushBack(ICommonRef val)
	{
		// Synchronize call.
		CoreMutexLock locker(CommonImpl< IVector >::GetLock());
		// Add element.
		stdVector_.push_back(val);
		// Notify subscribers on new event.
		eventsSpreader_->ElementAdded(APImpl::GetSelf(), val);
	}


	void Vector::Clear()
	{
		// Synchronize call.
		CoreMutexLock locker(CommonImpl< IVector >::GetLock());
		// Clear contents.
		stdVector_.clear();
		// Notify subscribers on new event.
		eventsSpreader_->ContainerCleared(APImpl::GetSelf());
	}

	// ICommon section
	result Vector::PostInit()
	{
		// Register additional access point for events' delivery and configure 
		// events spreader.
		eventsSpreader_ = APImpl::AdviseAndThrow( TypeInfo< DCommands >::GetGuid() );
		return _S_OK;
	}

}
