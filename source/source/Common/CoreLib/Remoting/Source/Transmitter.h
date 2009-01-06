#ifndef TRANSMITTER_H__REMOTING__CORELIB__INCLUDED_
#define TRANSMITTER_H__REMOTING__CORELIB__INCLUDED_

namespace Remoting
{

	class Transmitter
		: public mc::CommonImpl< ITransmitter >
	{
	public:

		Transmitter();

		// ICommon section
		DECLARE_INTERFACE_MAP()		

		// ITransmitter section
		virtual mc::result Transmit(
			Behaviour mode, 
			mc::ICommonRef object,
			Network::IClient::Id_ clientId,						
			IServerRef server,
			Network::IHostRef host);

		virtual mc::ICommonPtr Obtain(
			Behaviour mode, 
			void* ptr,
			Network::IClient::Id_ clientId,						
			IServerRef server,
			Network::IHostRef host);

	private:

		template 
		<
			class TMessage
		>
		mc::result ConnectToServer(
			Network::IHostRef host,
			void* ptr,
			Network::IClient::Id_ clientId, 			
			Network::IProtocolPtr& connectionHolder);

	};

}

#include "Transmitter_template.h"

#endif // !TRANSMITTER_H__REMOTING__CORELIB__INCLUDED_
