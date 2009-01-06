#ifndef WIDGETIMPL_H__AREASSELECTOR__INCLUDED_
#define WIDGETIMPL_H__AREASSELECTOR__INCLUDED_

namespace AreasSelector
{

	class WidgetImpl 
		: public mc::CommonImpl< IWidget >
	{
	public:

		WidgetImpl();

		// ICommon section
		DECLARE_INTERFACE_MAP()		

		// IWidget section
		virtual mc::result SetBehaviour(IBehaviourRef behaviour);

		virtual IBehaviourPtr GetBehaviour();

	private:

		IBehaviourPtr behaviour_;

	};

}

#endif // !WIDGETIMPL_H__AREASSELECTOR__INCLUDED_
