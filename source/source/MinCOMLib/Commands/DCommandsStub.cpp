#include "Common/Common.h"

#include "DCommandsStub.h"

namespace MinCOM
{

	// {D4EEA1E5-161E-4643-B658-CED5E6B5B96A}
	const Guid ModifiedChangedFnIid =  
		{ 0xd4eea1e5, 0x161e, 0x4643, 0xb6, 0x58, 0xce, 0xd5, 0xe6, 0xb5, 0xb9, 0x6a };

	DCommandsStub::DCommandsStub()
		: CommonImpl< DCommands >()
	{
	}

	// ICommandEvents section
	result DCommandsStub::ModifiedChanged(bool modified)
	{
		return Call::Make(
			CommonImpl< DCommands >::GetSelf(), 
			ModifiedChangedFnIid, 
			modified).toLong();
	}

	// ICommon section
	result DCommandsStub::Invoke(const Call& call)
	{	
		DCommandsPtr events( CommonImpl< DCommands >::GetTarget() );
		if ( !events )
			return _E_NOTINIT;

		if ( ModifiedChangedFnIid == call.GetMethod() )
		{
			result code = events->ModifiedChanged(call.GetArguments().at(0).toBool());
			call.GetResults().push_back(code);
		}
		
		return _S_OK;
	}

}
