#ifndef IQWIDGET_H__QKIT__INCLUDED_
#define IQWIDGET_H__QKIT__INCLUDED_

class QWidget;

namespace QExtension
{

	interface IQWidget : public mc::ICommon
	{

		virtual QWidget* GetWidget() = 0;

	};

	typedef mc::ComPtr< IQWidget > IQWidgetPtr;
	typedef const IQWidgetPtr& IQWidgetRef;

	// {d1e008db-2357-4af1-a924-284ca2e00878} 
	MC_DEFINE_GUID(IID_IQWidget, 
	0xd1e008db, 0x2357, 0x4af1, 0xa9, 0x24, 0x28, 0x4c, 0xa2, 0xe0, 0x08, 0x78);

}

#endif // !IQWIDGET_H__QKIT__INCLUDED_
