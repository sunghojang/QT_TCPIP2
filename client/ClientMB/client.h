#ifndef CLIENT_H
#define CLIENT_H
#include <QtGui>
#include <QMainWindow>
#include <QtNetwork/QTcpServer>
#include <QBuffer>
#include <QtNetwork/QTcpSocket>
#include <QMessageBox>
#include <QDebug>
#include <QtNetwork>
#include <QPushButton>
namespace Ui {
class Client;
}

class Client : public QMainWindow
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = 0);
    QString get_ipaddress();
    ~Client();
public slots:
    bool connectToHost();
    bool writeData(QByteArray data);

private slots:
    void on_bt_bytearrysend_clicked();

private:
    Ui::Client *ui;
    QTcpSocket *socket;
};

#endif // CLIENT_H
