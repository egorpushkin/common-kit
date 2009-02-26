/*
 * File name   : AccessPointImpl.h
 *
 * Copyright (c) 2009 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-01-30  Egor Pushkin        Initial version
 */

#ifndef ACCESSPOINTIMPL_H__MINCOMLIB__INCLUDED_
#define ACCESSPOINTIMPL_H__MINCOMLIB__INCLUDED_

namespace MinCOM
{

	class AccessPointImpl 
		: public CommonImpl< IAccessPoint >
	{
	public:

		typedef std::map< unsigned long, ICommonWeak > AccessEntries_;

	public:

		AccessPointImpl(IAccessProviderRef accessProvider, RefGuid iid);

		// IAccessPoint section
		virtual IAccessProviderPtr GetAccessProvider();

		virtual Iid GetIid();

		virtual result Advise(ICommonRef sink, unsigned long& cookie);

		virtual result Unadvise(unsigned long cookie);

		virtual result Unadvise(ICommonRef sink);

		virtual ICommonPtr Find(unsigned long cookie);

		virtual ICommonPtr CreateSpreader();

		virtual result Spread(const Call& call);

	protected:

		result NotifySinkOnEvent(ICommonRef stub, ICommonRef sink, const Call& call);

		result UnadviseInternl(unsigned long cookie);

	private:

		IAccessProviderWeak accessProvider_;

		Guid iid_;

		AccessEntries_ accessEntries_;

		bool spreading_;

		std::set< unsigned long > pendingRemoval_;

	};

}

#endif // !ACCESSPOINTIMPL_H__MINCOMLIB__INCLUDED_
