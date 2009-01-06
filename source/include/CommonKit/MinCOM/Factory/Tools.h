#ifndef FACTORY_TOOLS_H__MINCOM__COMMONKIT__INCLUDED_
#define FACTORY_TOOLS_H__MINCOM__COMMONKIT__INCLUDED_

namespace MinCOM
{

	namespace Private
	{

		ICommonPtr ObjectCreatorInternal(ICommonRef common);

	}

	template< class T > 
	ICommonPtr ObjectCreator() 
	{ 
		return Private::ObjectCreatorInternal(ICommonPtr(new T(), IID_ICommon)); 
	}	

	template< class T, class T1 > 
	ICommonPtr ObjectCreator(T1 p1) 
	{ 
		return Private::ObjectCreatorInternal(ICommonPtr(new T(p1), IID_ICommon)); 
	}	

	template< class T, class T1, class T2 > 
	ICommonPtr ObjectCreator(T1 p1, T2 p2) 
	{ 
		return Private::ObjectCreatorInternal(ICommonPtr(new T(p1, p2), IID_ICommon)); 
	}	

	template< class T, class T1, class T2, class T3 > 
	ICommonPtr ObjectCreator(T1 p1, T2 p2, T3 p3) 
	{ 
		return Private::ObjectCreatorInternal(ICommonPtr(new T(p1, p2, p3), IID_ICommon)); 
	}	

	// Common holder template 
	template
	<
		class T
	>
	class CommonHolder
	{
	public:

		CommonHolder()
			: containee_(ObjectCreator< T >())
		{
		}
		~CommonHolder()
		{
		}

		ICommonPtr GetInstance()
		{
			return containee_;
		}

	protected:

		void NullInstance()
		{
			containee_ = NULL;
		}

	private:

		ICommonPtr containee_;

	};

	// Default factory accessor routine
	inline CommonFactoryHolder::ObjectType& GetCommonFactory()
	{
		return CommonFactoryHolder::Instance();
	}

	// Default client creator routine
	inline ICommonPtr CreateObject(RefClsid clsid)
	{
		return GetCommonFactory().CreateObject(clsid);
	}

	// Default tester routine
	inline bool CanProduce(RefClsid clsid)
	{
		return GetCommonFactory().CanProduce(clsid);
	}

}

#endif // !FACTORY_TOOLS_H__MINCOM__COMMONKIT__INCLUDED_
