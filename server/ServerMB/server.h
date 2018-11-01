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
private:
    Ui::Server *ui;
private:
    int RProcess;
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
public:
    explicit Server(QWidget *parent = 0);
    ~Server();
     QList<QNetworkInterface> InterfaceList ;
     QList<QNetworkAddressEntry> ipAddrList;
     double cnt;
private:
    int get_interface();
    int get_interface_ipaddress(int index);

signals:
     void Signal_display(CommandData *arg);
private slots:
    void newConnection();
    void disconnected();
    void readyRead();
    void slot_receiveprocess(QByteArray);
    void slot_Display(CommandData *arg);
    void on_lw_netseleect_clicked(const QModelIndex &index);

    void on_button_serveropen_clicked();
    void on_button_Serverclose_clicked();
};

#endif // SERVER_H
