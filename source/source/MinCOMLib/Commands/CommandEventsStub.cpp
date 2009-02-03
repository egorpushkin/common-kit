#include "Common/Common.h"

#include "CommandEventsStub.h"

namespace MinCOM
{

	typedef result ( CommandEventsStub::*pfnModifiedChanged(bool) );

	// {D4EEA1E5-161E-4643-B658-CED5E6B5B96A}
	const Guid TypeInfo< pfnModifiedChanged >::iid_ =  
		{ 0xd4eea1e5, 0x161e, 0x4643, 0xb6, 0x58, 0xce, 0xd5, 0xe6, 0xb5, 0xb9, 0x6a };

	CommandEventsStub::CommandEventsStub()
		: CommonImpl< ICommandEvents >()
	{
	}

	// ICommandEvents section
	result CommandEventsStub::ModifiedChanged(bool modified)
	{
		ICommonPtr events = CommonImpl< ICommandEvents >::GetTarget();
		if ( !events )
			return _E_NOTINIT;

		CallData call;
		call.SetMethod( TypeInfo< pfnModifiedChanged >::GetGuid() );
		call.GetArguments().push_back(modified);
		events->Invoke(call);		
		if ( call.GetResults().size() > 0 )
			return call.GetResults().at(0).toLong();
		return _S_OK;
	}

	// ICommon section
	result CommandEventsStub::Invoke(const CallData& call)
	{	
		ICommandEventsPtr events( CommonImpl< ICommandEvents >::GetTarget() );
		if ( !events )
			return _E_NOTINIT;

		if ( TypeInfo< pfnModifiedChanged >::GetGuid() == call.GetMethod() )
		{
			result code = events->ModifiedChanged(call.GetArguments().at(0).toBool());
			call.GetResults().push_back(code);
		}
		
		return _S_OK;
	}

}
