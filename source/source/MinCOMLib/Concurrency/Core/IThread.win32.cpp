#include "Common/Common.h"

namespace MinCOM
{

	unsigned int IThread::GetCores()
	{
		return 0;
	}

    longlong IThread::GetSelfId()
    {
        return ::GetCurrentThreadId();
    }

    longlong IThread::Time()
    {
        FILETIME now;
        ::GetSystemTimeAsFileTime(&now);
        return (mc::longlong)now.dwLowDateTime + ((mc::longlong)(now.dwHighDateTime) << 32LL);
    }

	void IThread::Sleep(unsigned long delay)
	{
		::Sleep(delay);
	}

}
