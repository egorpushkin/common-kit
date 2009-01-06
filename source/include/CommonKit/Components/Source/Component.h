#ifndef COMPONENT_H__COMPONENTS__COMMONKIT__INCLUDED_
#define COMPONENT_H__COMPONENTS__COMMONKIT__INCLUDED_

namespace Components
{

	class Component
		: public Components::ComponentImpl
	{
	public:

		Component();
		virtual ~Component();

	};

	typedef Loki::SingletonHolder
	<
		mc::CommonHolder< Component >
	> 
	ComponentHolder;	

}

#endif // !COMPONENT_H__COMPONENTS__COMMONKIT__INCLUDED_
