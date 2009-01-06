#ifndef AREA_H__AREASLIB__INCLUDED_
#define AREA_H__AREASLIB__INCLUDED_

namespace Areas
{

	class Area
		: public mc::CommonImpl< IArea >
		, public Project::ContainerImpl
		, public Components::ObjCounter
	{

		typedef Project::ContainerImpl ContainerImpl_;

	public:

		Area();
		virtual ~Area();

		// ICommon section
		DECLARE_INTERFACE_MAP()	

		// IArea section
		virtual void SetName(const mc::StringA& name);

		virtual mc::StringA GetName();

	private:

		// Event dispatchers
		mc::result OnNameChanged(const mc::StringA& name);

		// Commands
		mc::result RegisterAreaNameCommand(const mc::StringA& name);

	private:

		mc::StringA name_;

	};

}

#endif // !AREA_H__AREASLIB__INCLUDED_
