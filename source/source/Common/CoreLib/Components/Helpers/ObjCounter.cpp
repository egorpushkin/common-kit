#include "Common/Common.h"

#include "CommonKit/Components.h"

namespace Components
{

	bool ObjCounter::lock_ = false;

	unsigned long ObjCounter::count_ = 0;

	ObjCounter::ObjCounter()
	{
		Increment();
	}

	ObjCounter::~ObjCounter()
	{
		Decrement();
	}

	bool ObjCounter::CanUnload()
	{
		if ( lock_ || count_ > 0 )
			return false;	

		return true;
	}

	void ObjCounter::Lock(bool lock)
	{
		lock_ = lock;

		if ( CanUnload() )
			NotifyOnUnload();
	}

	unsigned long ObjCounter::Increment()
	{
		return ++count_;
	}

	unsigned long ObjCounter::Decrement()
	{
		--count_;

		if ( CanUnload() )
			NotifyOnUnload();

		return count_;
	}

	void ObjCounter::NotifyOnUnload()
	{
		IInPlaceControllerPtr controller(ComponentHolder::Instance().GetInstance(), IID_IInPlaceController);
		if ( !controller )
			return;

		controller->SendUnloadRequest();
	}

}
