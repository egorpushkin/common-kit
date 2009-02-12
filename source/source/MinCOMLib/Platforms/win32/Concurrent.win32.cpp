#include "Common/Common.h"

#include "Concurrent.win32.h"

namespace MinCOM
{

	result ConcurrentWin32::Wait(HANDLE object, unsigned long delay)
	{
		if ( !object )
			return _E_NOTINIT;

		unsigned long waitResult = ::WaitForSingleObject(object, delay);
		
		if ( WAIT_ABANDONED == waitResult || WAIT_FAILED == waitResult )
			return _E_FAIL;

		if ( WAIT_TIMEOUT == waitResult )
			return _S_FALSE;
		
		// waitResult == WAIT_OBJECT_0
		return _S_OK;
	}

}
