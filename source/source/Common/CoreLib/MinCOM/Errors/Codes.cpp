#include "Common/Common.h"

namespace MinCOM
{

	// Core operations
	//////////////////////////////////////////////////////////////////////////

	result MakeResult(result severity, result facility, result code)
	{
		return ( (result) (((unsigned long)(severity)<<31) | ((unsigned long)(facility)<<16) \
			| ((unsigned long)(code))) );
	}

	result ResultCode(result status)
	{
		return ((status) & 0xFFFF);
	}

	result ResultFacility(result status)
	{
		return (((status) >> 16) & 0xff);
	}

	result ResultSeverity(result status) 
	{
		return (((status) >> 31) & 0x1);
	} 

	bool IsError(result status) 
	{
		return ((unsigned long)(status) >> 31 == _SEVERITY_ERROR);
	}

	bool IsSucceeded(result status)
	{
		return ((long)(status) >= 0);
	}

	bool IsFailed(result status)
	{
		return ((long)(status) < 0);
	}

}
