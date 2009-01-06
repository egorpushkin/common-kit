#ifndef COOKIESHELPER_H__AGENTS__COMMONKIT__INCLUDED_
#define COOKIESHELPER_H__AGENTS__COMMONKIT__INCLUDED_

namespace MinCOM
{

	class CookiesHelper
	{
	protected:

		CookiesHelper();
		virtual ~CookiesHelper();

		// Public tools
		result Register(mc::ICommonRef connectee, unsigned long cookie);
	
		result Unregister(mc::ICommonRef connectee);

		unsigned long GetCookie(mc::ICommonRef connectee);

	private:

		// Cookies container
		typedef std::pair< ICommonPtr, unsigned long > CookiesPair_;
		typedef std::map< CookiesPair_::first_type, CookiesPair_::second_type > CookiesMap_;
		CookiesMap_ cookies_;

	};

}

#endif // !COOKIESHELPER_H__AGENTS__COMMONKIT__INCLUDED_
