#include "Common/Common.h"

#include <sys/time.h>

namespace MinCOM
{

    int IThread::GetSelfId()
    {
        // When switching to 64-bit compiler, this routine should return intptr_t
        // ( declared in <inttypes.h> ).
        return (int)pthread_self();
    }

    longlong IThread::Time()
    {
        struct timeval tp;
        ::gettimeofday(&tp, NULL);
        return tp.tv_sec * 1000 + tp.tv_usec / 1000;
    }

    void IThread::Sleep(unsigned long delay)
    {
        usleep(delay * 1000); // Converting delay from milliseconds to microseconds.
    }
    
}
