#include "Common/Common.h"

#include "DServerStub.h"

namespace MinCOM
{

	// {F0492CB0-92F2-4e74-8666-EFFD54B20BC4}
	const Guid ConnectionAcceptedFnIid =  
		{ 0xf0492cb0, 0x92f2, 0x4e74, 0x86, 0x66, 0xef, 0xfd, 0x54, 0xb2, 0xb, 0xc4 };

	DServerStub::DServerStub()
		: CommonImpl< DServer >()
	{
	}

	// DServer section
	result DServerStub::ConnectionAccepted(IConnectionRef connection)
	{
		return Call::Make(
			CommonImpl< DServer >::GetSelf(),
			ConnectionAcceptedFnIid,
			connection).toLong();
	}
	
	// ICommon section
	result DServerStub::Invoke(const Call& call)
	{	
		DServerPtr events( CommonImpl< DServer >::GetTarget() );
		if ( !events )
			return _E_CALLNOTARGET;

		if ( ConnectionAcceptedFnIid == call.GetMethod() )
		{
			if ( call.GetArguments().size() < 1 )
				return _E_INVALIDARG;
			result code = events->ConnectionAccepted(call.GetArguments().at(0).toCommon());
			call.GetResults().clear();
			call.GetResults().push_back(code);
		}
	
		return _S_OK;
	}

}
