#include "qmcwidget.h"

#include <QPainter>
#include <QTime>
#include <QResizeEvent>

QMcWidget::QMcWidget(QWidget* parent)
	: QWidget(parent)
#ifdef WIDGET_CONTROL
	, gridLayout_(NULL)
	, attachedControl_()
#endif // WIDGET_CONTROL
{
}

QMcWidget::~QMcWidget()
{
}

#ifdef WIDGET_CONTROL

mc::result QMcWidget::Attach(mc::RefClsid objId)
{
	if ( attachedControl_ )
		return mc::_E_FAIL;

	attachedControl_ = Components::InstantiateCommon(objId);

	return AttachCore();
}

mc::result QMcWidget::Attach(mc::RefIid libIid, mc::RefClsid objId)
{
	if ( attachedControl_ )
		return mc::_E_FAIL;

	attachedControl_ = Components::InstantiateCommon(libIid, objId);

	return AttachCore();
}

mc::ICommonPtr QMcWidget::GetCommon()
{	
	return attachedControl_;
}

mc::result QMcWidget::AttachCore()
{
	if ( !attachedControl_ )
		return mc::_E_INVALIDARG;

	QExtension::IQWidgetPtr widgetControl(attachedControl_, QExtension::IID_IQWidget);
	if ( !widgetControl )
	{
		attachedControl_ = NULL;
		return mc::_E_FAIL;
	}

	QWidget* pAttachedWidget = widgetControl->GetWidget();
	if ( !pAttachedWidget )
	{
		attachedControl_ = NULL;
		return mc::_E_FAIL;
	}

	// Setup ui	
	gridLayout_ = new QGridLayout(this);
	gridLayout_->setSpacing(0);
	gridLayout_->setMargin(0);
	gridLayout_->setObjectName(QString::fromUtf8("gridLayout_"));
	pAttachedWidget->setParent(this);
	gridLayout_->addWidget(pAttachedWidget, 0, 0, 1, 1);	

	return mc::_S_OK;
}

#endif // WIDGET_CONTROL

#ifndef WIDGET_CONTROL

void QMcWidget::paintEvent(QPaintEvent* event)
{
	static const QPoint hourHand[3] = {
		QPoint(7, 8),
		QPoint(-7, 8),
		QPoint(0, -40)
	};
	static const QPoint minuteHand[3] = {
		QPoint(7, 8),
		QPoint(-7, 8),
		QPoint(0, -70)
	};

	QColor hourColor(127, 0, 127);
	QColor minuteColor(0, 127, 127, 191);

	int side = qMin(width(), height());
	QTime time = QTime::currentTime();

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.translate(width() / 2, height() / 2);
	painter.scale(side / 200.0, side / 200.0);

	painter.setPen(Qt::NoPen);
	painter.setBrush(hourColor);

	painter.save();
	painter.rotate(30.0 * ((time.hour() + time.minute() / 60.0)));
	painter.drawConvexPolygon(hourHand, 3);
	painter.restore();

	painter.setPen(hourColor);

	for (int i = 0; i < 12; ++i) {
		painter.drawLine(88, 0, 96, 0);
		painter.rotate(30.0);
	}

	painter.setPen(Qt::NoPen);
	painter.setBrush(minuteColor);

	painter.save();
	painter.rotate(6.0 * (time.minute() + time.second() / 60.0));
	painter.drawConvexPolygon(minuteHand, 3);
	painter.restore();

	painter.setPen(minuteColor);

	for (int j = 0; j < 60; ++j) {
		if ((j % 5) != 0)
			painter.drawLine(92, 0, 96, 0);
		painter.rotate(6.0);
	}
}

#endif // !WIDGET_CONTROL