#ifndef MSGDELIVERYJOB_H__NETWORK__CORELIB__INCLUDED_
#define MSGDELIVERYJOB_H__NETWORK__CORELIB__INCLUDED_

namespace Network
{

	class MsgDeliveryJob
		: public mc::AgentImpl
	{
	public:

		MsgDeliveryJob();

		// IAgent section
		virtual mc::result Invoke(mc::DispId idMember, mc::DispParamsRef dispParams, mc::IVariantWrapperRef result, mc::RefIid iid);

	};

}

#endif // !MSGDELIVERYJOB_H__NETWORK__CORELIB__INCLUDED_
