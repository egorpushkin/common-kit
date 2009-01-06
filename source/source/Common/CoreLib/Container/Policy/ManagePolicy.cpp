#include "Common/Common.h"

#include "CommonKit/Container.h"

namespace Container
{

	// Managed Policy :: Private
	//////////////////////////////////////////////////////////////////////////
	namespace Private
	{

		ContainerSpreader::ContainerSpreader(mc::DispId id, mc::DispParamsRef params)
			: mc::DispSpreader(id, params)
		{
		}

		bool ContainerSpreader::operator()(mc::AccessEntryPair sinkPair)
		{
			//DContainerEventsPtr events(mc::ICommonPtr(sinkPair.second), DIID_DContainerEvents);
			DContainerEventsPtr events(GetStrong(sinkPair.second), DIID_DContainerEvents);
			if ( events )
			{
				mc::result code = mc::_E_INVALIDARG;

				if ( mc::DispSpreader::id_ == AGENTID_ADDELEMENT )
				{
					code = events->OnAddElement(
						params_->Get(1)->toPVoid(),
						params_->Get(0)->toPBool()
					);
				}
				else if ( mc::DispSpreader::id_ == AGENTID_DELETEELEMENT )
				{
					code = events->OnDeleteElement(
						params_->Get(2)->toPVoid(),
						params_->Get(1)->toInt(),
						params_->Get(0)->toPBool()
					);
				}

				mc::DispSpreader::SetLastError(code);

				return true;
			}

			return mc::DispSpreader::operator()(sinkPair);
		}

	}

	// Managed Policy
	//////////////////////////////////////////////////////////////////////////
	mc::result Managed::OnAddElement(void* const pData, bool* pCancel)
	{
		return mc::APImpl::SpreadEvent< Private::ContainerSpreader >(
			AGENTID_ADDELEMENT, mc::CreateParams(pData, pCancel));
	}

	mc::result Managed::OnDeleteElement(void* const pData, int index, bool* pCancel)
	{
		return mc::APImpl::SpreadEvent< Private::ContainerSpreader >(
			AGENTID_DELETEELEMENT, mc::CreateParams(pData, index, pCancel));
	}

	// Unmanaged policy
	//////////////////////////////////////////////////////////////////////////
	mc::result Unmanaged::OnAddElement(void* const /* pData */, bool* /* pCancel */)
	{
		return mc::_S_OK;
	}

	mc::result Unmanaged::OnDeleteElement(void* const /* pData */, int /* index */, bool* /* pCancel */)
	{
		return mc::_S_OK;
	}

}
