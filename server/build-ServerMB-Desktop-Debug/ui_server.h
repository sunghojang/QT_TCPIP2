/********************************************************************************
** Form generated from reading UI file 'server.ui'
**
** Created: Wed Aug 22 19:31:21 2018
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVER_H
#define UI_SERVER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Server
{
public:
    QWidget *centralWidget;
    QLabel *lb_statemessage;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Server)
    {
        if (Server->objectName().isEmpty())
            Server->setObjectName(QString::fromUtf8("Server"));
        Server->resize(400, 300);
        centralWidget = new QWidget(Server);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        lb_statemessage = new QLabel(centralWidget);
        lb_statemessage->setObjectName(QString::fromUtf8("lb_statemessage"));
        lb_statemessage->setGeometry(QRect(25, 25, 351, 16));
        Server->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Server);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 20));
        Server->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Server);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        Server->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Server);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Server->setStatusBar(statusBar);

        retranslateUi(Server);

        QMetaObject::connectSlotsByName(Server);
    } // setupUi

    void retranslateUi(QMainWindow *Server)
    {
        Server->setWindowTitle(QApplication::translate("Server", "Server", 0, QApplication::UnicodeUTF8));
        lb_statemessage->setText(QApplication::translate("Server", "State Message", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Server: public Ui_Server {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVER_H
