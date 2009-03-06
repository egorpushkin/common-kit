/*
 * File name   : CommonVariant.h
 *
 * Copyright (c) 2008 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-01-26  Egor Pushkin        Initial version
 */

#ifndef COMMONVARIANT_H__MINCOM__INCLUDED_
#define COMMONVARIANT_H__MINCOM__INCLUDED_

namespace MinCOM
{

#if defined(_MSC_VER)
	typedef __int64 longlong;
	typedef unsigned __int64 ulonglong;
#elif defined(__MINGW32__ ) // MinGW
        typedef long long longlong;
        typedef unsigned long long ulonglong;
#elif defined(POSIX) // any Posix macro
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
			CE_GUID = 77,
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

		CommonVariant(char cVal);						// CE_C1
		CommonVariant(unsigned char ucVal);			    // CE_UC1

		template< class T >
		CommonVariant(const Strong< T >& ptr)			// CE_COMMON
			: vt_(CE_COMMON)
			, cmnVal_(ptr)
		{
		}

		CommonVariant(const std::string& strVal);		// CE_STRA
		CommonVariant(const std::wstring& strVal);		// CE_STRW

		CommonVariant(RefGuid guidVal);					// CE_GUID

		// Assignments
		//////////////////////////////////////////////////////////////////////////
		/*
			template
			<
				class T
			>
			const CommonVariant& operator=(T val)
			{
				CommonVariant temp(val);
				std::swap(temp, *this);
				return *this;
			}
		*/

		// Comparisons
		//////////////////////////////////////////////////////////////////////////
		bool operator==(const CommonVariant* pSrc) const;
		bool operator==(const CommonVariant& varSrc) const; 	

		// Operations
		//////////////////////////////////////////////////////////////////////////
		void Clear();
		void Convert(Type_ type, const CommonVariant* pSrc = NULL);
		void Attach(CommonVariant& varSrc);
		void Attach(CommonVariant* pSrc);
		CommonVariant Detach();

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
		//size_t toSize() const;						// CE_SIZE

		char toChar() const;					        // CE_C1
		unsigned char toUChar() const;			        // CE_UC1
		wchar_t toWChar() const;					    // CE_WC2

		std::string toString() const;					// CE_STRA
		std::wstring toWString() const;					// CE_STRW

		ICommonPtr toCommon() const;					// CE_BYPTR | CE_COMMON

		Guid toGuid() const;							// CE_GUID

		// Info
		//////////////////////////////////////////////////////////////////////////
		Type_ GetType() const;

	private:

		/** Value representing data type. */
		unsigned short vt_;
	
		// Data fields
		//////////////////////////////////////////////////////////////////////////

		/** Union to store possible data fields. */
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

			char					cVal_;              // CE_C1
			unsigned char			ucVal_;             // CE_UC1
			wchar_t					wcVal_;             // CE_WC2

			Guid					guidVal_;			// CE_GUID
		};

		ICommonPtr					cmnVal_;			// CE_BYPTR | CE_COMMON

	}; 

	typedef CommonVariant::Type_ VariantType;

}

#endif // !COMMONVARIANT_H__MINCOM__INCLUDED_
