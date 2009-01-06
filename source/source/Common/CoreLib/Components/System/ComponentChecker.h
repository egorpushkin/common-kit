#ifndef COMPONENTCHECKER_H__COMPONENTS__COMMONKIT__INCLUDED_
#define COMPONENTCHECKER_H__COMPONENTS__COMMONKIT__INCLUDED_

namespace Components
{

	class ComponentChecker
	{
	public:

		typedef enum tagMethod_
		{

			METHOD_BYLIBTYPE_ = 0x0,

			METHOD_BYLIBIID_,

			METHOD_BYCLSID_

		} Method_;

		ComponentChecker(Method_ method);

		bool Check(IComponentRef component, mc::RefIid iid, mc::RefIid typeIid = TYPEID_General);

	private:

		Method_ method_;

	};

}

#endif // !COMPONENTCHECKER_H__COMPONENTS__COMMONKIT__INCLUDED_
