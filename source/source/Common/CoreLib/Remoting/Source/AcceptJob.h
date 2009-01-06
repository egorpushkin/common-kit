#ifndef ACCEPTJOB_H__REMOTING__CORELIB__INCLUDED_
#define ACCEPTJOB_H__REMOTING__CORELIB__INCLUDED_

namespace Remoting
{

	class AcceptJob
		: public mc::AgentImpl
	{
	public:

		AcceptJob();

		// IAgent section
		virtual mc::result Invoke(mc::DispId idMember, mc::DispParamsRef dispParams, mc::IVariantWrapperRef result, mc::RefIid iid);

	private:

		mc::result HandleAccept(Remoting::IServerInternalRef serverInternal, Network::IClientRef client);

	};

}

#endif // !ACCEPTJOB_H__REMOTING__CORELIB__INCLUDED_
