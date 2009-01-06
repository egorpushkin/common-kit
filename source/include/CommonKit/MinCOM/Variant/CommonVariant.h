#ifndef COMMONVARIANT_H__MINCOM__INCLUDED_
#define COMMONVARIANT_H__MINCOM__INCLUDED_

namespace MinCOM
{

#ifdef _MSC_VER
	typedef __int64 longlong;
	typedef unsigned __int64 ulonglong;
#elif WIN32 // MinGW or something else	
#elif POSIX // any Posix macro
#elif __MACH__
	typedef long long longlong;
	typedef unsigned long long ulonglong;
#endif // _MSC_VER

	class CommonVariant
	{			
	public:

		enum Type_ 
		{
			// Inherited constants
			CE_WRONG = -1,
			CE_EMPTY = 0,
			CE_NULL = 1,
			CE_I2 = 2,
			CE_I4 = 3,
			CE_R4 = 4,
			CE_R8 = 5,
			CE_BOOL = 11,	
			CE_UI2 = 18,
			CE_UI4 = 19,
			CE_I8 = 20,
			CE_UI8 = 21,
			CE_INT = 22,
			CE_UINT = 23,
			CE_SIZE = 24,

			// Characters
			CE_C1 = 64,
			CE_UC1 = 65,
			CE_WC2 = 66,

			// Native OM support
			CE_COMMON = 68,

			// Strings
			CE_STR = 69,
			CE_STRA = 70,
			CE_STRW = 71,

			// Voids
			CE_VOID = 76,

			CE_GUID = 77,

			// Modifiers
			CE_BYREF = 0x4000,
			CE_BYPTR = 0x8000
		};
		
		// Constructors
		//////////////////////////////////////////////////////////////////////////
		// Default
		CommonVariant();

		// Specific
		CommonVariant(bool boolVal);					// CE_BOOL
		CommonVariant(short iVal);						// CE_I2
		CommonVariant(unsigned short uiVal);			// CE_UI2
		CommonVariant(int intVal);						// CE_INT
		CommonVariant(unsigned int uintVal);			// CE_UINT
		CommonVariant(long lVal);						// CE_I4
		CommonVariant(unsigned long ulVal);				// CE_UI4
		CommonVariant(longlong llval);					// CE_I8
		CommonVariant(ulonglong ullVal);				// CE_UI8
		CommonVariant(float fltVal);					// CE_R4
		CommonVariant(double dblVal);					// CE_R8
		//CommonVariant(size_t sizeVal);					// CE_SIZE

		CommonVariant(bool* pboolVal);					// CE_BYREF | CE_BOOL
		CommonVariant(short* piVal);					// CE_BYREF | CE_I2
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
		// CommonVariant(wchar_t wcVal);					// CE_WC2

		CommonVariant(char*	pcVal);						// CE_BYREF | CE_C1
		CommonVariant(unsigned char* pucVal);		    // CE_BYREF | CE_UC1
		//CommonVariant(wchar_t* pwcVal);					// CE_BYREF | CE_WC1

		CommonVariant(ICommon* pcmnVal);				// CE_BYPTR | CE_COMMON
		CommonVariant(ICommon** ppcmnVal);				// CE_BYREF | CE_COMMON

		template< class T >
		CommonVariant(const ComPtr< T >& ptr)			// CE_COMMON
			: vt_(CE_COMMON)
			, cmnVal_(ICommonPtr(ptr, IID_ICommon))
		{
		}

		CommonVariant(const ComPtr< ICommon >& ptr)		// CE_COMMON
			: vt_(CE_COMMON)
			, cmnVal_(ptr)
		{
		} 

		CommonVariant(CommonVariant* pvarVal);		    // CE_BYREF | CE_VARIANT
		CommonVariant(void* pvVal);						// CE_BYREF | CE_VOID
		CommonVariant(void** byref);					// Generic ByRef

		CommonVariant(const StringA& strVal);			// CE_STRA
		CommonVariant(const StringW& strVal);			// CE_STRW
		CommonVariant(StringA* pstraVal);				// CE_BYREF | CE_STRA
		CommonVariant(StringW* pstrwVal);				// CE_BYREF | CE_STRW

		CommonVariant(RefGuid guidVal);					// CE_GUID

		// Copy
		CommonVariant(const CommonVariant* pSrc);
		CommonVariant(const CommonVariant& varSrc);

		// Destructor
		//////////////////////////////////////////////////////////////////////////
		virtual ~CommonVariant();

