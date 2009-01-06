#include "Common/Common.h"

#include "Project/AProject.h"
#include "Project/Area.h"
#include "Project/Point.h"

#include "Project/PS/PointPS.h"

namespace Components
{

	Component::Component()
		: Components::ComponentImpl(Components::TYPEID_General, Areas::LIBID_Areas)
	{

		Component::Register(Areas::CLSID_AreasProject, mc::ObjectCreator< Areas::AProject >);
		Component::Register(Areas::CLSID_Area, mc::ObjectCreator< Areas::Area >);
		Component::Register(Areas::CLSID_Point, mc::ObjectCreator< Areas::Point >);

		Component::Register(Areas::IID_IPoint, mc::ObjectCreator< Areas::PointPS >);

	}

}
