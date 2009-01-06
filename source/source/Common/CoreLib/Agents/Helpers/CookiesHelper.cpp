#include "Common/Common.h"

namespace MinCOM
{

	CookiesHelper::CookiesHelper()
		: cookies_()
	{
	}

	CookiesHelper::~CookiesHelper()
	{
	}

	// Public tools
	result CookiesHelper::Register(mc::ICommonRef connectee, unsigned long cookie)
	{
		cookies_.insert(CookiesPair_(connectee, cookie));
		return _S_OK;
	}

	result CookiesHelper::Unregister(mc::ICommonRef connectee)
	{
		if ( cookies_.find(connectee) == cookies_.end() )
			return _S_FALSE;
	
		cookies_.erase(connectee);
		return _S_OK;
	}

	unsigned long CookiesHelper::GetCookie(mc::ICommonRef connectee)
	{
		if ( cookies_.find(connectee) == cookies_.end() )
			return 0;

		return cookies_[connectee];
	}

}
