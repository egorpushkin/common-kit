#ifndef SERVER_H__REMOTING__CORELIB__INCLUDED_
#define SERVER_H__REMOTING__CORELIB__INCLUDED_

namespace Remoting
{

	class Server 
		: public mc::CommonImpl< IServer >
		, public mc::CommonImpl< IServerInternal >
		, public mc::AgentImpl
		, public mc::ItemImpl
	{
	public:

		Server();
		
		virtual ~Server();

		// ICommon section
		DECLARE_INTERFACE_MAP()		

		// IServer section
		virtual mc::result Run(Network::IHostRef host);

		// IServerInternal section
		virtual mc::result RunPassive();

		virtual mc::result RegisterStub(IStubRef stub);

		virtual mc::result AttachObject(void* id, Network::IClient::Id_ clientId, mc::ICommonRef object);

		virtual mc::ICommonPtr RemitProxy(void* id, Network::IClient::Id_ clientId);

		virtual Network::IClient::Id_ GenerateUniqueClientId();

		// IAgent section
		virtual mc::result Invoke(mc::DispId idMember, mc::DispParamsRef dispParams, mc::IVariantWrapperRef result, mc::RefIid iid);

	private:

		mc::IMutexPtr lock_;

		Network::IServerPtr server_;

		typedef std::vector< IStubPtr > StubsList_;

		StubsList_ stubs_;

		typedef enum tagMode_
		{

			UNDEFINED_ = 0x0,

			ACTIVE_ = 0x1,

			PASSIVE_ = 0x2

		}
		Mode_;

		Mode_ mode_;

		typedef std::pair< void*, Network::IClient::Id_ > ObjectKey_;
		
		typedef std::multimap< ObjectKey_, mc::ICommonPtr > TransmittedObjects_;

		TransmittedObjects_ transmittedObjects_;

		Components::IJobsQueuePtr acceptJobs_;

		mc::IThreadPtr localLauncher_;

		mc::IAgentPtr launcherContext_;

	};

	typedef Loki::SingletonHolder
	<
		mc::CommonHolder< Server >
	> 
	ServerHolder;

	IServerPtr GetGlobalServer();

}

#endif // !SERVER_H__REMOTING__CORELIB__INCLUDED_
