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

		virtual result Spread(const Call& call);

	protected:

		/**
		 * Tool provided for convenience. Use this tool if you are not going to 
		 * override default IAccessPoint behavior.
		 *
		 * @return Returns reference to events spreader associated with newly 
		 * created access point.
		 */
		ICommonPtr Advise(RefIid eventsIid);

		/**
		 * Wraps call to Advise tool and throws exception if the operation fails.
		 * The need of this tool is caused by desire to make PostInit call simpler
		 * and to avoid additional checks. Developer should not explicitly perform
		 * exception handling because this is done by MinCOM (see Class.h for
		 * details).
		 */
		ICommonPtr AdviseAndThrow(RefIid eventsIid);


	private:

		AccessPoints_ accessPoints_;

	};

	typedef AccessProviderImpl APImpl;

}

#endif // !ACCESSPROVIDERIMPL_H__MINCOM__INCLUDED_
