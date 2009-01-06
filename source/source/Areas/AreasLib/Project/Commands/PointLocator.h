#ifndef POINTLOCATOR_H__AREASLIB__INCLUDED_
#define POINTLOCATOR_H__AREASLIB__INCLUDED_

namespace Areas
{

	class PointLocator
		: public mc::CommandImpl
		, public Components::ObjCounter
	{
	public:

		PointLocator();

		// ICommand section
		virtual mc::result Undo();

	};

}

#endif // !POINTLOCATOR_H__AREASLIB__INCLUDED_
