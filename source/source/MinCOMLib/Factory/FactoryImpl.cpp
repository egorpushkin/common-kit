#include "Common/Common.h"

namespace MinCOM
{

	FactoryImpl::FactoryImpl()
		: CommonImpl< IFactory >()
		, creators_()
	{
	}

	// IFactory section
	ICommonPtr FactoryImpl::Create(KeyRef_ id)
	{
		CreatorsCIter_ iter = creators_.find(id);
		if ( iter == creators_.end() )
			return NULL;

		return (*((*iter).second))();
	}

	result FactoryImpl::Register(KeyRef_ id, Creator_ creator)
	{
		creators_.insert(CreatorPair_(id, creator));

		return _S_OK;
	}

	result FactoryImpl::Unregister(KeyRef_ id)
	{
		if ( creators_.find(id) == creators_.end() )
			return _S_FALSE;
			
		creators_.erase(id);

		return _S_OK;
	}

	bool FactoryImpl::IsSupported(KeyRef_ id)
	{
		CreatorsCIter_ iter = creators_.find(id);

		return ( iter != creators_.end() );
	}		

}


