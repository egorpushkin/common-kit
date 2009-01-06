#ifndef QWIDGETIMPL_H__QKIT__INCLUDED_
#define QWIDGETIMPL_H__QKIT__INCLUDED_

namespace QExtension
{

	class QWidgetImpl 
		: public mc::CommonImpl< IQWidget > 
	{
	public:

		QWidgetImpl();

		// ICommon section
		DECLARE_INTERFACE_MAP()		

		// IQWidget section
		virtual QWidget* GetWidget();

	private:



	};

}

#endif // !QWIDGETIMPL_H__QKIT__INCLUDED_
