#include "Common/Common.h"

#include "DProtocolStub.h"

namespace MinCOM
{

	// {8C7AE980-AD27-4186-94B3-2C59CCAFEA1F}
	const Guid MessageArrivedFnIid = 
		{ 0x8c7ae980, 0xad27, 0x4186, 0x94, 0xb3, 0x2c, 0x59, 0xcc, 0xaf, 0xea, 0x1f };

	DProtocolStub::DProtocolStub()
		: CommonImpl< DProtocol >()
	{
	}

	// DServer section
	result DProtocolStub::MessageArrived(IMessageRef message)
	{
		return Call::Make(
			CommonImpl< DProtocol >::GetSelf(),
			MessageArrivedFnIid,
			message).toLong();
	}
	
	// ICommon section
	result DProtocolStub::Invoke(const Call& call)
	{	
		DProtocolPtr events( CommonImpl< DProtocol >::GetTarget() );
		if ( !events )
			return _E_CALLNOTARGET;

		if ( MessageArrivedFnIid == call.GetMethod() )
		{
			if ( call.GetArguments().size() < 1 )
				return _E_INVALIDARG;
			result code = events->MessageArrived(call.GetArguments().at(0).toCommon());
			call.GetResults().clear();
			call.GetResults().push_back(code);
		}
	
		return _S_OK;
	}

}
