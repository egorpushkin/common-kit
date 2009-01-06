namespace MinCOM
{

	template 
	< class T >
	AgentTImpl<T>::AgentTImpl()
		: CommonImpl< T >()
	{
	}

	// IAgent section
	/*template 
	< class T >
	result AgentTImpl<T>::GetTypeInfoCount(
		unsigned int& /* infoCount *)
	{
		return _E_NOTIMPL;
	}*/
	
	template 
	< class T >
	result AgentTImpl<T>::GetTypeInfo(
		unsigned int /* info */, 
		LcId /* id */, 
		ITypeInfoPtr& /* typeInfo */)
	{
		return _E_NOTIMPL;
	}

	template 
	< class T >
	result AgentTImpl<T>::GetIDsOfNames(
		RefIid /* riid */, 
		//StringArRef /* names */,
		unsigned int /* countNames */, 
		unsigned long /* locale */, 
		DispIdArRef /* ids */)
	{
		return _E_NOTIMPL;
	}
	
	template 
	< class T >
	result AgentTImpl<T>::Invoke(
		DispId /* idMember */, 
		DispParamsRef /* dispParams */)
	{
		return _E_NOTIMPL;
	}	

}

