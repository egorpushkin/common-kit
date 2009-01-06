/********************************************************************************
** Form generated from reading ui file 'areasselector.ui'
**
** Created: Sun 10. Aug 16:49:13 2008
**      by: Qt User Interface Compiler version 4.3.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_AREASSELECTOR_H
#define UI_AREASSELECTOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QPushButton>
#include "SelectorWidget.h"

class Ui_AreasSelectorClass
{
public:
    SelectorWidget *selectorMirror_;
    SelectorWidget *selector_;
    QPushButton *loadProject_;

    void setupUi(QDialog *AreasSelectorClass)
    {
    if (AreasSelectorClass->objectName().isEmpty())
        AreasSelectorClass->setObjectName(QString::fromUtf8("AreasSelectorClass"));
    QSize size(721, 488);
    size = size.expandedTo(AreasSelectorClass->minimumSizeHint());
    AreasSelectorClass->resize(size);
    selectorMirror_ = new SelectorWidget(AreasSelectorClass);
    selectorMirror_->setObjectName(QString::fromUtf8("selectorMirror_"));
    selectorMirror_->setGeometry(QRect(420, 20, 271, 201));
    selectorMirror_->setMinimumSize(QSize(200, 200));
    selector_ = new SelectorWidget(AreasSelectorClass);
    selector_->setObjectName(QString::fromUtf8("selector_"));
    selector_->setGeometry(QRect(10, 10, 400, 408));
    selector_->setMinimumSize(QSize(400, 400));
    selector_->setContextMenuPolicy(Qt::DefaultContextMenu);
    loadProject_ = new QPushButton(AreasSelectorClass);
    loadProject_->setObjectName(QString::fromUtf8("loadProject_"));
    loadProject_->setGeometry(QRect(530, 260, 77, 26));

    retranslateUi(AreasSelectorClass);

    QMetaObject::connectSlotsByName(AreasSelectorClass);
    } // setupUi

    void retranslateUi(QDialog *AreasSelectorClass)
    {
    AreasSelectorClass->setWindowTitle(QApplication::translate("AreasSelectorClass", "AreasSelector", 0, QApplication::UnicodeUTF8));
    loadProject_->setText(QApplication::translate("AreasSelectorClass", "Load Project", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(AreasSelectorClass);
    } // retranslateUi

};

namespace Ui {
    class AreasSelectorClass: public Ui_AreasSelectorClass {};
} // namespace Ui

#endif // UI_AREASSELECTOR_H
