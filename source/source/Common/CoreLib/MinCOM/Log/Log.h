#ifndef LOG_H__MINCOM__CORELIB__INCLUDED_
#define LOG_H__MINCOM__CORELIB__INCLUDED_

namespace MinCOM
{

	class Log 
		: public CommonImpl< ILog >
	{
	public:

		Log();
		virtual ~Log();

		// ICommon section
		DECLARE_INTERFACE_MAP()		

		// ILog section
		virtual result Notify(const String& message);
		
	};

	// External tools
	ILogPtr InstantiateLog();

}

#endif // !LOG_H__MINCOM__CORELIB__INCLUDED_
