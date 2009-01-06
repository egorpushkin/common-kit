#include "Common/Common.h"

#include "MsgDeliveryJob.h"

namespace Network
{

	MsgDeliveryJob::MsgDeliveryJob()
		: mc::AgentImpl()
	{
	}

	// IAgent section
	mc::result MsgDeliveryJob::Invoke(mc::DispId idMember, mc::DispParamsRef dispParams, mc::IVariantWrapperRef /* result */, mc::RefIid /* iid */)
	{		

		if ( idMember == Components::AGENTID_MAINJOBCALL )
		{
			// Accept params
			if ( dispParams->GetCount() < 2 )
				return mc::_E_FAIL;

			IProtocolPtr protocol(dispParams->Get(1)->toCommon(), IID_IProtocol);
			IMessagePtr message(dispParams->Get(0)->toCommon(), IID_IMessage);

			if ( !protocol || !message )
				return mc::_E_FAIL;

			// Spread message to all subscribers
			return protocol->Spread(message);
		}

		return mc::_S_OK;
	}

}
