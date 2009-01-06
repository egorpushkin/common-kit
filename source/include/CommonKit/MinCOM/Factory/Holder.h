#ifndef FACTORY_HOLDER_H__MINCOM__COMMONKIT__INCLUDED_
#define FACTORY_HOLDER_H__MINCOM__COMMONKIT__INCLUDED_

namespace MinCOM
{

	typedef Factory
	<
		ICommonPtr, Clsid
	>
	CommonFactory;

	template 
	<
		class T // CommonFactory always
	> 
	class FactoryCreator
	{
	public:

		static T* Create()
		{			
			return new T;
		}

		static void Destroy(T* pFactory)
		{ 
			delete pFactory;
		}

	};	

	typedef Loki::SingletonHolder
	<
		CommonFactory,
		FactoryCreator 
	> 
	CommonFactoryHolder;

}

#endif // !FACTORY_HOLDER_H__MINCOM__COMMONKIT__INCLUDED_
