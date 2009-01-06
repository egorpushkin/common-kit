#ifndef CREATORS_H__CONTAINER__COMMONKIT__INCLUDED_
#define CREATORS_H__CONTAINER__COMMONKIT__INCLUDED_

namespace Container
{

	template
	<
		class T
	>
	mc::ComPtr< IContainer< T > > CreateDefault()
	{
		return mc::ComPtr< IContainer< T > >( 
			new Container< T, VectorStorage, Copy, NoRefs >(), IID_IContainer 
		);
	}

	template
	<
		class T
	>
	mc::ComPtr< IContainer< T > > CreateUnmanagedDefault()
	{
		return mc::ComPtr< IContainer< T > >( 
			new Container< T, VectorStorage, Copy, NoRefs, Unmanaged >(), IID_IContainer 
		);
	}

	template
	<
		class T
	>
	mc::ComPtr< IContainer< T > > CreateMap()
	{
		return mc::ComPtr< IContainer< T > >( 
			new Container< T, MapStorage, Copy, NoRefs >(), IID_IContainer 
		);
	}

	template
	<
		class T
	>
	mc::ComPtr< IContainer< T > > CreateUnmanagedMap()
	{
		return mc::ComPtr< IContainer< T > >( 
			new Container< T, MapStorage, Copy, NoRefs, Unmanaged >(), IID_IContainer 
		);
	}

}

#endif // !CREATORS_H__CONTAINER__COMMONKIT__INCLUDED_
