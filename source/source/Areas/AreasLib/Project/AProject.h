#ifndef APROJECT_H__AREASLIB__INCLUDED_
#define APROJECT_H__AREASLIB__INCLUDED_

namespace Areas
{

	class AProject
		: public mc::CommonImpl< IAProject >
		, public Project::ContainerImpl
		, public Components::ObjCounter
	{

		typedef Project::ContainerImpl ContainerImpl_;

	public:

		AProject();
		virtual ~AProject();

		// ICommon section
		DECLARE_INTERFACE_MAP()	

		// IAProject section
		virtual IMsImagePtr GetImage();

		// IItem section
		virtual mc::result PostInit();

	private:

		IMsImagePtr image_;

	};

}

#endif // !APROJECT_H__AREASLIB__INCLUDED_


