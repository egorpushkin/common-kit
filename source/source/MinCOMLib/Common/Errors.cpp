#include "Common/Common.h"

namespace MinCOM
{

	result Error::MakeResult(result severity, result facility, result code)
	{
		return ( (result) (((unsigned long)(severity)<<31) | ((unsigned long)(facility)<<16) \
			| ((unsigned long)(code))) );
	}

	result Error::ResultCode(result status)
	{
		return ((status) & 0xFFFF);
	}

	result Error::ResultFacility(result status)
	{
		return (((status) >> 16) & 0xff);
	}

	result Error::ResultSeverity(result status) 
	{
		return (((status) >> 31) & 0x1);
	} 

	bool Error::IsError(result status) 
	{
		return ((unsigned long)(status) >> 31 == _SEVERITY_ERROR);
	}

	bool Error::IsSucceeded(result status)
	{
		return ((long)(status) >= 0);
	}

	bool Error::IsFailed(result status)
	{
		return ((long)(status) < 0);
	}

	// See member declaration for details. 
	// std::map< long, result > LastError::errorCode_ = std::map< long, result >();

	/**
	 * Gets error code.
	 */
	result LastError::Get()
	{
		return _S_OK;
	}

	/**
 	 * Sets error code. Client code should not refer to this function.
	 */
	void LastError::Set(result /* code */)
	{		
	}

}
