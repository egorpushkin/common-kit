#include "Common/Common.h"

namespace MinCOM
{
    
    int IThread::GetSelfId()
    {
        return (int)pthread_self();
    }
    
}
