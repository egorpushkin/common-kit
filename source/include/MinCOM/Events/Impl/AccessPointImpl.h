/*
 * File name   : AccessPointImpl.h
 *
 * Copyright (c) 2009 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-01-30  Egor Pushkin        Initial version
 */

#ifndef ACCESSPOINTIMPL_H__MINCOM__INCLUDED_
#define ACCESSPOINTIMPL_H__MINCOM__INCLUDED_

namespace MinCOM
{

	class AccessPointImpl 
		: public CommonImpl< IAccessPoint >
	{
	public:

		typedef std::map< unsigned long, ICommonWeak > AccessEntries_;

	public:

		AccessPointImpl(RefGuid iid);

		// IAccessPoint section
		virtual Iid GetIid();

		virtual IAccessProviderPtr GetAccessProvider();

		virtual result Advise(ICommonRef sink, unsigned long& cookie);

		virtual result Unadvise(unsigned long cookie);

		virtual ICommonPtr Find(unsigned long cookie);

	private:

		CoreMutex lock_;

		Guid iid_;

		AccessEntries_ accessEntries_;

	};

}

#endif // !ACCESSPOINTIMPL_H__MINCOM__INCLUDED_
