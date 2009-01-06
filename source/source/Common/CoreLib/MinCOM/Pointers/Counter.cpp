#include "Common/Common.h"

namespace MinCOM
{

	Counter::Counter()
		: count_(0)
	{
	}

	Counter::~Counter()
	{
	}

	void Counter::Increment()
	{
		++count_;
	}
		
	void Counter::Decrement()
	{
		if ( count_ > 0 )
			--count_;
	}

	uintptr_t Counter::GetCount()
	{
		return count_;
	}

	Counter* Counter::Create()
	{
		/*Counter* pCounter = (Counter*)::VirtualAlloc(NULL, sizeof(Counter), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

		pCounter->count_ = 0;
		
		return pCounter; */
		
		return new Counter;
	}

	void Counter::Release(Counter* pCounter)
	{
		// ::VirtualFree(pCounter, 0, MEM_RELEASE);
		pCounter->DoRelease();
	}

	void Counter::DoRelease()
	{
		delete this;
	}

}
