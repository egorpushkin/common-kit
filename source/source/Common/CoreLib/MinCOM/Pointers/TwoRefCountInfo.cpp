#include "Common/Common.h"

// #include <fstream>

namespace MinCOM
{
	
	TwoRefCountInfo::TwoRefCountInfo( bool strong )
		: Loki::Private::TwoRefCountInfo(strong)
	{
		/* std::ofstream ofs("e:\\temp.txt", std::ios_base::out | std::ios_base::app);		
		if ( ofs.bad() || !ofs.is_open() )
			return;

		ofs << "11" << std::endl; */
	}

	TwoRefCountInfo::~TwoRefCountInfo()
	{
		/* std::ofstream ofs("e:\\temp.txt", std::ios_base::out | std::ios_base::app);		
		if ( ofs.bad() || !ofs.is_open() )
			return;

		ofs << "22" << std::endl; */
	}

	TwoRefCountInfo* TwoRefCountInfo::Create( bool strong )  
	{
		return new TwoRefCountInfo( strong );
	}

	void TwoRefCountInfo::Release( TwoRefCountInfo* info ) 
	{
		info->DoRelease();
	}

	void TwoRefCountInfo::DoRelease()
	{
		delete this;
	}

}
