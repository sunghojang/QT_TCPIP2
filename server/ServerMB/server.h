#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include <QtNetwork/QTcpServer>
#include <QBuffer>
#include <QtNetwork/QTcpSocket>
#include <QMessageBox>
#include <QDebug>
#include <QtNetwork>
namespace Ui {
class Server;
}

class Server : public QMainWindow
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = 0);
    ~Server();
signals:

private slots:
    void newConnection();
    void disconnected();
    void readyRead();
    void slot_receiveprocess(QByteArray);
private:
    Ui::Server *ui;
private:
    QTcpServer *server;
    QHash<QTcpSocket*, QByteArray*> buffers; //We need a buffer to store data until block has completely received
    QHash<QTcpSocket*, qint32*> sizes; //We need to store the size to verify if a block has received completely
    //QHash<QTcpSocket*, qint32*> cmmprcs; // We need to store the commend history to use multi client
    struct CommandData{
        int STX;
        int host;
        int cmm;
        int ETX;
        QString user;
        QString message;

    }*cmmdata_rx;
    enum {
        en_Null,en_STX,en_host,en_user,en_cmm,en_message,en_ETX,
    };
    int RProcess;
};

#endif // SERVER_H
