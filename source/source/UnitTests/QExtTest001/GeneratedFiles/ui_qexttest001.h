/********************************************************************************
** Form generated from reading ui file 'qexttest001.ui'
**
** Created: Mon 3. Dec 12:07:36 2007
**      by: Qt User Interface Compiler version 4.3.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_QEXTTEST001_H
#define UI_QEXTTEST001_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>
#include "qmcwidget.h"

class Ui_QExtTest001Class
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QMcWidget *selectorDemo_;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QExtTest001Class)
    {
    if (QExtTest001Class->objectName().isEmpty())
        QExtTest001Class->setObjectName(QString::fromUtf8("QExtTest001Class"));
    QSize size(600, 400);
    size = size.expandedTo(QExtTest001Class->minimumSizeHint());
    QExtTest001Class->resize(size);
    centralWidget = new QWidget(QExtTest001Class);
    centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
    gridLayout = new QGridLayout(centralWidget);
    gridLayout->setSpacing(6);
    gridLayout->setMargin(9);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    selectorDemo_ = new QMcWidget(centralWidget);
    selectorDemo_->setObjectName(QString::fromUtf8("selectorDemo_"));

    gridLayout->addWidget(selectorDemo_, 0, 0, 1, 1);

    QExtTest001Class->setCentralWidget(centralWidget);
    menuBar = new QMenuBar(QExtTest001Class);
    menuBar->setObjectName(QString::fromUtf8("menuBar"));
    menuBar->setGeometry(QRect(0, 0, 600, 19));
    QExtTest001Class->setMenuBar(menuBar);
    mainToolBar = new QToolBar(QExtTest001Class);
    mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
    mainToolBar->setOrientation(Qt::Horizontal);
    QExtTest001Class->addToolBar(static_cast<Qt::ToolBarArea>(4), mainToolBar);
    statusBar = new QStatusBar(QExtTest001Class);
    statusBar->setObjectName(QString::fromUtf8("statusBar"));
    QExtTest001Class->setStatusBar(statusBar);

    retranslateUi(QExtTest001Class);

    QMetaObject::connectSlotsByName(QExtTest001Class);
    } // setupUi

    void retranslateUi(QMainWindow *QExtTest001Class)
    {
    QExtTest001Class->setWindowTitle(QApplication::translate("QExtTest001Class", "QExtTest001", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(QExtTest001Class);
    } // retranslateUi

};

namespace Ui {
    class QExtTest001Class: public Ui_QExtTest001Class {};
} // namespace Ui

#endif // UI_QEXTTEST001_H
