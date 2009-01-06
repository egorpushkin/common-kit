#ifndef STRINGS_H__MINCOM__COMMONKIT__INCLUDED_
#define STRINGS_H__MINCOM__COMMONKIT__INCLUDED_

#if defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#endif

namespace MinCOM
{

#ifdef _UNICODE

	#define _S(x) L##x
	typedef wchar_t Char;

#else // _UNICODE

	#define _S(x) x
	typedef char Char;

#endif // _UNICODE

	typedef Char* lptstr; // LPTSTR
	typedef const Char* lpctstr; // LPCTSTR

	// Multi-byte string macros
	typedef char* lpstr; // LPSTR
	typedef const char* lpcstr; // LPCSTR

	// Unicode string macros
	typedef wchar_t* lpwstr; // LPWSTR
	typedef const wchar_t* lpcwstr; // LPCUSTR

	// Declaring object model main string container
	typedef std::basic_string< Char > String;
	typedef std::basic_string< char > StringA;
	typedef std::basic_string< wchar_t > StringW;
	
	// Pointers
	typedef Loki::SmartPtr< String > StringPtr;
	typedef const StringPtr& StringRef;

	// Strong array of strings
	typedef Loki::SmartPtr< 
		String,  
		Loki::RefCounted,
		Loki::DisallowConversion,
		Loki::AssertCheck,
		Loki::ArrayStorage
	> StringArPtr;	
	
	typedef const StringArPtr& StringArRef;

}

#endif // !STRINGS_H__MINCOM__COMMONKIT__INCLUDED_
