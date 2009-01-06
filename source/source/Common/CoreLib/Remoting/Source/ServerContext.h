#ifndef SERVERCONTEXT_H__REMOTING__CORELIB__INCLUDED_
#define SERVERCONTEXT_H__REMOTING__CORELIB__INCLUDED_

namespace Remoting
{

	class ServerContext
		: public mc::AgentImpl
	{
	public:

		ServerContext();

		// IAgent section
		virtual mc::result Invoke(mc::DispId idMember, mc::DispParamsRef dispParams, mc::IVariantWrapperRef result, mc::RefIid iid);

	private:

		Network::IServerPtr server_;

	};

}

#endif // !SERVERCONTEXT_H__REMOTING__CORELIB__INCLUDED_
