#ifndef ACCESSPROVIDERIMPL_H__MINCOM__COMMONKIT__INCLUDED_
#define ACCESSPROVIDERIMPL_H__MINCOM__COMMONKIT__INCLUDED_

namespace MinCOM
{

	class AccessProviderImpl 
		: public CommonImpl< IAccessProvider >
		, public ItemImpl
	{
	public:

		AccessProviderImpl(bool regDefault = true);
		virtual ~AccessProviderImpl();

		// IAccessProvider section
		virtual result AdviseAccessPoint(RefIid iid, IAccessPointRef accessPoint, bool replace);

		virtual result UnadviseAccessPoint(RefIid iid);

		virtual result FindAccessPoint(RefIid iid, IAccessPointPtr& accessPoint);

		// ICommon section
		DECLARE_INTERFACE_MAP()		

		// Public events tools
		static result SpreadEventCore(IAccessEntriesEnumRef entries, DispSpreader& spreader);

	protected:

		// Protected tools
		IAccessPointPtr GetAccessPoint(RefIid iid = mc::IID_IAgent);
		
		IAccessEntriesEnumPtr GetAccessEntries(RefIid iid = mc::IID_IAgent);

		result RegisterAccessPoint(RefIid iid, bool replace = true);

	protected:

		// Protected events tools
		template 
		< typename Spreader >
		result SpreadEvent(DispId id, mc::DispParamsRef params, RefIid iid = mc::IID_IAgent)
		{
			Spreader spreader(id, params);
			return SpreadEventCore(GetAccessEntries(iid), spreader);	
		}

		result SpreadBase(DispId id, mc::DispParamsRef params, RefIid iid = mc::IID_IAgent);

	private:

		IAccessPointsPtr accessPoints_;

	};

	typedef AccessProviderImpl APImpl;

}

#endif // !ACCESSPROVIDERIMPL_H__MINCOM__COMMONKIT__INCLUDED_
