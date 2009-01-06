#include "Common/Common.h"

namespace MinCOM
{

	DispParamsPtr CreateParamsCore(unsigned int count)
	{
		return DispParamsPtr(new DispParams(count));
	}

	DispParams::DispParams(unsigned int count)
		: vararg_()
		, countArgs_(count)
	{		
		if ( countArgs_ > 0 )
			vararg_ = VariantArPtr(new Variant[countArgs_]);
	}

	result DispParams::Set(unsigned int index, const Variant& param)
	{
		if ( index >= countArgs_ )
			return _E_INVALIDARG;

		GetImpl(vararg_)[index] = param;

		return _S_OK;
	}

	Variant* DispParams::Get(unsigned int index)
	{
		if ( index >= countArgs_ )
			return NULL;

		return &GetImpl(vararg_)[index];
	}

	Variant& DispParams::GetRef(unsigned int index)
	{
		if ( index >= countArgs_ )
			throw std::out_of_range("Invalid argument index");

		return GetImpl(vararg_)[index];
	}

	unsigned int DispParams::GetCount()
	{
		return countArgs_;
	}

	IVariantWrapperPtr ConstructVariantWrapper()
	{
		return IVariantWrapperPtr(ConstractWrapper< IVariantWrapperPtr::Type_::Type_ >(), IID_IWrapper);
	}

}
