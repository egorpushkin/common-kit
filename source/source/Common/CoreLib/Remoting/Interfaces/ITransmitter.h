#ifndef ITRANSMITTER_H__REMOTING__COMMONKIT__INCLUDED_
#define ITRANSMITTER_H__REMOTING__COMMONKIT__INCLUDED_

namespace Remoting
{

	interface ITransmitter : public mc::ICommon
	{

		virtual mc::result Transmit(
			Behaviour mode, 
			mc::ICommonRef object,
			Network::IClient::Id_ clientId,						
			IServerRef server,
			Network::IHostRef host) = 0;

		virtual mc::ICommonPtr Obtain(
			Behaviour mode, 
			void* ptr,
			Network::IClient::Id_ clientId,						
			IServerRef server,
			Network::IHostRef host) = 0;

	};

	typedef mc::ComPtr< ITransmitter > ITransmitterPtr;
	typedef const ITransmitterPtr& ITransmitterRef;

	// {51cda09f-473e-44fb-a84c-1a7dc1c986ce} 
	MC_DEFINE_GUID(IID_ITransmitter, 
	0x51cda09f, 0x473e, 0x44fb, 0xa8, 0x4c, 0x1a, 0x7d, 0xc1, 0xc9, 0x86, 0xce);

}

#endif // !ITRANSMITTER_H__REMOTING__COMMONKIT__INCLUDED_
