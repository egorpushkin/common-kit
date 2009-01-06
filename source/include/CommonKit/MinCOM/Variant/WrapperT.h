#ifndef WRAPPERT_H__MINCOM__COMMONKIT__INCLUDED_
#define WRAPPERT_H__MINCOM__COMMONKIT__INCLUDED_

namespace MinCOM
{

	template
	<
		class T
	>
	interface IWrapperT : public ICommon
	{

		typedef T Type_;

		virtual result SetData(const T& data) = 0;

		virtual T& GetData() = 0;
 
	};

	// {c4a1b926-9ffe-4dc2-9a9b-83f822286ed0} 
	MC_DEFINE_GUID(IID_IWrapper, 
	0xc4a1b926, 0x9ffe, 0x4dc2, 0x9a, 0x9b, 0x83, 0xf8, 0x22, 0x28, 0x6e, 0xd0);

	template
	<
		class T
	>
	class WrapperT 
		: public CommonImpl< IWrapperT< T > >
	{
	public:

		WrapperT()
			: CommonImpl< IWrapperT< T > >()
			, data_()
		{
		}

		// ICommon section
		IMPLACE_INTERFACE_MAP()			
			COMMON(IWrapperT<T>)			
			INTERFACE_(IWrapperT<T>, IID_IWrapper)
		END_INTERFACE_MAP()	

		// IWrapperT section
		result SetData(const T& data)
		{
			data_ = data;

			return _S_OK;
		}

		T& GetData()
		{
			return data_;
		}

	private:

		T data_;

	};

	template
	<
		class T
	>
	ICommonPtr ConstractWrapper()
	{
		return ObjectCreator< WrapperT< T > >();
	}

	template
	<
		class T
	>
	ICommonPtr ConstractWrapper(const T& data)
	{
		ComPtr< IWrapperT< T > > wrapper(ObjectCreator< WrapperT< T > >(), IID_IWrapper);

		wrapper->SetData(data);

		return ICommonPtr(wrapper, IID_ICommon);
	}

	template
	<
		class T
	>
	T Unwrap(ICommonRef cmnWrapper)
	{
		ComPtr< IWrapperT< T > > wrapper(cmnWrapper, IID_IWrapper);
		if ( !wrapper )
			return T();

		return wrapper->GetData();
	}

}

#endif // !WRAPPERT_H__MINCOM__COMMONKIT__INCLUDED_
