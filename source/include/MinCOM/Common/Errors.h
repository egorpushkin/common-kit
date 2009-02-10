/*
 * File name   : Errors.h
 *
 * Copyright (c) 2009 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-01-23  Egor Pushkin        Initial version
 */

#ifndef ERRORS_H__MINCOM__INCLUDED_
#define ERRORS_H__MINCOM__INCLUDED_

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
		_FACILITY_ICOMMON           = 2,
		_FACILITY_CONFIGURATION     = 33,
		_FACILITY_BACKGROUNDCOPY    = 32
	};

	/**
	 * Class to provide set of most common operations over error codes.
	 */
	class Error
	{
	public:

		static result MakeResult(result severity, result facility, result code);
		
		static result ResultCode(result status); 
			// ((status) & 0xFFFF)
		
		static result ResultFacility(result status); 
			// (((status) >> 16) & 0xff)
		
		static result ResultSeverity(result status); 
			// (((status) >> 31) & 0x1)
		
		static bool IsError(result status); 
			// ((unsigned long)(status) >> 31 == SEVERITY_ERROR)
		
		static bool IsSucceeded(result status);
			// ((long)(status) >= 0)

		static bool IsFailed(result status);
			// ((long)(Status) < 0)

	};

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
		_E_NOTINIT              = ((result)0x80004002L), 
		_E_ALREADYINIT          = ((result)0x80004003L), 
		_E_OUTOFMEMORY          = ((result)0x8007000EL),
		_E_PENDING              = ((result)0x8000000AL), 
		_E_POINTER              = ((result)0x80004003L), 
		_E_UNEXPECTED           = ((result)0x8000FFFFL),

		/** Invalid call target is specified. */
		_E_CALLNOTARGET         = ((result)0x81000001L),

		_S_FALSE                = ((result)0x00000001L), 
		_S_OK                   = ((result)0x00000000L),
		_E_CANCELED             = ((result)0x80004FF1L)

	} StandardErrorCodes;

	/** 
	 * Class to store and provide access to last occurred error. 
	 * The class should be implemented in thread safe manner.
	 * Client software should not use this tool to modify last error.
	 */ 
	class LastError
	{
	public:
	
		/**
		 * Gets error code.
		 */
		static result Get();

		/**
		 * Sets error code. Client code should not refer to this function.
		 */
		static void Set(result code);

	private:

		/**
		 * Thread dependent errors storage. 
		 * This member should not be static due to the fact that this brings 
		 * to its instantiation each time when Errrs.obj/.a is included into
		 * an assembly. This causes fake memory leak if leak detection tool 
		 * performs check at the end of main() routine, because static objects
		 * are not yet removed by that time.
		 */
		// static std::map< long, result > errorCode_;

	};

}

#endif // !ERRORS_H__MINCOM__INCLUDED_