		// Assignments
		//////////////////////////////////////////////////////////////////////////
/* 		const CommonVariant& operator=(const CommonVariant* pSrc);
		const CommonVariant& operator=(const CommonVariant& varSrc);		
		
/*		const CommonVariant& operator=(bool boolVal);					// CE_BOOL
		const CommonVariant& operator=(short iVal);						// CE_I2
		const CommonVariant& operator=(unsigned short uiVal);			// CE_UI2
		const CommonVariant& operator=(int intVal);						// CE_INT
		const CommonVariant& operator=(unsigned int uintVal);			// CE_UINT
		const CommonVariant& operator=(long lVal);						// CE_I4
		const CommonVariant& operator=(unsigned long ulVal);			// CE_UI4
		const CommonVariant& operator=(longlong llval);					// CE_I8
		const CommonVariant& operator=(unsigned longlong ullVal);		// CE_UI8
		const CommonVariant& operator=(float fltVal);					// CE_R4
		const CommonVariant& operator=(double dblVal);					// CE_R8

		const CommonVariant& operator=(bool* pboolVal);					// CE_BYREF | CE_BOOL
		const CommonVariant& operator=(short* piVal);					// CE_BYREF | CE_I2
		const CommonVariant& operator=(unsigned short* puiVal);		    // CE_BYREF | CE_UI2
		const CommonVariant& operator=(int* pintVal);					// CE_BYREF | CE_INT
		const CommonVariant& operator=(unsigned int* puintVal);		    // CE_BYREF | CE_UINT
		const CommonVariant& operator=(long* plVal);					// CE_BYREF | CE_I4
		const CommonVariant& operator=(unsigned long* pulVal);			// CE_BYREF | CE_UI4
		const CommonVariant& operator=(longlong* pllVal);				// CE_BYREF | CE_I8
		const CommonVariant& operator=(unsigned longlong* pullVal);		// CE_BYREF | CE_UI8
		const CommonVariant& operator=(float* pfltVal);					// CE_BYREF | CE_R4
		const CommonVariant& operator=(double* pdblVal);				// CE_BYREF | CE_R8

		const CommonVariant& operator=(char cVal);						// CE_C1
		const CommonVariant& operator=(unsigned char ucVal);			// CE_UC1
		const CommonVariant& operator=(wchar_t wcVal);					// CE_WC2

		const CommonVariant& operator=(char* pcVal);					// CE_BYREF | CE_C1
		const CommonVariant& operator=(unsigned char* pucVal);		    // CE_BYREF | CE_UC1
		const CommonVariant& operator=(wchar_t* pwcVal);				// CE_BYREF | CE_WC1

		const CommonVariant& operator=(ICommon* pcmnVal);				// CE_COMMON
		const CommonVariant& operator=(ICommon** ppcmnVal);				// CE_BYREF | CE_COMMON

		const CommonVariant& operator=(CommonVariant* pvarVal);		    // CE_BYREF | CE_VARIANT
		const CommonVariant& operator=(void* pvVal);					// CE_BYREF | CE_VOID
		const CommonVariant& operator=(void** byref);					// Generic ByRef

		const CommonVariant& operator=(String* pstrVal);				// CE_BYREF | CE_STR
		const CommonVariant& operator=(StringA* pstraVal);				// CE_BYREF | CE_STRA
		const CommonVariant& operator=(StringW* pstrwVal);				// CE_BYREF | CE_STRW */

		// Comparisons
		//////////////////////////////////////////////////////////////////////////
		bool operator==(const CommonVariant* pSrc) const;
		bool operator==(const CommonVariant& varSrc) const; 	

		// Operations
		//////////////////////////////////////////////////////////////////////////
		void Clear();
		
		void Convert(Type_ type, const CommonVariant* pSrc = NULL);
		Type_ GetType() const;
		
		void Attach(CommonVariant& varSrc);
		void Attach(CommonVariant* pSrc);
		CommonVariant Detach();

		/*
		template< class T >
		void SetValue(T value)
		{
			*this = CommonVariant(value);
		}

		template< class T >
		T Value();
		*/

		// Data modifiers
		//////////////////////////////////////////////////////////////////////////
		


		// Data accessors
		//////////////////////////////////////////////////////////////////////////
		bool toBool() const;							// CE_BOOL
		short toShort() const;                          // CE_I2
		unsigned short toUShort() const;                // CE_UI2
		int toInt() const;								// CE_INT
		unsigned int toUInt() const;                    // CE_UINT
		long toLong() const;                            // CE_I4
		unsigned long toULong() const;                  // CE_UI4
		longlong toLLong() const;                       // CE_I8
		ulonglong toULLong() const;						// CE_UI8
		float toFloat() const;							// CE_R4
		double toDouble() const;                        // CE_R8
		//size_t toSize() const;							// CE_SIZE

		bool* toPBool() const;							// CE_BYREF | CE_BOOL
		short* toPShort() const;				        // CE_BYREF | CE_I2
		unsigned short* toPUShort() const;			    // CE_BYREF | CE_UI2
		int* toPInt() const;							// CE_BYREF | CE_INT
		unsigned int* toPUInt() const;		            // CE_BYREF | CE_UINT
		long* toPLong() const;					        // CE_BYREF | CE_I4
		unsigned long* toPUlong() const;			    // CE_BYREF | CE_UI4
		longlong* toPLLong() const;				        // CE_BYREF | CE_I8
		ulonglong* toPULLong() const; 					// CE_BYREF | CE_UI8
		float* toPFloat() const;					    // CE_BYREF | CE_R4
		double* toPDouble() const;				        // CE_BYREF | CE_R8

