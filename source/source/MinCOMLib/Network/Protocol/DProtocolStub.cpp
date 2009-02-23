#include "Common/Common.h"

#include "DProtocolStub.h"

namespace MinCOM
{

	// {8C7AE980-AD27-4186-94B3-2C59CCAFEA1F}
	const Guid MessageArrivedFnIid = 
		{ 0x8c7ae980, 0xad27, 0x4186, 0x94, 0xb3, 0x2c, 0x59, 0xcc, 0xaf, 0xea, 0x1f };

	// {B33B6778-B6AC-46e3-832A-432ABF0CAFF9}
	const Guid DataErrorOccuredFnIid =  
		{ 0xb33b6778, 0xb6ac, 0x46e3, 0x83, 0x2a, 0x43, 0x2a, 0xbf, 0xc, 0xaf, 0xf9 };

	// {F650A3D0-2721-44c6-A9C2-0FAE47196C30}
	const Guid ProtocolDisconnectedFnIid =
		{ 0xf650a3d0, 0x2721, 0x44c6, 0xa9, 0xc2, 0xf, 0xae, 0x47, 0x19, 0x6c, 0x30 };

	DProtocolStub::DProtocolStub()
		: CommonImpl< DProtocol >()
	{
	}

	// DServer section
	result DProtocolStub::MessageArrived(IProtocolRef protocol, IMessageRef message)
	{
		return Call::Make(
			CommonImpl< DProtocol >::GetSelf(),
			MessageArrivedFnIid,
			protocol, message).toLong();
	}

	result DProtocolStub::DataErrorOccured(IProtocolRef protocol)
	{
		return Call::Make(
			CommonImpl< DProtocol >::GetSelf(),
			DataErrorOccuredFnIid,
			protocol).toLong();
	}

	result DProtocolStub::Disconnected(IProtocolRef protocol)
	{
		return Call::Make(
			CommonImpl< DProtocol >::GetSelf(),
			ProtocolDisconnectedFnIid,
			protocol).toLong();
	}
	
	// ICommon section
	result DProtocolStub::Invoke(const Call& call)
	{	
		DProtocolPtr events( CommonImpl< DProtocol >::GetTarget() );
		if ( !events )
			return _E_CALLNOTARGET;

		if ( MessageArrivedFnIid == call.GetMethod() )
		{
			if ( call.GetArguments().size() < 2 )
				return _E_INVALIDARG;
			result code = events->MessageArrived(
				call.GetArguments().at(0).toCommon(), 
				call.GetArguments().at(1).toCommon());
			call.GetResults().clear();
			call.GetResults().push_back(code);
		}
		else if ( DataErrorOccuredFnIid == call.GetMethod() )
		{
			if ( call.GetArguments().size() < 1 )
				return _E_INVALIDARG;
			result code = events->DataErrorOccured(
				call.GetArguments().at(0).toCommon());
			call.GetResults().clear();
			call.GetResults().push_back(code);
		}
		else if ( ProtocolDisconnectedFnIid == call.GetMethod() )
		{
			if ( call.GetArguments().size() < 1 )
				return _E_INVALIDARG;
			result code = events->Disconnected(
				call.GetArguments().at(0).toCommon());
			call.GetResults().clear();
			call.GetResults().push_back(code);
		}

		return _S_OK;
	}

}
