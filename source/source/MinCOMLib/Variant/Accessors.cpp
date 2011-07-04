#include "Common/Common.h"

namespace MinCOM
{

	bool CommonVariant::toBool() const				// CE_BOOL
	{
		return boolVal_;
	}

	
	short CommonVariant::toShort() const            // CE_I2
    {
        return iVal_;
    }
	
    unsigned short CommonVariant::toUShort() const  // CE_UI2
    {
        return uiVal_;
    }
    
	int CommonVariant::toInt() const				// CE_INT
	{
		return intVal_;
	}

	unsigned int CommonVariant::toUInt() const      // CE_UINT
	{
		return uintVal_;
	}

	long CommonVariant::toLong() const              // CE_I4
	{
		return lVal_;
	}

	unsigned long CommonVariant::toULong() const    // CE_UI4
	{
		return ulVal_;
	}
	
	longlong CommonVariant::toLLong() const         // CE_I8
    {
        return llVal_;
    }
    
	ulonglong CommonVariant::toULLong() const		// CE_UI8
    {
        return ullVal_;
    }
	
	float CommonVariant::toFloat() const			// CE_R4
	{
		return fltVal_;
	}

	double CommonVariant::toDouble() const          // CE_R8
	{
		return dblVal_;
	}

	/* size_t CommonVariant::toSize() const			// CE_SIZE
	{
		return sizeVal_;
	} */

/*	char toChar() const;					        // CE_C1 */
	unsigned char CommonVariant::toUChar() const    // CE_UC1
	{
		return ucVal_;
	}
/*	wchar_t toWChar() const;					    // CE_WC2 */

	std::string CommonVariant::toString() const		// CE_STRA
	{
		if ( vt_ != CE_STRA )
			return std::string();
		return Unwrap< std::string >(cmnVal_);
	}

	std::wstring CommonVariant::toWString() const		// CE_STRW
	{
		if ( vt_ != CE_STRW )
			return std::wstring();

		return Unwrap< std::wstring >(cmnVal_);
	}

	ICommonPtr CommonVariant::toCommon() const		// CE_COMMON
	{
		if ( CE_COMMON != vt_ )
			return ICommonPtr();

		return cmnVal_;
	}

	Guid CommonVariant::toGuid() const				// CE_GUID
	{
		return guidVal_;
	}

	// Info
	//////////////////////////////////////////////////////////////////////////
	CommonVariant::Type_ CommonVariant::GetType() const
	{
		return (CommonVariant::Type_)vt_;
	}

}
