#ifndef IMAGENAME_H__AREASLIB__INCLUDED_
#define IMAGENAME_H__AREASLIB__INCLUDED_

namespace Areas
{

	class ImageName
		: public mc::CommandImpl
		, public Components::ObjCounter
	{
	public:

		ImageName();

		// ICommand section
		virtual mc::result Undo();

	};

}

#endif // !IMAGENAME_H__AREASLIB__INCLUDED_
