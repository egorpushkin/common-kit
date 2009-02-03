#include "Common/Common.h"

namespace MinCOM
{

	CallData::CallData()
		: methodIid_()
		, arguments_()
		, results_()
	{
	}

	void CallData::SetMethod(RefIid methodIid) const
	{
		methodIid_ = methodIid;
	}

	RefIid CallData::GetMethod() const
	{
		return methodIid_;
	}

	Variants& CallData::GetArguments() const
	{
		return arguments_;
	}

	Variants& CallData::GetResults() const
	{
		return results_;
	}

	// CommonVariant& CallData::GetResult()
	// {
	//	return result_;
	// }

}
