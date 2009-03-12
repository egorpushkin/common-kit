#include "Common/Common.h"

namespace MinCOM
{

	unsigned int IThread::GetCores()
	{
		return 0;
	}

	void IThread::Sleep(unsigned long delay)
	{
		::Sleep(delay);
	}

	int IThread::GetSelfId()
	{
		return ::GetCurrentThreadId();
	}

}
