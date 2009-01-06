#include <QWidget>

#include <QKit/QKit.h>

namespace QExtension 
{

	QWidgetImpl::QWidgetImpl()
		: mc::CommonImpl< IQWidget >()
	{
		mc::CommonImpl< IQWidget >::AddRef();
	}

	// ICommon section
	BEGIN_INTERFACE_MAP(QWidgetImpl)
		COMMON(IQWidget)
		INTERFACE(IQWidget)
	END_INTERFACE_MAP()	

	// IQWidget section
	QWidget* QWidgetImpl::GetWidget()
	{
		return dynamic_cast< QWidget* >(this);
	}





}
