/********************************************************************************
** Form generated from reading ui file 'areasselector.ui'
**
** Created: Sun 10. Aug 16:49:15 2008
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
#include <QtGui/QGridLayout>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>
#include "qmcwidget.h"

class Ui_AreasSelectorClass
{
public:
    QAction *actionLoad_Project;
    QAction *actionSave_Project;
    QAction *actionLoad_Image;
    QAction *actionExit;
    QAction *actionProperties;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionNew_Project;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QMcWidget *selectorControl_;
    QMenuBar *menuBar;
    QMenu *menuTools;
    QMenu *menuEdit;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *AreasSelectorClass)
    {
    if (AreasSelectorClass->objectName().isEmpty())
        AreasSelectorClass->setObjectName(QString::fromUtf8("AreasSelectorClass"));
    QSize size(600, 400);
    size = size.expandedTo(AreasSelectorClass->minimumSizeHint());
    AreasSelectorClass->resize(size);
    actionLoad_Project = new QAction(AreasSelectorClass);
    actionLoad_Project->setObjectName(QString::fromUtf8("actionLoad_Project"));
    actionSave_Project = new QAction(AreasSelectorClass);
    actionSave_Project->setObjectName(QString::fromUtf8("actionSave_Project"));
    actionLoad_Image = new QAction(AreasSelectorClass);
    actionLoad_Image->setObjectName(QString::fromUtf8("actionLoad_Image"));
    actionExit = new QAction(AreasSelectorClass);
    actionExit->setObjectName(QString::fromUtf8("actionExit"));
    actionProperties = new QAction(AreasSelectorClass);
    actionProperties->setObjectName(QString::fromUtf8("actionProperties"));
    actionUndo = new QAction(AreasSelectorClass);
    actionUndo->setObjectName(QString::fromUtf8("actionUndo"));
    actionRedo = new QAction(AreasSelectorClass);
    actionRedo->setObjectName(QString::fromUtf8("actionRedo"));
    actionNew_Project = new QAction(AreasSelectorClass);
    actionNew_Project->setObjectName(QString::fromUtf8("actionNew_Project"));
    centralWidget = new QWidget(AreasSelectorClass);
    centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
    gridLayout = new QGridLayout(centralWidget);
    gridLayout->setSpacing(6);
    gridLayout->setMargin(9);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    selectorControl_ = new QMcWidget(centralWidget);
    selectorControl_->setObjectName(QString::fromUtf8("selectorControl_"));

    gridLayout->addWidget(selectorControl_, 0, 0, 1, 1);

    AreasSelectorClass->setCentralWidget(centralWidget);
    menuBar = new QMenuBar(AreasSelectorClass);
    menuBar->setObjectName(QString::fromUtf8("menuBar"));
    menuBar->setGeometry(QRect(0, 0, 600, 19));
    menuTools = new QMenu(menuBar);
    menuTools->setObjectName(QString::fromUtf8("menuTools"));
    menuEdit = new QMenu(menuBar);
    menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
    menuFile = new QMenu(menuBar);
    menuFile->setObjectName(QString::fromUtf8("menuFile"));
    AreasSelectorClass->setMenuBar(menuBar);
    mainToolBar = new QToolBar(AreasSelectorClass);
    mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
    mainToolBar->setOrientation(Qt::Horizontal);
    AreasSelectorClass->addToolBar(static_cast<Qt::ToolBarArea>(4), mainToolBar);
    statusBar = new QStatusBar(AreasSelectorClass);
    statusBar->setObjectName(QString::fromUtf8("statusBar"));
    AreasSelectorClass->setStatusBar(statusBar);

    menuBar->addAction(menuFile->menuAction());
    menuBar->addAction(menuEdit->menuAction());
    menuBar->addAction(menuTools->menuAction());
    menuTools->addAction(actionProperties);
    menuEdit->addAction(actionUndo);
    menuEdit->addAction(actionRedo);
    menuFile->addAction(actionNew_Project);
    menuFile->addSeparator();
    menuFile->addAction(actionLoad_Project);
    menuFile->addAction(actionSave_Project);
    menuFile->addAction(actionLoad_Image);
    menuFile->addSeparator();
    menuFile->addAction(actionExit);

    retranslateUi(AreasSelectorClass);

    QMetaObject::connectSlotsByName(AreasSelectorClass);
    } // setupUi

    void retranslateUi(QMainWindow *AreasSelectorClass)
    {
    AreasSelectorClass->setWindowTitle(QApplication::translate("AreasSelectorClass", "Areas Selector Tool", 0, QApplication::UnicodeUTF8));
    actionLoad_Project->setText(QApplication::translate("AreasSelectorClass", "Load Project...", 0, QApplication::UnicodeUTF8));
    actionSave_Project->setText(QApplication::translate("AreasSelectorClass", "Save Project As...", 0, QApplication::UnicodeUTF8));
    actionLoad_Image->setText(QApplication::translate("AreasSelectorClass", "Load Image...", 0, QApplication::UnicodeUTF8));
    actionExit->setText(QApplication::translate("AreasSelectorClass", "Exit", 0, QApplication::UnicodeUTF8));
    actionProperties->setText(QApplication::translate("AreasSelectorClass", "Properties...", 0, QApplication::UnicodeUTF8));
    actionUndo->setText(QApplication::translate("AreasSelectorClass", "Undo", 0, QApplication::UnicodeUTF8));
    actionRedo->setText(QApplication::translate("AreasSelectorClass", "Redo", 0, QApplication::UnicodeUTF8));
    actionNew_Project->setText(QApplication::translate("AreasSelectorClass", "New Project", 0, QApplication::UnicodeUTF8));
    menuTools->setTitle(QApplication::translate("AreasSelectorClass", "Tools", 0, QApplication::UnicodeUTF8));
    menuEdit->setTitle(QApplication::translate("AreasSelectorClass", "Edit", 0, QApplication::UnicodeUTF8));
    menuFile->setTitle(QApplication::translate("AreasSelectorClass", "File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AreasSelectorClass: public Ui_AreasSelectorClass {};
} // namespace Ui

#endif // UI_AREASSELECTOR_H
