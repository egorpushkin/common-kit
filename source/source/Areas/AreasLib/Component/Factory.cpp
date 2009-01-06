#include "Common/Common.h"

#include "Project/AProject.h"

namespace MinCOM
{

	result ConfigureFactory(CommonFactory* pFactory)
	{
		pFactory->Register(Areas::CLSID_AreasProject, mc::ObjectCreator< Areas::AProject >);

		return _S_OK;
	}

}
