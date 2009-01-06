#ifndef AREANAME_H__AREASLIB__INCLUDED_
#define AREANAME_H__AREASLIB__INCLUDED_

namespace Areas
{

	class AreaName
		: public mc::CommandImpl
		, public Components::ObjCounter
	{
	public:

		AreaName();

		// ICommand section
		virtual mc::result Undo();

	};

}

#endif // !AREANAME_H__AREASLIB__INCLUDED_
