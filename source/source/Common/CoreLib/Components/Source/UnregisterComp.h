#ifndef UNREGISTERCOMP_H__COMPONENTS__CORELIB__INCLUDED_
#define UNREGISTERCOMP_H__COMPONENTS__CORELIB__INCLUDED_

namespace Components
{

	class UnregisterComp
		: public mc::AgentImpl
	{
	public:

		UnregisterComp();
		virtual ~UnregisterComp();

		// IAgent section
		virtual mc::result Invoke(mc::DispId idMember, mc::DispParamsRef dispParams, mc::IVariantWrapperRef result, mc::RefIid iid);

	};

}

#endif // !UNREGISTERCOMP_H__COMPONENTS__CORELIB__INCLUDED_