/********************************************************************************
** Form generated from reading ui file 'AreaName.ui'
**
** Created: Sun 10. Aug 16:49:11 2008
**      by: Qt User Interface Compiler version 4.3.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_AREANAME_H
#define UI_AREANAME_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

class Ui_AreaNameClass
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *hboxLayout;
    QLabel *label;
    QLineEdit *areaName_;
    QPushButton *ok_;

    void setupUi(QDialog *AreaNameClass)
    {
    if (AreaNameClass->objectName().isEmpty())
        AreaNameClass->setObjectName(QString::fromUtf8("AreaNameClass"));
    AreaNameClass->setWindowModality(Qt::ApplicationModal);
    QSize size(400, 46);
    size = size.expandedTo(AreaNameClass->minimumSizeHint());
    AreaNameClass->resize(size);
    QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(5), static_cast<QSizePolicy::Policy>(0));
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(AreaNameClass->sizePolicy().hasHeightForWidth());
    AreaNameClass->setSizePolicy(sizePolicy);
    AreaNameClass->setMaximumSize(QSize(16777215, 46));
    gridLayout = new QGridLayout(AreaNameClass);
    gridLayout->setSpacing(6);
    gridLayout->setMargin(9);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    hboxLayout = new QHBoxLayout();
    hboxLayout->setSpacing(6);
    hboxLayout->setMargin(0);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    label = new QLabel(AreaNameClass);
    label->setObjectName(QString::fromUtf8("label"));

    hboxLayout->addWidget(label);

    areaName_ = new QLineEdit(AreaNameClass);
    areaName_->setObjectName(QString::fromUtf8("areaName_"));

    hboxLayout->addWidget(areaName_);

    ok_ = new QPushButton(AreaNameClass);
    ok_->setObjectName(QString::fromUtf8("ok_"));

    hboxLayout->addWidget(ok_);


    gridLayout->addLayout(hboxLayout, 0, 0, 1, 1);


    retranslateUi(AreaNameClass);

    QMetaObject::connectSlotsByName(AreaNameClass);
    } // setupUi

    void retranslateUi(QDialog *AreaNameClass)
    {
    AreaNameClass->setWindowTitle(QApplication::translate("AreaNameClass", "Modify Area Name", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("AreaNameClass", "Area name:", 0, QApplication::UnicodeUTF8));
    ok_->setText(QApplication::translate("AreaNameClass", "OK", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(AreaNameClass);
    } // retranslateUi

};

namespace Ui {
    class AreaNameClass: public Ui_AreaNameClass {};
} // namespace Ui

#endif // UI_AREANAME_H
