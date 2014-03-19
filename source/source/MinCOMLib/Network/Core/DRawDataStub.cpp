#include "Common/Common.h"

#include "DRawDataStub.h"

namespace MinCOM
{

	// {6CDDFFF2-BB87-4b28-983A-6C77928075A9}
	const Guid ConnectedFnIid =  
        { 0x6cddfff2, 0xbb87, 0x4b28, { 0x98, 0x3a, 0x6c, 0x77, 0x92, 0x80, 0x75, 0xa9 } };

	// {1C011B08-11BC-44c5-A3C8-FC6BB9893452}
	const Guid DataReceivedFnIid =  
        { 0x1c011b08, 0x11bc, 0x44c5, { 0xa3, 0xc8, 0xfc, 0x6b, 0xb9, 0x89, 0x34, 0x52 } };

	// {F925B1A6-9502-4b76-A599-1DC259769158}
	const Guid DisconnectedFnIid =  
        { 0xf925b1a6, 0x9502, 0x4b76, { 0xa5, 0x99, 0x1d, 0xc2, 0x59, 0x76, 0x91, 0x58 } };

	DRawDataStub::DRawDataStub()
		: CommonImpl< DRawData >()
	{
	}

	// DRawData section
	result DRawDataStub::Connected(IConnectionRef connection)
	{
		return Call::Make(
			CommonImpl< DRawData >::GetSelf(),
			ConnectedFnIid,
			connection).toLong();
	}

	result DRawDataStub::DataReceived(IConnectionRef connection)
	{
		return Call::Make(
			CommonImpl< DRawData >::GetSelf(),
			DataReceivedFnIid,
			connection).toLong();
	}

	result DRawDataStub::Disconnected(IConnectionRef connection)
	{
		return Call::Make(
			CommonImpl< DRawData >::GetSelf(),
			DisconnectedFnIid,
			connection).toLong();
	}

	// ICommon section
	result DRawDataStub::Invoke(const Call& call)
	{	
		DRawDataPtr events( CommonImpl< DRawData >::GetTarget() );
		if ( !events )
			return _E_CALLNOTARGET;

		if ( ConnectedFnIid == call.GetMethod() )
		{
			if ( call.GetArguments().size() < 1 )
				return _E_INVALIDARG;
			result code = events->Connected(call.GetArguments().at(0).toCommon());
			call.GetResults().clear();
			call.GetResults().push_back(code);
		}
		else if ( DataReceivedFnIid == call.GetMethod() )
		{
			if ( call.GetArguments().size() < 1 )
				return _E_INVALIDARG;
			result code = events->DataReceived(call.GetArguments().at(0).toCommon());
			call.GetResults().clear();
			call.GetResults().push_back(code);
		}
		else if ( DisconnectedFnIid == call.GetMethod() )
		{
			if ( call.GetArguments().size() < 1 )
				return _E_INVALIDARG;
			result code = events->Disconnected(call.GetArguments().at(0).toCommon());
			call.GetResults().clear();
			call.GetResults().push_back(code);
		}

		return _S_OK;
	}

}
