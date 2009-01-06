#ifndef MESSAGESMAP_H__REMOTING__COMMONKIT__INCLUDED_
#define MESSAGESMAP_H__REMOTING__COMMONKIT__INCLUDED_

namespace Remoting
{

	class MessagesMap
	{
	public:

		static Network::IProtocolPtr InstantiateProtocol();

		static mc::IFactoryPtr Prepare();

		static mc::result Configure(Network::IProtocolRef protocol);

	private:

		static mc::result Configure(mc::IFactoryRef messagesMap);

	};

}

#endif // !MESSAGESMAP_H__REMOTING__COMMONKIT__INCLUDED_
