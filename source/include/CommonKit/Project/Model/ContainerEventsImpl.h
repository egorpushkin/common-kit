#ifndef CONTAINEREVENTSIMPL_H__PROJECTKIT__INCLUDED_
#define CONTAINEREVENTSIMPL_H__PROJECTKIT__INCLUDED_

namespace Project
{

	class ContainerEventsImpl
		: public mc::CommonImpl< IContainerEvents > 
	{
	public:

		ContainerEventsImpl();

		// IContainer section
		virtual void SetOnBeforeAdd(mc::DispId id);

		virtual void SetOnAfterAdd(mc::DispId id);

		virtual void SetOnBeforeDelete(mc::DispId id);

		virtual void SetOnAfterDelete(mc::DispId id);

		virtual mc::DispId GetOnBeforeAdd();

		virtual mc::DispId GetOnAfterAdd();

		virtual mc::DispId GetOnBeforeDelete();

		virtual mc::DispId GetOnAfterDelete();

		// ICommon section
		DECLARE_INTERFACE_MAP()		

	protected:

		mc::DispId onBeforeAdd_;	

		mc::DispId onAfterAdd_;		

		mc::DispId onBeforeDelete_;	

		mc::DispId onAfterDelete_;		

	};

	typedef ContainerEventsImpl CEvImpl;

}

#endif // !CONTAINEREVENTSIMPL_H__PROJECTKIT__INCLUDED_
