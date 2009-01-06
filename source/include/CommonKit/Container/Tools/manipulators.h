#ifndef MANIPULATORS_H__CONTAINER__COMMONKIT__INCLUDED_
#define MANIPULATORS_H__CONTAINER__COMMONKIT__INCLUDED_

namespace Container
{

#ifdef _MSC_VER
	typedef std::_Iterator_base BaseIterator;
#elif WIN32 // MinGW or something else	
#elif POSIX // any Posix macro
#elif __MACH__
	typedef void* BaseIterator;
#endif // _MSC_VER

	class Manipulator
	{
	public:

		virtual MinCOM::result operator()(BaseIterator& begin, BaseIterator& end);

	};
	
}

#endif // !MANIPULATORS_H__CONTAINER__COMMONKIT__INCLUDED_
