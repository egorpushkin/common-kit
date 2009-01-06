/********************************************************************************
** Form generated from reading ui file 'SelectorProperties.ui'
**
** Created: Sun 10. Aug 16:49:11 2008
**      by: Qt User Interface Compiler version 4.3.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_SELECTORPROPERTIES_H
#define UI_SELECTORPROPERTIES_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QFontComboBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

class Ui_SelectorProperties
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *vboxLayout;
    QCheckBox *displayPoints_;
    QGroupBox *pointProperties_;
    QGridLayout *gridLayout1;
    QHBoxLayout *hboxLayout;
    QLabel *label_3;
    QLineEdit *radius_;
    QLabel *label_9;
    QFrame *frame;
    QGridLayout *gridLayout2;
    QWidget *selectedColorDisplayer_;
    QToolButton *selectSelectedColor_;
    QLabel *label_10;
    QFrame *frame_2;
    QGridLayout *gridLayout3;
    QWidget *freeColorDisplayer_;
    QToolButton *selectFreeColor_;
    QCheckBox *displayLabels_;
    QGroupBox *labelProperties_;
    QGridLayout *gridLayout4;
    QVBoxLayout *vboxLayout1;
    QHBoxLayout *hboxLayout1;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *labelXOffset_;
    QLabel *label_7;
    QLineEdit *labelYOffset_;
    QLabel *label_11;
    QLineEdit *labelSize_;
    QHBoxLayout *hboxLayout2;
    QLabel *label_4;
    QFontComboBox *labelFont_;
    QLabel *label_8;
    QFrame *frame_3;
    QGridLayout *gridLayout5;
    QWidget *labelColorDisplayer_;
    QToolButton *labelColor_;
    QCheckBox *displayConnectors_;
    QGroupBox *connectorProperties_;
    QGridLayout *gridLayout6;
    QHBoxLayout *hboxLayout3;
    QLabel *label;
    QLineEdit *connectorWidth_;
    QLabel *label_2;
    QFrame *frame_4;
    QGridLayout *gridLayout7;
    QWidget *connectorColorDisplayer_;
    QToolButton *connectorColor_;

    void setupUi(QDialog *SelectorProperties)
    {
    if (SelectorProperties->objectName().isEmpty())
        SelectorProperties->setObjectName(QString::fromUtf8("SelectorProperties"));
    QSize size(409, 305);
    size = size.expandedTo(SelectorProperties->minimumSizeHint());
    SelectorProperties->resize(size);
    QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(5), static_cast<QSizePolicy::Policy>(0));
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(SelectorProperties->sizePolicy().hasHeightForWidth());
    SelectorProperties->setSizePolicy(sizePolicy);
    SelectorProperties->setMaximumSize(QSize(600, 305));
    gridLayout = new QGridLayout(SelectorProperties);
#ifndef Q_OS_MAC
    gridLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
    gridLayout->setMargin(9);
#endif
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    vboxLayout = new QVBoxLayout();
#ifndef Q_OS_MAC
    vboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
    vboxLayout->setMargin(0);
#endif
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    displayPoints_ = new QCheckBox(SelectorProperties);
    displayPoints_->setObjectName(QString::fromUtf8("displayPoints_"));

    vboxLayout->addWidget(displayPoints_);

    pointProperties_ = new QGroupBox(SelectorProperties);
    pointProperties_->setObjectName(QString::fromUtf8("pointProperties_"));
    sizePolicy.setHeightForWidth(pointProperties_->sizePolicy().hasHeightForWidth());
    pointProperties_->setSizePolicy(sizePolicy);
    gridLayout1 = new QGridLayout(pointProperties_);
#ifndef Q_OS_MAC
    gridLayout1->setSpacing(6);
#endif
#ifndef Q_OS_MAC
    gridLayout1->setMargin(9);
#endif
    gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
    hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
    hboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
    hboxLayout->setMargin(0);
#endif
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    label_3 = new QLabel(pointProperties_);
    label_3->setObjectName(QString::fromUtf8("label_3"));

    hboxLayout->addWidget(label_3);

    radius_ = new QLineEdit(pointProperties_);
    radius_->setObjectName(QString::fromUtf8("radius_"));

    hboxLayout->addWidget(radius_);

    label_9 = new QLabel(pointProperties_);
    label_9->setObjectName(QString::fromUtf8("label_9"));

    hboxLayout->addWidget(label_9);

    frame = new QFrame(pointProperties_);
    frame->setObjectName(QString::fromUtf8("frame"));
    QSizePolicy sizePolicy1(static_cast<QSizePolicy::Policy>(0), static_cast<QSizePolicy::Policy>(5));
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
    frame->setSizePolicy(sizePolicy1);
    frame->setMinimumSize(QSize(40, 16));
    frame->setFrameShape(QFrame::StyledPanel);
    frame->setFrameShadow(QFrame::Raised);
    gridLayout2 = new QGridLayout(frame);
    gridLayout2->setSpacing(1);
    gridLayout2->setMargin(1);
    gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
    selectedColorDisplayer_ = new QWidget(frame);
    selectedColorDisplayer_->setObjectName(QString::fromUtf8("selectedColorDisplayer_"));
    selectedColorDisplayer_->setAutoFillBackground(true);

    gridLayout2->addWidget(selectedColorDisplayer_, 0, 0, 1, 1);


    hboxLayout->addWidget(frame);

    selectSelectedColor_ = new QToolButton(pointProperties_);
    selectSelectedColor_->setObjectName(QString::fromUtf8("selectSelectedColor_"));

    hboxLayout->addWidget(selectSelectedColor_);

    label_10 = new QLabel(pointProperties_);
    label_10->setObjectName(QString::fromUtf8("label_10"));

    hboxLayout->addWidget(label_10);

    frame_2 = new QFrame(pointProperties_);
    frame_2->setObjectName(QString::fromUtf8("frame_2"));
    sizePolicy1.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
    frame_2->setSizePolicy(sizePolicy1);
    frame_2->setMinimumSize(QSize(40, 16));
    frame_2->setFrameShape(QFrame::StyledPanel);
    frame_2->setFrameShadow(QFrame::Raised);
    gridLayout3 = new QGridLayout(frame_2);
    gridLayout3->setSpacing(1);
    gridLayout3->setMargin(1);
    gridLayout3->setObjectName(QString::fromUtf8("gridLayout3"));
    freeColorDisplayer_ = new QWidget(frame_2);
    freeColorDisplayer_->setObjectName(QString::fromUtf8("freeColorDisplayer_"));
    freeColorDisplayer_->setAutoFillBackground(true);

    gridLayout3->addWidget(freeColorDisplayer_, 0, 0, 1, 1);


    hboxLayout->addWidget(frame_2);

    selectFreeColor_ = new QToolButton(pointProperties_);
    selectFreeColor_->setObjectName(QString::fromUtf8("selectFreeColor_"));

    hboxLayout->addWidget(selectFreeColor_);


    gridLayout1->addLayout(hboxLayout, 0, 0, 1, 1);


    vboxLayout->addWidget(pointProperties_);

    displayLabels_ = new QCheckBox(SelectorProperties);
    displayLabels_->setObjectName(QString::fromUtf8("displayLabels_"));

    vboxLayout->addWidget(displayLabels_);

    labelProperties_ = new QGroupBox(SelectorProperties);
    labelProperties_->setObjectName(QString::fromUtf8("labelProperties_"));
    sizePolicy.setHeightForWidth(labelProperties_->sizePolicy().hasHeightForWidth());
    labelProperties_->setSizePolicy(sizePolicy);
    gridLayout4 = new QGridLayout(labelProperties_);
#ifndef Q_OS_MAC
    gridLayout4->setSpacing(6);
#endif
#ifndef Q_OS_MAC
    gridLayout4->setMargin(9);
#endif
    gridLayout4->setObjectName(QString::fromUtf8("gridLayout4"));
    vboxLayout1 = new QVBoxLayout();
#ifndef Q_OS_MAC
    vboxLayout1->setSpacing(6);
#endif
#ifndef Q_OS_MAC
    vboxLayout1->setMargin(0);
#endif
    vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
    hboxLayout1 = new QHBoxLayout();
#ifndef Q_OS_MAC
    hboxLayout1->setSpacing(6);
#endif
#ifndef Q_OS_MAC
    hboxLayout1->setMargin(0);
#endif
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    label_5 = new QLabel(labelProperties_);
    label_5->setObjectName(QString::fromUtf8("label_5"));

    hboxLayout1->addWidget(label_5);

    label_6 = new QLabel(labelProperties_);
    label_6->setObjectName(QString::fromUtf8("label_6"));

    hboxLayout1->addWidget(label_6);

    labelXOffset_ = new QLineEdit(labelProperties_);
    labelXOffset_->setObjectName(QString::fromUtf8("labelXOffset_"));
    QSizePolicy sizePolicy2(static_cast<QSizePolicy::Policy>(0), static_cast<QSizePolicy::Policy>(0));
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(labelXOffset_->sizePolicy().hasHeightForWidth());
    labelXOffset_->setSizePolicy(sizePolicy2);
    labelXOffset_->setMinimumSize(QSize(70, 0));

    hboxLayout1->addWidget(labelXOffset_);

    label_7 = new QLabel(labelProperties_);
    label_7->setObjectName(QString::fromUtf8("label_7"));

    hboxLayout1->addWidget(label_7);

    labelYOffset_ = new QLineEdit(labelProperties_);
    labelYOffset_->setObjectName(QString::fromUtf8("labelYOffset_"));
    sizePolicy2.setHeightForWidth(labelYOffset_->sizePolicy().hasHeightForWidth());
    labelYOffset_->setSizePolicy(sizePolicy2);
    labelYOffset_->setMinimumSize(QSize(70, 0));

    hboxLayout1->addWidget(labelYOffset_);

    label_11 = new QLabel(labelProperties_);
    label_11->setObjectName(QString::fromUtf8("label_11"));

    hboxLayout1->addWidget(label_11);

    labelSize_ = new QLineEdit(labelProperties_);
    labelSize_->setObjectName(QString::fromUtf8("labelSize_"));

    hboxLayout1->addWidget(labelSize_);


    vboxLayout1->addLayout(hboxLayout1);

    hboxLayout2 = new QHBoxLayout();
#ifndef Q_OS_MAC
    hboxLayout2->setSpacing(6);
#endif
    hboxLayout2->setMargin(0);
    hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
    label_4 = new QLabel(labelProperties_);
    label_4->setObjectName(QString::fromUtf8("label_4"));

    hboxLayout2->addWidget(label_4);

    labelFont_ = new QFontComboBox(labelProperties_);
    labelFont_->setObjectName(QString::fromUtf8("labelFont_"));

    hboxLayout2->addWidget(labelFont_);

    label_8 = new QLabel(labelProperties_);
    label_8->setObjectName(QString::fromUtf8("label_8"));

    hboxLayout2->addWidget(label_8);

    frame_3 = new QFrame(labelProperties_);
    frame_3->setObjectName(QString::fromUtf8("frame_3"));
    sizePolicy1.setHeightForWidth(frame_3->sizePolicy().hasHeightForWidth());
    frame_3->setSizePolicy(sizePolicy1);
    frame_3->setMinimumSize(QSize(40, 16));
    frame_3->setFrameShape(QFrame::StyledPanel);
    frame_3->setFrameShadow(QFrame::Raised);
    gridLayout5 = new QGridLayout(frame_3);
    gridLayout5->setSpacing(1);
    gridLayout5->setMargin(1);
    gridLayout5->setObjectName(QString::fromUtf8("gridLayout5"));
    labelColorDisplayer_ = new QWidget(frame_3);
    labelColorDisplayer_->setObjectName(QString::fromUtf8("labelColorDisplayer_"));
    labelColorDisplayer_->setAutoFillBackground(true);

    gridLayout5->addWidget(labelColorDisplayer_, 0, 0, 1, 1);


    hboxLayout2->addWidget(frame_3);

    labelColor_ = new QToolButton(labelProperties_);
    labelColor_->setObjectName(QString::fromUtf8("labelColor_"));

    hboxLayout2->addWidget(labelColor_);


    vboxLayout1->addLayout(hboxLayout2);


    gridLayout4->addLayout(vboxLayout1, 0, 0, 1, 1);


    vboxLayout->addWidget(labelProperties_);

    displayConnectors_ = new QCheckBox(SelectorProperties);
    displayConnectors_->setObjectName(QString::fromUtf8("displayConnectors_"));

    vboxLayout->addWidget(displayConnectors_);

    connectorProperties_ = new QGroupBox(SelectorProperties);
    connectorProperties_->setObjectName(QString::fromUtf8("connectorProperties_"));
    sizePolicy.setHeightForWidth(connectorProperties_->sizePolicy().hasHeightForWidth());
    connectorProperties_->setSizePolicy(sizePolicy);
    gridLayout6 = new QGridLayout(connectorProperties_);
#ifndef Q_OS_MAC
    gridLayout6->setSpacing(6);
#endif
#ifndef Q_OS_MAC
    gridLayout6->setMargin(9);
#endif
    gridLayout6->setObjectName(QString::fromUtf8("gridLayout6"));
    hboxLayout3 = new QHBoxLayout();
#ifndef Q_OS_MAC
    hboxLayout3->setSpacing(6);
#endif
#ifndef Q_OS_MAC
    hboxLayout3->setMargin(0);
#endif
    hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
    label = new QLabel(connectorProperties_);
    label->setObjectName(QString::fromUtf8("label"));

    hboxLayout3->addWidget(label);

    connectorWidth_ = new QLineEdit(connectorProperties_);
    connectorWidth_->setObjectName(QString::fromUtf8("connectorWidth_"));

    hboxLayout3->addWidget(connectorWidth_);

    label_2 = new QLabel(connectorProperties_);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    hboxLayout3->addWidget(label_2);

    frame_4 = new QFrame(connectorProperties_);
    frame_4->setObjectName(QString::fromUtf8("frame_4"));
    sizePolicy1.setHeightForWidth(frame_4->sizePolicy().hasHeightForWidth());
    frame_4->setSizePolicy(sizePolicy1);
    frame_4->setMinimumSize(QSize(40, 16));
    frame_4->setFrameShape(QFrame::StyledPanel);
    frame_4->setFrameShadow(QFrame::Raised);
    gridLayout7 = new QGridLayout(frame_4);
    gridLayout7->setSpacing(1);
    gridLayout7->setMargin(1);
    gridLayout7->setObjectName(QString::fromUtf8("gridLayout7"));
    connectorColorDisplayer_ = new QWidget(frame_4);
    connectorColorDisplayer_->setObjectName(QString::fromUtf8("connectorColorDisplayer_"));
    connectorColorDisplayer_->setAutoFillBackground(true);

    gridLayout7->addWidget(connectorColorDisplayer_, 0, 0, 1, 1);


    hboxLayout3->addWidget(frame_4);

    connectorColor_ = new QToolButton(connectorProperties_);
    connectorColor_->setObjectName(QString::fromUtf8("connectorColor_"));

    hboxLayout3->addWidget(connectorColor_);


    gridLayout6->addLayout(hboxLayout3, 0, 0, 1, 1);


    vboxLayout->addWidget(connectorProperties_);


    gridLayout->addLayout(vboxLayout, 0, 0, 1, 1);


    retranslateUi(SelectorProperties);
    QObject::connect(displayPoints_, SIGNAL(clicked(bool)), pointProperties_, SLOT(setEnabled(bool)));
    QObject::connect(displayLabels_, SIGNAL(clicked(bool)), labelProperties_, SLOT(setEnabled(bool)));
    QObject::connect(displayConnectors_, SIGNAL(clicked(bool)), connectorProperties_, SLOT(setEnabled(bool)));

    QMetaObject::connectSlotsByName(SelectorProperties);
    } // setupUi

    void retranslateUi(QDialog *SelectorProperties)
    {
    SelectorProperties->setWindowTitle(QApplication::translate("SelectorProperties", "Selector Control Properties", 0, QApplication::UnicodeUTF8));
    displayPoints_->setText(QApplication::translate("SelectorProperties", "Display points", 0, QApplication::UnicodeUTF8));
    pointProperties_->setTitle(QApplication::translate("SelectorProperties", "Point Properties", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("SelectorProperties", "Radius:", 0, QApplication::UnicodeUTF8));
    label_9->setText(QApplication::translate("SelectorProperties", "Selected:", 0, QApplication::UnicodeUTF8));
    selectSelectedColor_->setText(QApplication::translate("SelectorProperties", "...", 0, QApplication::UnicodeUTF8));
    label_10->setText(QApplication::translate("SelectorProperties", "Free:", 0, QApplication::UnicodeUTF8));
    selectFreeColor_->setText(QApplication::translate("SelectorProperties", "...", 0, QApplication::UnicodeUTF8));
    displayLabels_->setText(QApplication::translate("SelectorProperties", "Display labels", 0, QApplication::UnicodeUTF8));
    labelProperties_->setTitle(QApplication::translate("SelectorProperties", "Point Properties", 0, QApplication::UnicodeUTF8));
    label_5->setText(QApplication::translate("SelectorProperties", "Offset:", 0, QApplication::UnicodeUTF8));
    label_6->setText(QApplication::translate("SelectorProperties", "X:", 0, QApplication::UnicodeUTF8));
    label_7->setText(QApplication::translate("SelectorProperties", "Y:", 0, QApplication::UnicodeUTF8));
    label_11->setText(QApplication::translate("SelectorProperties", "Size:", 0, QApplication::UnicodeUTF8));
    label_4->setText(QApplication::translate("SelectorProperties", "Font:", 0, QApplication::UnicodeUTF8));
    label_8->setText(QApplication::translate("SelectorProperties", "Color:", 0, QApplication::UnicodeUTF8));
    labelColor_->setText(QApplication::translate("SelectorProperties", "...", 0, QApplication::UnicodeUTF8));
    displayConnectors_->setText(QApplication::translate("SelectorProperties", "Display connectors", 0, QApplication::UnicodeUTF8));
    connectorProperties_->setTitle(QApplication::translate("SelectorProperties", "Connector Properties", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("SelectorProperties", "Width:", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("SelectorProperties", "Color:", 0, QApplication::UnicodeUTF8));
    connectorColor_->setText(QApplication::translate("SelectorProperties", "...", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(SelectorProperties);
    } // retranslateUi

};

namespace Ui {
    class SelectorProperties: public Ui_SelectorProperties {};
} // namespace Ui

#endif // UI_SELECTORPROPERTIES_H
