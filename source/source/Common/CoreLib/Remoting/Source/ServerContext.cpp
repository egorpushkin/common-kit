#include "Common/Common.h"

#include "ServerContext.h"

#include "Remoting/Interfaces/Common.h"

#include "Remoting/Interfaces/IStub.h"

#include "Remoting/Interfaces/IServerInternal.h"

namespace Remoting
{

	ServerContext::ServerContext()
		: mc::AgentImpl()
		, server_()
	{
	}

	// IAgent section
	mc::result ServerContext::Invoke(mc::DispId idMember, mc::DispParamsRef dispParams, mc::IVariantWrapperRef /* result */, mc::RefIid /* iid */)
	{		
		if ( mc::AGENTID_MAINCTXCALL == idMember )
		{
			server_ = Network::IServerPtr(dispParams->Get(0)->toCommon(), Network::IID_IServer);
			if ( !server_ )
				return mc::_E_FAIL;

			server_->Run();
		} 
		else if ( AGENTID_STOPSERVICE == idMember )
		{
			if ( !server_ )
				return mc::_E_FAIL;

			server_->Stop();
		}

		return mc::_S_OK;
	}

}
