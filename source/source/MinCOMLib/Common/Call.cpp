#include "Common/Common.h"

namespace MinCOM
{

	Call::Call()
		: methodIid_()
		, arguments_()
		, results_()
	{
	}

	Call::Call(RefIid methodIid)
		: methodIid_(methodIid)
		, arguments_()
		, results_()
	{
	}

	void Call::SetMethod(RefIid methodIid) const
	{
		methodIid_ = methodIid;
	}

	RefIid Call::GetMethod() const
	{
		return methodIid_;
	}

	Variants& Call::GetArguments() const
	{
		return arguments_;
	}

	Variants& Call::GetResults() const
	{
		return results_;
	}

	mc::Variant Call::Make(ICommonRef invoker, RefIid methodId, const Variant& arg1)
	{
		Call call(methodId);
		call.GetArguments().push_back( arg1 );
		return Make(invoker, call);
	}

	mc::Variant Call::Make(ICommonRef invoker, RefIid methodId, const Variant& arg1, const Variant& arg2)
	{
		Call call(methodId);
		call.GetArguments().push_back( arg1 );
		call.GetArguments().push_back( arg2 );
		return Make(invoker, call);
	}

	mc::Variant Call::Make(ICommonRef invoker, const Call& call)
	{
		// Try to acquire call target.
		ICommonPtr target = invoker->GetTarget();
		if ( !target )
			return Variant(_E_CALLNOTARGET);

		// Make synchronous call.
		target->Invoke(call);

		// Check whether any result is returned.
		if ( call.GetResults().size() > 0 )
			return call.GetResults().at(0);
		return Variant(_S_OK);
	}


}
