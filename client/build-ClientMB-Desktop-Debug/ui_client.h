/********************************************************************************
** Form generated from reading UI file 'client.ui'
**
** Created: Wed Aug 22 19:18:49 2018
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENT_H
#define UI_CLIENT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Client
{
public:
    QWidget *centralWidget;
    QLineEdit *hostLineEdit;
    QLineEdit *portLineEdit;
    QPushButton *bt_hostconnect;
    QPushButton *bt_bytearrysend;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Client)
    {
        if (Client->objectName().isEmpty())
            Client->setObjectName(QString::fromUtf8("Client"));
        Client->resize(583, 339);
        centralWidget = new QWidget(Client);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        hostLineEdit = new QLineEdit(centralWidget);
        hostLineEdit->setObjectName(QString::fromUtf8("hostLineEdit"));
        hostLineEdit->setGeometry(QRect(10, 5, 113, 23));
        portLineEdit = new QLineEdit(centralWidget);
        portLineEdit->setObjectName(QString::fromUtf8("portLineEdit"));
        portLineEdit->setGeometry(QRect(10, 35, 113, 23));
        bt_hostconnect = new QPushButton(centralWidget);
        bt_hostconnect->setObjectName(QString::fromUtf8("bt_hostconnect"));
        bt_hostconnect->setGeometry(QRect(135, 5, 76, 51));
        bt_bytearrysend = new QPushButton(centralWidget);
        bt_bytearrysend->setObjectName(QString::fromUtf8("bt_bytearrysend"));
        bt_bytearrysend->setGeometry(QRect(250, 5, 126, 106));
        Client->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Client);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 583, 20));
        Client->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Client);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        Client->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Client);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Client->setStatusBar(statusBar);

        retranslateUi(Client);

        QMetaObject::connectSlotsByName(Client);
    } // setupUi

    void retranslateUi(QMainWindow *Client)
    {
        Client->setWindowTitle(QApplication::translate("Client", "Client", 0, QApplication::UnicodeUTF8));
        hostLineEdit->setText(QApplication::translate("Client", "ip address", 0, QApplication::UnicodeUTF8));
        portLineEdit->setText(QApplication::translate("Client", "4002", 0, QApplication::UnicodeUTF8));
        bt_hostconnect->setText(QApplication::translate("Client", "Connect", 0, QApplication::UnicodeUTF8));
        bt_bytearrysend->setText(QApplication::translate("Client", "SEND", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Client: public Ui_Client {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENT_H
