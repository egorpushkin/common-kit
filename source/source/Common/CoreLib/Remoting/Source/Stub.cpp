#include "Common/Common.h"

#include "Remoting/Interfaces/Common.h"

#include "Remoting/Interfaces/ITransmitter.h"

#include "Remoting/Interfaces/IStub.h"

#include "Stub.h"

#include "Remoting/Interfaces/IServerInternal.h"

#include "Remoting/Messages/MessagesMap.h"

#include "Remoting/Messages/Codes.h"

#include "Transmitter.h"

// Messages
#include "Remoting/Messages/Codes.h"
#include "Remoting/Interfaces/IInvokeMsg.h"
#include "Remoting/Messages/InvokeRespMsg.h"

namespace Remoting
{

	Stub::Stub()
		: mc::CommonImpl< IStub >()
		, mc::AgentImpl()
		, mc::ItemImpl()
		, lock_(mc::InstantiateMutex())
		, mode_(UNDEFINED)
		, transmitter_(mc::ObjectCreator< Transmitter >(), IID_ITransmitter)
		, protocol_()
		, clientId_(0)
		, targetCommon_()
		, host_()
	{
	}

	// ICommon section
	BEGIN_INTERFACE_MAP(Stub)
		COMMON(IStub)
		INTERFACE(IStub)
		IMPL(mc::AgentImpl)
		IMPL(mc::ItemImpl)
	END_INTERFACE_MAP()	

	// IStub section
	mc::result Stub::Initialize(Network::IProtocolRef protocol, Network::IClient::Id_ clientId, mc::RefClsid objId)
	{
		return Initialize(
			protocol,
			clientId,
			InstantiateFromId(objId),
			SERVER_SIDE,
			NULL);	
	}

	mc::result Stub::Initialize(Network::IProtocolRef protocol, Network::IClient::Id_ clientId, mc::ICommonRef target, Behaviour mode, Network::IHostRef host)
	{
		mc::MutexLock lock(lock_);

		if ( protocol_ || !protocol || !target )
			return mc::_E_FAIL;

		protocol_ = protocol;

		clientId_ = clientId;

		host_ = host;

		targetCommon_ = target;

		// Configure gateway to async 'on data' notifications 
		unsigned long cookie = 0;
		mc::Advise(mc::ICommonPtr(protocol_, mc::IID_ICommon), mc::ItemImpl::GetLocal(), cookie);

		// Start receiving messages
		protocol_->SetMode(Network::PROTOCOL_ASYNC);

		mode_ = mode;

		return mc::_S_OK;
	}

	Network::IClient::Id_ Stub::GetClientId()
	{
		return clientId_;
	}
	
	// IAgent section
	mc::result Stub::Invoke(mc::DispId idMember, mc::DispParamsRef dispParams, mc::IVariantWrapperRef /* result */, mc::RefIid iid)
	{
		mc::MutexLock lock(lock_);

		if ( Network::AGENTID_MESSAGE == idMember )
		{
			if ( !dispParams || dispParams->GetCount() != 3 )
				return mc::_E_FAIL;

			Network::IMessagePtr msg(dispParams->Get(0)->toCommon(), Network::IID_IMessage);
			if ( !msg )
				return mc::_E_FAIL;

			if ( MSGCODE_INVOKE != msg->GetCode() )
				return mc::_S_FALSE;

			// Prepare call target
			mc::IAgentPtr targetAgent = PrepareCallTarget(iid);
			if ( !targetAgent )
				return mc::_E_FAIL;

			IInvokeMsgPtr invokeMsg(msg, IID_IInvokeMsg);
			if ( !invokeMsg )
				return mc::_E_FAIL;

			mc::DispId invokeIdMember = msg->GetProperty(MSGPROP_DISPID).toLong();
			mc::DispParamsRef invokeDispParams = invokeMsg->GetParams();

			// Correct references to transmitted objects
			unsigned int paramsCount = 0;
			if ( invokeDispParams )
				paramsCount = invokeDispParams->GetCount();
			for ( unsigned int i = 0 ; i < paramsCount ; ++i )
			{
				if ( ( mc::Variant::CE_BYPTR | mc::Variant::CE_COMMON ) == invokeDispParams->GetRef(i).type() )
				{
					// Object found. It must be requested from server. Transmitter is responsible for this operation.
					invokeDispParams->GetRef(i) = mc::Variant(
						transmitter_->Obtain(
							mode_, 
							invokeDispParams->GetRef(i).toPCommon(),
							clientId_,
							IServerPtr(mc::ItemImpl::GetParent(), IID_IServer),
							host_));				
				}
			}
			
			mc::IVariantWrapperPtr invokeResultWrapper = mc::ConstructVariantWrapper();
			if ( !invokeResultWrapper )
				return mc::_E_FAIL;

			// Perform call
			mc::result code = targetAgent->Invoke(invokeIdMember, invokeDispParams, invokeResultWrapper);

			// Analise result 
			if ( mc::Variant::CE_COMMON == invokeResultWrapper->GetData().type() )
			{
				// Returned object must be passed to caller. Transmitter is responsible for this operation.
				if ( mc::IsFailed(transmitter_->Transmit(
					mode_,
					invokeResultWrapper->GetData().toCommon(),
					clientId_,
					IServerPtr(mc::ItemImpl::GetParent(), IID_IServer),
					host_)) )
					code = mc::_E_FAIL;
			}

			// Send response
			Network::IMessagePtr invokeRespMsg(mc::ObjectCreator< InvokeRespMsg >(code, invokeResultWrapper->GetData()), Network::IID_IMessage);
			if ( mc::IsFailed(protocol_->Send(invokeRespMsg)) )
				return mc::_E_FAIL;
		}

		return mc::_S_OK;
	}

	// Requests
	mc::ICommonPtr Stub::InstantiateFromId(mc::RefClsid objId)
	{
		// Try to instantiate first from registered objects
		mc::IItemPtr serverItem(mc::ItemImpl::GetParent(), mc::IID_IItem);
		if ( serverItem )
		{
			mc::ICommonPtr target = serverItem->Acquire(objId);
			if ( target )
				return target;		
		}

		// Finally try to instantiate in regular way
		return Components::InstantiateCommon(objId); 
	}

	// Tools
	mc::IAgentPtr Stub::PrepareCallTarget(mc::RefIid iid)
	{
		mc::ICommonPtr targetCommon = targetCommon_;

/*
		mc::ICommonPtr targetCommon = mc::ItemImpl::Acquire(iid);
		if ( targetCommon )
		{
			targetCommon = Components::InstantiateCommon(iid);
			if ( !targetCommon )
			{
				targetCommon = targetCommon_;
			}
			else
			{
				mc::ItemImpl::Attach(iid, targetCommon);
			}
		}
*/

		return mc::IAgentPtr(targetCommon, mc::IID_IAgent);
	}

}
