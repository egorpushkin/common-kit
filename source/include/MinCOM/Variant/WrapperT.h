/*
 * File name   : WrapperT.h
 *
 * Copyright (c) 2009 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-01-30  Egor Pushkin        Initial version
 */

#ifndef WRAPPERT_H__MINCOM__INCLUDED_
#define WRAPPERT_H__MINCOM__INCLUDED_

namespace MinCOM
{

	template
	<
		class T
	>
	interface IWrapperT : public ICommon
	{
		virtual void SetData(const T& data) = 0;
		virtual T GetData() = 0;
	};

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

		WrapperT(const T& data)
			: CommonImpl< IWrapperT< T > >()
			, data_(data)
		{
		}

		// IWrapperT section
		void SetData(const T& data)
		{
			data_ = data;
		}

		T GetData()
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
	ICommonPtr Wrap(const T& data)
	{
		return Class< WrapperT< T > >::Create(data);
	}

	template
	<
		class T
	>
	T Unwrap(ICommonRef cmnWrapper)
	{
		Strong< IWrapperT< T > > wrapper(cmnWrapper);
		if ( !wrapper )
			return T();
		return wrapper->GetData();
	}

}

#endif // !WRAPPERT_H__MINCOM__INCLUDED_