		char toChar() const;					        // CE_C1
		unsigned char toUChar() const;			        // CE_UC1
		wchar_t toWChar() const;					    // CE_WC2

		char* toPChar() const;					        // CE_BYREF | CE_C1
		unsigned char* toPUchar() const;		        // CE_BYREF | CE_UC1
		wchar_t* toPWChar() const;						// CE_BYREF | CE_WC1

		ICommon* toPCommon() const;						// CE_COMMON
		ICommon** toPPCommon() const;					// CE_BYREF | CE_COMMON

		CommonVariant* toPVariant() const;			    // CE_BYREF | CE_VARIANT
		void* toPVoid() const;					        // CE_BYREF | CE_VOID
		void** toPPVoid() const;					    // Generic ByRef

		StringA toStringA() const;						// CE_STRA
		StringW toStringW() const;						// CE_STRW
		String* toPString() const;						// CE_BYREF | CE_STR
		StringA* toPStringA() const;					// CE_BYREF | CE_STRA
		StringW* toPStringW() const;					// CE_BYREF | CE_STRW		

		ICommonPtr toCommon() const;					// CE_BYPTR | CE_COMMON

		Guid toGuid() const;							// CE_GUID

		// Info
		//////////////////////////////////////////////////////////////////////////
		Type_ type() const;

	private:

		// Data
		//////////////////////////////////////////////////////////////////////////

		unsigned short vt_;
		unsigned short reserved1_;
		unsigned short reserved2_;
		unsigned short reserved3_;

		union 
		{

			bool				    boolVal_;           // CE_BOOL
			short                   iVal_;              // CE_I2
			unsigned short          uiVal_;             // CE_UI2
			int                     intVal_;            // CE_INT
			unsigned int            uintVal_;           // CE_UINT
			long                    lVal_;              // CE_I4
			unsigned long           ulVal_;             // CE_UI4
			longlong                llval_;             // CE_I8
			ulonglong				ullVal_;            // CE_UI8
			float                   fltVal_;            // CE_R4
			double                  dblVal_;            // CE_R8
			// size_t                  sizeVal_;           // CE_SIZE

			bool*					pboolVal_;          // CE_BYREF | CE_BOOL
			short*					piVal_;             // CE_BYREF | CE_I2
			unsigned short*			puiVal_;            // CE_BYREF | CE_UI2
			int*					pintVal_;           // CE_BYREF | CE_INT
			unsigned int*			puintVal_;          // CE_BYREF | CE_UINT
			long*					plVal_;             // CE_BYREF | CE_I4
			unsigned long*			pulVal_;            // CE_BYREF | CE_UI4
			longlong*				pllVal_;            // CE_BYREF | CE_I8
			ulonglong*				pullVal_;           // CE_BYREF | CE_UI8
			float*					pfltVal_;           // CE_BYREF | CE_R4
			double*					pdblVal_;           // CE_BYREF | CE_R8

			char					cVal_;              // CE_C1
			unsigned char			ucVal_;             // CE_UC1
			wchar_t					wcVal_;             // CE_WC2

			char*					pcVal_;             // CE_BYREF | CE_C1
			unsigned char*			pucVal_;            // CE_BYREF | CE_UC1
			wchar_t*				pwcVal_;			// CE_BYREF | CE_WC1

			ICommon*				pcmnVal_;			// CE_COMMON
			ICommon**				ppcmnVal_;			// CE_BYREF | CE_COMMON

			CommonVariant*			pvarVal_;           // CE_BYREF | CE_VARIANT
			void*					pvVal_;             // CE_BYREF | CE_VOID
			void**					byref_;             // Generic ByRef

			String*					pstrVal_;			// CE_BYREF | CE_STR
			StringA*				pstraVal_;			// CE_BYREF | CE_STRA
			StringW*				pstrwVal_;			// CE_BYREF | CE_STRW

			Guid					guidVal_;			// CE_GUID

		};

		ICommonPtr					cmnVal_;			// CE_BYPTR | CE_COMMON

	}; 

	typedef CommonVariant Variant;
	typedef CommonVariant::Type_ VariantType;

	// Single variant
	typedef Loki::SmartPtr< Variant > VariantPtr;	
	typedef const VariantPtr& VariantRef;	

	// Array of variants 
	typedef Loki::SmartPtr< 
		Variant,  
		Loki::RefCounted,
		Loki::DisallowConversion,
		Loki::AssertCheck,
		Loki::ArrayStorage
	> VariantArPtr;	

}

#endif // !COMMONVARIANT_H__MINCOM__INCLUDED_

