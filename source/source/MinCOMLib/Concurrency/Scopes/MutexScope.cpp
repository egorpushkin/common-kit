#include "Common/Common.h"

namespace MinCOM
{

	MutexScope::MutexScope(IMutexRef mutex)
		: mutex_(mutex)
	{
		if ( mutex_ )
			mutex_->Wait();
	}

	MutexScope::~MutexScope()
	{
		if ( !mutex_ )
			return;
		mutex_->Release();
	}

}
