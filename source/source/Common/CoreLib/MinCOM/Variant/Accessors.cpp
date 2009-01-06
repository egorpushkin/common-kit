#include "Common/Common.h"

namespace MinCOM
{

	bool CommonVariant::toBool() const				// CE_BOOL
	{
		return boolVal_;
	}

	
/*	short toShort() const;                          // CE_I2
	unsigned short toUShort() const;                // CE_UI2*/
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


	
	/*	longlong toLLong() const;                       // CE_I8
	ulonglong toULLong() const;						// CE_UI8 */
	
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

	bool* CommonVariant::toPBool() const			// CE_BYREF | CE_BOOL
	{
		return pboolVal_;
	}
/*	short* toPShort() const;				        // CE_BYREF | CE_I2
	unsigned short* toPUShort() const;			    // CE_BYREF | CE_UI2
	int* toPInt() const;							// CE_BYREF | CE_INT
	unsigned int* toPUInt() const;		            // CE_BYREF | CE_UINT
	long* toPLong() const;					        // CE_BYREF | CE_I4
	unsigned long* toPUlong() const;			    // CE_BYREF | CE_UI4
	longlong* toPLLong() const;				        // CE_BYREF | CE_I8
	ulonglong* toPULLong() const; 					// CE_BYREF | CE_UI8
	float* toPFloat() const;					    // CE_BYREF | CE_R4 */
	
	double* CommonVariant::toPDouble() const		// CE_BYREF | CE_R8
	{
		return pdblVal_;
	}

/*	char toChar() const;					        // CE_C1
	unsigned char toUChar() const;			        // CE_UC1
	wchar_t toWChar() const;					    // CE_WC2

	char* toPChar() const;					        // CE_BYREF | CE_C1
	unsigned char* toPUchar() const;		        // CE_BYREF | CE_UC1
	wchar_t* toPWChar() const;						// CE_BYREF | CE_WC1*/

	ICommon* CommonVariant::toPCommon() const		// CE_BYPTR | CE_COMMON
	{
		return ( ( CE_BYPTR | CE_COMMON ) == vt_) ? ( pcmnVal_ ) : ( NULL );
	}

/*	ICommon** toPPCommon() const;					// CE_BYREF | CE_COMMON

	CommonVariant* toPVariant() const;			    // CE_BYREF | CE_VARIANT*/
	void* CommonVariant::toPVoid() const			// CE_BYREF | CE_VOID
	{
		return pvVal_;
	}
/*	void** toPPVoid() const;					    // Generic ByRef */

	StringA CommonVariant::toStringA() const		// CE_STRA
	{
		if ( vt_ != CE_STRA )
			return StringA();

		return Unwrap< StringA >(cmnVal_);
	}

	StringW CommonVariant::toStringW() const		// CE_STRW
	{
		if ( vt_ != CE_STRW )
			return StringW();

		return Unwrap< StringW >(cmnVal_);
	}
	
	/* String* toPString() const;						// CE_BYREF | CE_STR
	StringA* toPStringA() const;					// CE_BYREF | CE_STRA
	StringW* toPStringW() const;					// CE_BYREF | CE_STRW	*/

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
	CommonVariant::Type_ CommonVariant::type() const
	{
		return (CommonVariant::Type_)vt_;
	}

}
