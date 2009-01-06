#ifndef REFERENCESPOLICY_H__COMMON__INCLUDED_
#define REFERENCESPOLICY_H__COMMON__INCLUDED_

namespace Container
{

	template 
	<
		class T
	>
	class WithRefs
	{
	public:	
		static unsigned long AddRef(const T& element)  
		{
			return element->AddRef();
		}

		static unsigned long Release(const T& element) 
		{
			return element->Release();
		}
	};

	template 
	<
		class T
	>
	class MapRefs
	{
	public:	
		static unsigned long AddRef(const T& element)  
		{
			return WithRefs< typename T::second_type >::AddRef(element.second);
		}

		static unsigned long Release(const T& element) 
		{
			return WithRefs< typename T::second_type >::Release(element.second);
		}
	};

	template 
	<
		class T
	>
	class NoRefs
	{
	public:
		static unsigned long AddRef(const T& /* element */) 
		{
			return 0;
		}

		static unsigned long Release(const T& /* element */) 
		{
			return 0;
		}
	};

}

#endif // !REFERENCESPOLICY_H__COMMON__INCLUDED_
