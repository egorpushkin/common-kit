#include "Common/Common.h"

#include "SelectorWidget/SelectorWidget.h"
#include "Serialization/AsciiLoader.h"

namespace Components
{

	Component::Component()
		: Components::ComponentImpl(Components::TYPEID_General, AreasSelector::LIBID_AreasSelector)
	{

		Component::Register(AreasSelector::CLSID_AreasSelector, mc::ObjectCreator< SelectorWidget >);
		Component::Register(AreasSelector::CLSID_AsciiLoader, mc::ObjectCreator< Serialization::AsciiLoader >);

	}

}
