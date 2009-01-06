#include "Common/Common.h"

namespace MinCOM
{

	FactoryImpl::FactoryImpl()
		: CommonImpl< IFactory >()
		, creators_()
	{
	}

	// ICommon section
	BEGIN_INTERFACE_MAP(FactoryImpl)
		COMMON(IFactory)
		INTERFACE(IFactory)
	END_INTERFACE_MAP()

	// IFactory section
	ICommonPtr FactoryImpl::Create(DispId id)
	{
		CreatorsCIter_ iter = creators_.find(id);
		if ( iter == creators_.end() )
			return NULL;

		return (*((*iter).second))();
	}

	result FactoryImpl::Register(DispId id, FactoryCreator creator)
	{
		creators_.insert(CreatorPair_(id, creator));

		return _S_OK;
	}

	result FactoryImpl::Unregister(DispId id)
	{
		if ( creators_.find(id) == creators_.end() )
			return _S_FALSE;
			
		creators_.erase(id);

		return _S_OK;
	}

	bool FactoryImpl::IsSupported(DispId id)
	{
		CreatorsCIter_ iter = creators_.find(id);

		return ( iter != creators_.end() );
	}		

	// External tools
	IFactoryPtr InstantiateFactory()
	{
		return IFactoryPtr(ObjectCreator< FactoryImpl >(), IID_IFactory);
	}

}


