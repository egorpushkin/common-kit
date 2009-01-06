#include "Common/Common.h"

namespace MinCOM
{

	namespace Private
	{
		result lastErrorCode = _S_OK;
	}

	result GetLastError()
	{
		return Private::lastErrorCode;
	}	

	void SetLastError(result code)
	{
		Private::lastErrorCode = code;
	}

}
