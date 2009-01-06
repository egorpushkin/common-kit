#ifndef ACCESSPOINTIMPL_H__MINCOM__COMMONKIT__INCLUDED_
#define ACCESSPOINTIMPL_H__MINCOM__COMMONKIT__INCLUDED_

namespace MinCOM
{

	class AccessPointImpl 
		: public CommonImpl< IAccessPoint >
	{
	public:

		AccessPointImpl();
		virtual ~AccessPointImpl();

		// IAccessPoint section
		virtual result GetAccessId(Iid& iid);

		virtual IAccessProviderPtr GetAccessProvider();

		virtual result Advise(ICommonRef sink, unsigned long& cookie);

		virtual result Unadvise(unsigned long cookie);

		virtual ICommonPtr Query(unsigned long cookie);

		virtual IAccessEntriesEnumPtr GetPointsEnum();

		// ICommon section
		DECLARE_INTERFACE_MAP()		

	protected:

		virtual unsigned long GenerateUniqueCookie(ICommonRef sink);

	private:

		IAccessEntriesPtr accessEntries_;


	};

}

#endif // !ACCESSPOINTIMPL_H__MINCOM__COMMONKIT__INCLUDED_
