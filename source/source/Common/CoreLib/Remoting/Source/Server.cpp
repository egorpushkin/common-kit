#include "Common/Common.h"

#include "Remoting/Interfaces/Common.h"

#include "Remoting/Interfaces/IStub.h"

#include "Remoting/Interfaces/IServerInternal.h"

#include "Remoting/Interfaces/IProxy.h"

#include "Server.h"

#include "Remoting/Interfaces/ITransmitter.h"

#include "Stub.h"

#include "Remoting/Tools/Factory.h"

#include "AcceptJob.h"

#include "Remoting/Source/ServerContext.h"

namespace Remoting
{

	Server::Server()
		: mc::CommonImpl< IServer >()
		, mc::CommonImpl< IServerInternal >()
		, mc::AgentImpl()
		, mc::ItemImpl()
		, lock_(mc::InstantiateMutex())
		, server_()
		, stubs_()
		, mode_(PASSIVE_)
		, transmittedObjects_()
		, acceptJobs_()
		, localLauncher_()
		, launcherContext_()
	{
	}

	Server::~Server()
	{
		if ( localLauncher_ && launcherContext_ )
		{
			launcherContext_->Invoke(AGENTID_STOPSERVICE);					
			localLauncher_->Join();
		}
	}

	// ICommon section
	BEGIN_INTERFACE_MAP(Server)
		COMMON(IServer)
		INTERFACE(IServer)
		INTERFACE(IServerInternal)
		IMPL(mc::AgentImpl)
		IMPL(mc::ItemImpl)
	END_INTERFACE_MAP()		

	// IServer section
	mc::result Server::Run(Network::IHostRef host)
	{
		mc::MutexLock lock(lock_);

		if ( server_ )
			return mc::_E_FAIL;

		mode_ = ACTIVE_;

		// Instantiate server
		server_ = Network::InstantiateServer();
		acceptJobs_ = Components::InstantiateJobsQueue();

		// Attach to server's notifications
		unsigned long cookie = 0;
		mc::Advise(mc::ICommonPtr(server_, mc::IID_ICommon), mc::ItemImpl::GetLocal(), cookie);

		// Configure accept jobs processing engine
		acceptJobs_->Start();

		// Configure and start server
		server_->AsyncAccept(host->GetPort());
		server_->Run();

		server_ = NULL;
		mode_ = UNDEFINED_;

		return mc::_S_OK;
	}

	// IServerInternal section
	mc::result Server::RunPassive()
	{
		mc::MutexLock lock(lock_);

		if ( server_ )
			return mc::_E_FAIL;

		mode_ = PASSIVE_;

		// Instantiate server
		server_ = Network::InstantiateServer();

		localLauncher_ = mc::InstantiateThread();
		launcherContext_ = mc::InstantiateAgent< ServerContext >();
		localLauncher_->SetContext(
			launcherContext_,
			mc::CreateParams(server_)
		);
		localLauncher_->Start();

		server_ = NULL;
		mode_ = UNDEFINED_;
		
		return mc::_S_OK;
	}

	mc::result Server::RegisterStub(IStubRef stub)
	{
		stubs_.push_back(stub);

		return mc::_S_OK;
	}

	mc::result Server::AttachObject(void* id, Network::IClient::Id_ clientId, mc::ICommonRef object)
	{
		transmittedObjects_.insert(
			TransmittedObjects_::value_type(
				ObjectKey_(id, clientId), object));

		return mc::_S_OK;
	}

	mc::ICommonPtr Server::RemitProxy(void* id, Network::IClient::Id_ clientId)
	{
		TransmittedObjects_::iterator proxyPos = transmittedObjects_.find(ObjectKey_(id, clientId));
		if ( transmittedObjects_.end() == proxyPos )
			return NULL;

		mc::ICommonPtr localProxy = (*proxyPos).second;

		transmittedObjects_.erase(proxyPos);

		return localProxy;
	}

	Network::IClient::Id_ Server::GenerateUniqueClientId()
	{
		Network::IClient::Id_ clientId = 1;

		StubsList_::const_iterator iter = stubs_.begin();
		StubsList_::const_iterator end = stubs_.end();

		for ( ; iter != end ; ++iter )
		{
			if ( (*iter)->GetClientId() >= clientId )
				++clientId;
		}

		return clientId;
	}

	// IAgent section
	mc::result Server::Invoke(mc::DispId idMember, mc::DispParamsRef dispParams, mc::IVariantWrapperRef /* result */, mc::RefIid /* iid */)
	{
		if ( idMember == Network::AGENTID_ACCEPT )
		{
			if ( PASSIVE_ == mode_ )
				return mc::_S_FALSE;				

			// Get connection gateway 
			Network::IClientPtr client(dispParams->Get(0)->toCommon(), Network::IID_IClient);
			if ( !client )
				return mc::_E_FAIL;

			// Start new job
			acceptJobs_->Push(
				mc::InstantiateAgent< AcceptJob >(),
				mc::CreateParams(
					mc::ItemImpl::GetLocal(), // Param 1: Remoting::Server
					client // Param 2: Network::Client
				)
			);
		}

		return mc::_S_OK;
	}

	// External tools
	IServerPtr InstantiateServer()
	{
		return IServerPtr(mc::ObjectCreator< Server >(), IID_IServer);
	}

	// Holder tools
	IServerPtr GetGlobalServer()
	{
		return IServerPtr(ServerHolder::Instance().GetInstance(), IID_IServer);
	}

}
