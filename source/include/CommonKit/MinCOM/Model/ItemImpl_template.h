namespace MinCOM
{

	template 
	< class T >
	result ItemImpl::SetParent(const T& item, ICommonRef parent)
	{
		if ( !item )
			return _E_INVALIDARG;
	
		IItemPtr pointItem(item, IID_IItem);
		if ( !pointItem )
			return mc::_E_FAIL;
		
		pointItem->SetParent(parent);

		return _S_OK;
	}

}

