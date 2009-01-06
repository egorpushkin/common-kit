namespace Project
{

	// Events' registration
	template< class U >
	mc::result ContainerImpl::LocalAdvise(const U& connectee, mc::RefIid apIid /* = IID_IAgent */)
	{
		mc::ICommonPtr localProvider = ItemImpl::GetLocal();
			
		if ( !localProvider || !connectee )
			return mc::_E_INVALIDARG;

		unsigned long cookie = 0;

		mc::ICommonPtr connecteeCommon(connectee, mc::IID_ICommon);

		mc::result code = mc::Advise(connecteeCommon, localProvider, cookie, apIid);
		if ( mc::IsSucceeded(code) )
		{
			// Remember cookie to use it when it happens to remove point
			mc::CookiesHelper::Register(connecteeCommon, cookie);
		}	

		return mc::_S_OK;
	}

	template< class U >
	mc::result ContainerImpl::LocalUnadvise(const U& connectee, mc::RefIid apIid /* = mc::IID_IAgent */)
	{
		if ( !connectee )
			return mc::_E_INVALIDARG;

		mc::ICommonPtr connecteeCommon(connectee, mc::IID_ICommon);

		unsigned long cookie = mc::CookiesHelper::GetCookie(connecteeCommon);

		mc::Unadvise(connecteeCommon, cookie, apIid);

		mc::CookiesHelper::Unregister(connecteeCommon);

		return mc::_S_OK;
	}

}
