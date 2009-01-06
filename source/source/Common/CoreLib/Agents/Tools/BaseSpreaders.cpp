#include "Common/Common.h"

namespace MinCOM
{

	DispSpreader::DispSpreader(DispId id, DispParamsRef params)
		: lastError_(_S_OK)
		, id_(id)
		, params_(params)
	{
	}

	void DispSpreader::SetLastError(result code)
	{
		if ( IsFailed(code) )
			lastError_ = code;
	}

	result DispSpreader::GetLastError() const
	{
		return lastError_;
	}

	bool DispSpreader::operator()(AccessEntryPair sinkPair)
	{
		// Construct strong pointer first
		//ICommonPtr strongSink(sinkPair.second);
		ICommonPtr strongSink = GetStrong(sinkPair.second);
		if ( !strongSink )
			return true;

		IAgentPtr agent(strongSink, IID_IAgent);
		if ( !agent )
			return true;

		mc::result code = agent->Invoke(id_, params_);
		SetLastError(code);

		return true;
	}

}