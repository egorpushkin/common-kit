#include "Common/Common.h"

namespace MinCOM
{

	void IThread::Sleep(unsigned long delay)
	{
		usleep(delay * 1000); // Converting delay from milliseconds to microseconds.
	}
    
    int IThread::GetSelfId()
    {
        return (int)pthread_self();
    }
    
}
