/*
 * File name   : AccessProviderImpl.h
 *
 * Copyright (c) 2009 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-01-30  Egor Pushkin        Initial version
 */

#ifndef ACCESSPROVIDERIMPL_H__MINCOM__INCLUDED_
#define ACCESSPROVIDERIMPL_H__MINCOM__INCLUDED_

namespace MinCOM
{

	class AccessProviderImpl 
		: public CommonImpl< IAccessProvider >
	{
	public:

		typedef std::map< Guid, IAccessPointPtr > AccessPoints_;

	public:

		AccessProviderImpl();

		// IAccessProvider section
		virtual result Advise(RefIid iid, IAccessPointRef accessPoint);

		virtual result Unadvise(RefIid iid);

		virtual IAccessPointPtr Find(RefIid iid);

		// Public events tools
		// static result SpreadEventCore(IAccessEntriesEnumRef entries, DispSpreader& spreader);

	protected:

		// Protected tools
		// IAccessPointPtr GetAccessPoint(RefIid iid = mc::IID_IAgent);
		
		// IAccessEntriesEnumPtr GetAccessEntries(RefIid iid = mc::IID_IAgent);

		// result RegisterAccessPoint(RefIid iid, bool replace = true);

	protected:

		// Protected events tools
		/* template 
		< typename Spreader >
		result SpreadEvent(DispId id, mc::DispParamsRef params, RefIid iid = mc::IID_IAgent)
		{
			Spreader spreader(id, params);
			return SpreadEventCore(GetAccessEntries(iid), spreader);	
		}

		result SpreadBase(DispId id, mc::DispParamsRef params, RefIid iid = mc::IID_IAgent); */

	private:
		
		CoreMutex lock_;

		AccessPoints_ accessPoints_;

	};

	typedef AccessProviderImpl APImpl;

}

#endif // !ACCESSPROVIDERIMPL_H__MINCOM__INCLUDED_
