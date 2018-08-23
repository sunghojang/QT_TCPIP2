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
    struct CommandData{
        int STX;
        int host;
        int cmm;
        int ETX;
        QString user;
        QString message;

    }*cmmdata_tx;
    QByteArray parse(CommandData *src) {
        QByteArray data;
        QDataStream out(&data, QIODevice::WriteOnly);
        out.setByteOrder(QDataStream::BigEndian);
        out
                << (qint32)sizeof(CommandData)
                << src->STX
                << src->host
                << src->user.toAscii()
                << src->cmm
                << src->message.toAscii()
                << src->ETX
                   ;
        return data;
    }
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
