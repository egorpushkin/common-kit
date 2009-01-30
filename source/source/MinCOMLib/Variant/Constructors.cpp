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

	/*
	CommonVariant(char cVal);						// CE_C1
	CommonVariant(unsigned char ucVal);			    // CE_UC1
	CommonVariant(wchar_t wcVal);					// CE_WC2

	CommonVariant(char*	pcVal);						// CE_BYREF | CE_C1
	CommonVariant(unsigned char* pucVal);		    // CE_BYREF | CE_UC1
	CommonVariant(wchar_t* pwcVal);					// CE_BYREF | CE_WC1 */

	CommonVariant::CommonVariant(const std::string& strVal) // CE_STRA
		: vt_(CE_STRA)
		, cmnVal_(Wrap(strVal))
	{
	}

	CommonVariant::CommonVariant(const std::wstring& strVal) // CE_STRW
		: vt_(CE_STRW)
		, cmnVal_(Wrap(strVal))
	{
	}

	/* CommonVariant(StringA* pstraVal);				// CE_BYREF | CE_STRA
	CommonVariant(StringW* pstrwVal);				// CE_BYREF | CE_STRW*/

	CommonVariant::CommonVariant(RefGuid guidVal)	// CE_GUID
		: vt_(CE_GUID)
		, guidVal_(guidVal)
	{
	}

}
