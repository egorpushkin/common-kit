#include "Common/Common.h"

namespace MinCOM
{

	// Constructors
	//////////////////////////////////////////////////////////////////////////

	// Default
	CommonVariant::CommonVariant()
		: vt_(CE_EMPTY)
	{
	}

	// Specific
	CommonVariant::CommonVariant(bool boolVal)		// CE_BOOL
		: vt_(CE_BOOL)
		, boolVal_(boolVal)
	{
	}	
	
	/*CommonVariant(short iVal);						// CE_I2
	CommonVariant(unsigned short uiVal);			// CE_UI2*/
	CommonVariant::CommonVariant(int intVal)		// CE_INT
		: vt_(CE_INT)
		, intVal_(intVal)
	{
	}
	CommonVariant::CommonVariant(unsigned int uintVal)			// CE_UINT
		: vt_(CE_UINT)
		, uintVal_(uintVal)
	{
	}
	
	CommonVariant::CommonVariant(long lVal)						// CE_I4
		: vt_(CE_UINT)
		, lVal_(lVal)
	{
	}

	CommonVariant::CommonVariant(unsigned long ulVal)				// CE_UI4
		: vt_(CE_UINT)
		, ulVal_(ulVal)
	{
	}	
	
	/*CommonVariant(longlong llval);					// CE_I8
	CommonVariant(ulonglong ullVal);				// CE_UI8*/
	
	CommonVariant::CommonVariant(float fltVal)		// CE_R4
		: vt_(CE_R8)
		, fltVal_(fltVal)
	{
	}

	CommonVariant::CommonVariant(double dblVal)		// CE_R8
		: vt_(CE_R8)
		, dblVal_(dblVal)
	{
	}

/*	CommonVariant::CommonVariant(size_t sizeVal)	// CE_SIZE
		: vt_(CE_SIZE)
		, sizeVal_(sizeVal)
	{
	} */

	CommonVariant::CommonVariant(bool* pboolVal)	// CE_BYREF | CE_BOOL
		: vt_(CE_BYREF | CE_BOOL)
		, pboolVal_(pboolVal)
	{
	}
	/*CommonVariant(short* piVal);					// CE_BYREF | CE_I2
	CommonVariant(unsigned short* puiVal);		    // CE_BYREF | CE_UI2
	CommonVariant(int* pintVal);					// CE_BYREF | CE_INT
	CommonVariant(unsigned int* puintVal);		    // CE_BYREF | CE_UINT
	CommonVariant(long* plVal);						// CE_BYREF | CE_I4
	CommonVariant(unsigned long* pulVal);			// CE_BYREF | CE_UI4
	CommonVariant(longlong* pllVal);				// CE_BYREF | CE_I8
	CommonVariant(ulonglong* pullVal);				// CE_BYREF | CE_UI8
	CommonVariant(float* pfltVal);					// CE_BYREF | CE_R4
	CommonVariant(double* pdblVal);					// CE_BYREF | CE_R8

	CommonVariant(char cVal);						// CE_C1
	CommonVariant(unsigned char ucVal);			    // CE_UC1
	CommonVariant(wchar_t wcVal);					// CE_WC2

	CommonVariant(char*	pcVal);						// CE_BYREF | CE_C1
	CommonVariant(unsigned char* pucVal);		    // CE_BYREF | CE_UC1
	CommonVariant(wchar_t* pwcVal);					// CE_BYREF | CE_WC1 */

	CommonVariant::CommonVariant(ICommon* pcmnVal)	// CE_BYPTR | CE_COMMON
		: vt_(CE_BYPTR | CE_COMMON)
		, pcmnVal_(pcmnVal)
	{
	}

/*	CommonVariant(ICommon** ppcmnVal);				// CE_BYREF | CE_COMMON

	CommonVariant(CommonVariant* pvarVal);		    // CE_BYREF | CE_VARIANT*/
	CommonVariant::CommonVariant(void* pvVal)		// CE_BYREF | CE_VOID
		: vt_(CE_BYREF | CE_VOID)
		, pvVal_(pvVal)
	{
	}
	/*CommonVariant(void** byref);					// Generic ByRef */

	CommonVariant::CommonVariant(const StringA& strVal) // CE_STRA
		: vt_(CE_STRA)
		, cmnVal_(ConstractWrapper(strVal))
	{
	}

	CommonVariant::CommonVariant(const StringW& strVal) // CE_STRW
		: vt_(CE_STRW)
		, cmnVal_(ConstractWrapper(strVal))
	{
	}

	/* CommonVariant(StringA* pstraVal);				// CE_BYREF | CE_STRA
	CommonVariant(StringW* pstrwVal);				// CE_BYREF | CE_STRW*/

	CommonVariant::CommonVariant(RefGuid guidVal)	// CE_GUID
		: vt_(CE_GUID)
		, guidVal_(guidVal)
	{
	}

	// Copy
	//CommonVariant(const CommonVariant* pSrc);
	CommonVariant::CommonVariant(const CommonVariant& varSrc)
	{
		*this = varSrc;
	}
	
	// Destructor
	//////////////////////////////////////////////////////////////////////////
	CommonVariant::~CommonVariant()
	{
	}





}
