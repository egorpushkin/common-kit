#include "Common/Common.h"

#include "CommonKit/Components.h"

#include "CommonKit/Project.h"

namespace Components
{

	ComponentImpl::ComponentImpl(mc::RefIid typeIid, mc::RefIid iid)
		: mc::CommonImpl< IComponent >()
		, mc::CommonImpl< IInPlaceController >()
		, mc::APImpl()
		, typeIid_(typeIid)
		, iid_(iid)
		, compMng_()
	{
	}

	ComponentImpl::~ComponentImpl()
	{
	}

	// ICommon section
	BEGIN_INTERFACE_MAP(ComponentImpl)
		COMMON(IComponent)
		INTERFACE(IComponent)
		INTERFACE(IInPlaceController)
		IMPL(mc::APImpl)
	END_INTERFACE_MAP()

	// IComponent section
	mc::Iid ComponentImpl::GetTypeIid()
	{
		return typeIid_;
	}

	mc::Iid ComponentImpl::GetIid()
	{
		return iid_;
	}

	mc::ICommonPtr ComponentImpl::CreateObject(mc::RefClsid clsid)
	{
		try 
		{ 
			return mc::CreateObject(clsid); 
		} 
		catch ( ... ) 
		{
		}

		return NULL;
	}	

	bool ComponentImpl::CanProduce(mc::RefClsid clsid)
	{
		return mc::CanProduce(clsid); 
	}

	mc::result ComponentImpl::Lock(bool lock)
	{
		ObjCounter::Lock(lock);

		return mc::_S_OK;
	}

	mc::result ComponentImpl::SetCM(IComponentsManagerRef mc)
	{
		compMng_ = GetWeak(mc);
		
		return mc::_S_OK;
	}

	IComponentsManagerPtr ComponentImpl::GetCM()
	{
		return GetStrong(compMng_);
	}

	// IInPlaceController section
	mc::result ComponentImpl::SendUnloadRequest()
	{
		return mc::APImpl::SpreadBase(
			AGENTID_UNLOADME, 
			mc::CreateParams(mc::ItemImpl::GetLocal()));			// Param1: Component self
	}

	// Protected tools
	bool ComponentImpl::Register(mc::RefClsid clsid, mc::CommonFactory::Creator_ creator)
	{
		return mc::GetCommonFactory().Register(clsid, creator);

	}

}
