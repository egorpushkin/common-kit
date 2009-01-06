#ifndef CODES_H__MINCOM__COMMONKIT__INCLUDED_
#define CODES_H__MINCOM__COMMONKIT__INCLUDED_

namespace MinCOM
{

	/************************************************************************

		Rresult bit structure:
	        
			|31         24|23           16|15            8|7             0|
			| | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | 
			|s| Reserved  |   Facility    |           Error code          |

		Result fields description:
			The facility field indicates the system service responsible 
			for the error.    

	************************************************************************/

	// Define type responsible for error code serialization
	////////////////////////////////////////////////////////////////////////// 

	typedef long result;

	// Define the severity codes
	//////////////////////////////////////////////////////////////////////////

	enum SeverityCodes
	{
		_SEVERITY_ERROR             = 1,
		_SEVERITY_SUCCESS           = 0
	};

	// Define the facility codes
	//////////////////////////////////////////////////////////////////////////

	enum FacilityCodes
	{
		_FACILITY_STORAGE           = 3,
		_FACILITY_STATE_MANAGEMENT  = 34,
		_FACILITY_SECURITY          = 9,
		_FACILITY_RPC               = 1,
		_FACILITY_SYSTEM            = 7,
		_FACILITY_CONTROL           = 10,
		_FACILITY_NULL              = 0,
		_FACILITY_METADIRECTORY     = 35,
		_FACILITY_INTERNET          = 12,
		_FACILITY_IOBJECT           = 2,
		_FACILITY_CONFIGURATION     = 33,
		_FACILITY_BACKGROUNDCOPY    = 32
	};

	// Core operations
	//////////////////////////////////////////////////////////////////////////

	result MakeResult(result severity, result facility, result code);
	
	result ResultCode(result status); 
		// ((status) & 0xFFFF)
	
	result ResultFacility(result status); 
		// (((status) >> 16) & 0xff)
	
	result ResultSeverity(result status); 
		// (((status) >> 31) & 0x1)
	
	bool IsError(result status); 
		// ((unsigned long)(status) >> 31 == SEVERITY_ERROR)
	
	bool IsSucceeded(result status);
		// ((long)(status) >= 0)

	bool IsFailed(result status);
		// ((long)(Status) < 0)

	// Define standard error codes
	//////////////////////////////////////////////////////////////////////////

	/************************************************************************

		Standard error codes description:
			_E_ABORT            The operation was aborted because of an unspecified error. 
			_E_ACCESSDENIED     A general access-denied error. 
			_E_FAIL             An unspecified failure has occurred. 
			_E_HANDLE           An invalid handle was used. 
			_E_INVALIDARG       One or more arguments are invalid. 
			_E_NOINTERFACE      The QueryInterface method did not recognize the requested 
							   interface. The interface is not supported. 
			_E_NOTIMPL          The method is not implemented. 
			_E_OUTOFMEMORY      The method failed to allocate necessary memory. 
			_E_PENDING          The data necessary to complete the operation is not yet 
							   available. 
			_E_POINTER          An invalid pointer was used. 
			_E_UNEXPECTED       A catastrophic failure has occurred. 
			_S_FALSE            The method succeeded and returned the boolean value FALSE. 
			_S_OK               The method succeeded. If a boolean return value is expected, 
							   the returned value is TRUE.         

	************************************************************************/

	typedef enum tagStandardErrorCodes
	{

		_E_ABORT                = ((result)0x80004004L),
		_E_ACCESSDENIED         = ((result)0x80070005L), 
		_E_FAIL                 = ((result)0x80004005L),
		_E_HANDLE               = ((result)0x80070006L), 
		_E_INVALIDARG           = ((result)0x80070057L), 
		_E_NOINTERFACE          = ((result)0x80004002L),
		_E_NOTIMPL              = ((result)0x80004001L), 
		_E_OUTOFMEMORY          = ((result)0x8007000EL),
		_E_PENDING              = ((result)0x8000000AL), 
		_E_POINTER              = ((result)0x80004003L), 
		_E_UNEXPECTED           = ((result)0x8000FFFFL), 
		_S_FALSE                = ((result)0x00000001L), 
		_S_OK                   = ((result)0x00000000L),
		_E_CANCELED             = ((result)0x80004FF1L)

	} StandardErrorCodes;

}

#endif // !CODES_H__MINCOM__COMMONKIT__INCLUDED_
