#include "server.h"
#include "ui_server.h"
static inline qint32 ArrayToInt(QByteArray source);
Server::Server(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Server)
{
    ui->setupUi(this);

    server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()), SLOT(newConnection()));
    connect(server, SIGNAL(dataReceived(QByteArray)), SLOT(slot_receiveprocess(QByteArray)));
    if (!server->listen(QHostAddress::Any, 4002)) {
        QMessageBox::critical(this, tr("Server"), tr("Unable to start the server: %1.").arg(server->errorString()));
        return;
    }
    ui->lb_statemessage->setText(QString("Server Open : %1").arg(server->serverPort()));

}

Server::~Server()
{
    delete ui;
}
void Server::newConnection()
{
    qDebug() << "void Server::newConnection()";
    while (server->hasPendingConnections())
    {
        QTcpSocket *socket = server->nextPendingConnection();
        connect(socket, SIGNAL(readyRead()), SLOT(readyRead()));
        connect(socket, SIGNAL(disconnected()), SLOT(disconnected()));
        connect(this, SIGNAL( Signal_display(CommandData*)),this, SLOT(slot_Display(CommandData*)));
        QByteArray *buffer = new QByteArray();
        cmmdata_rx = new CommandData();
        qint32 *s = new qint32(0);
        buffers.insert(socket, buffer);
        sizes.insert(socket, s);
        qDebug() << buffers;

        QList<QTcpSocket*> values = buffers.keys();
        for (int i = 0; i < values.size(); ++i){
            qDebug() <<"Soket List:"<< values.at(i);

        }

        //ui->lw_clientlist->insertItem(values.size(),QString("%1").arg("values"));

    }
}

void Server::disconnected()
{
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    QByteArray *buffer = buffers.value(socket);
    qint32 *s = sizes.value(socket);
    socket->deleteLater();
    delete buffer;
    delete s;
}

void Server::readyRead()
{
    qDebug() << "void Server::readyRead()";
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    QByteArray *buffer = buffers.value(socket);
    qint32 *s = sizes.value(socket);
    qint32 size = *s;
    while (socket->bytesAvailable() > 0)
    {
        buffer->append(socket->readAll());
        while ((size == 0 && buffer->size() >= 4) || (size > 0 && buffer->size() >= size)) //While can process data, process it
        {

            if (size == 0 && buffer->size() >= 4) //if size of data has received completely, then store it on our global variable
            {
                size = ArrayToInt(buffer->mid(0, 4));
                *s = size;
                qDebug()<<"size :"<<size;
                buffer->remove(0, 4);
            }
            if (size > 0 && buffer->size() >= size) // If data has received completely
            {
                QByteArray data = buffer->mid(0, size);
                buffer->remove(0, size);
                size = 0;
                *s = size;
//                qDebug() << data.toHex();
//                QString DataAsString = QString::fromAscii(data.data());
//                qDebug() << DataAsString;
                slot_receiveprocess(data);

            }
        }
    }
}

qint32 ArrayToInt(QByteArray source)
{
    qint32 temp;
    QDataStream data(&source, QIODevice::ReadWrite);
    data >> temp;
    return temp;
}
void Server::slot_receiveprocess(QByteArray data){
    qDebug()<<"void Server::slot_receiveprocess(QTcpSocket* soket,QByteArray data)";
    uchar sftbyte = 4;
    int temp4byte = 0;
    QString tempQstring = "";
    RProcess = en_STX;
    while(!data.isEmpty()){
        switch(RProcess){
        case en_STX:
            sftbyte = 4;
            temp4byte = ArrayToInt(data.mid(0, sftbyte));
            data.remove(0,sftbyte);
            if(temp4byte == 0x8E){
                cmmdata_rx->STX = temp4byte;
                RProcess = en_host;
            }
            break;
        case en_host:
            sftbyte = 4;
            temp4byte = ArrayToInt(data.mid(0, sftbyte));
            data.remove(0,sftbyte);

            cmmdata_rx->host = temp4byte;
            RProcess = en_user;

            break;
        case en_user:
            sftbyte = 4;
            temp4byte = ArrayToInt(data.mid(0, sftbyte));
            data.remove(0,sftbyte);
            sftbyte = temp4byte;

            tempQstring = QString::fromAscii(data.mid(0, sftbyte).data());
            data.remove(0,sftbyte);
            if(tempQstring.size() == sftbyte){
                cmmdata_rx->user = tempQstring;
                RProcess = en_cmm;
            }
            break;
        case en_cmm:
            sftbyte = 4;
            temp4byte = ArrayToInt(data.mid(0, sftbyte));
            data.remove(0,sftbyte);

            cmmdata_rx->cmm = temp4byte;
            RProcess = en_message;

            break;

        case en_message:
            sftbyte = 4;
            temp4byte = ArrayToInt(data.mid(0, sftbyte));
            data.remove(0,sftbyte);
            sftbyte = temp4byte;

            tempQstring = QString::fromAscii(data.mid(0, sftbyte).data());
            data.remove(0,sftbyte);
            if(tempQstring.size() == sftbyte){
                cmmdata_rx->message = tempQstring;
                RProcess = en_ETX;
            }
            break;
        case en_ETX:
            sftbyte = 4;
            temp4byte = ArrayToInt(data.mid(0, sftbyte));
            data.remove(0,sftbyte);
            if(temp4byte == 0x8F){
                cmmdata_rx->ETX = temp4byte;
                RProcess = en_STX;
                qDebug()<<"Signal_display(cmmdata_rx)";
                emit Signal_display(cmmdata_rx);
            }
            break;
        case en_Null:
            break;
        default:
            qDebug("default case");
            break;
        }


    }
    qDebug() <<    cmmdata_rx->STX ;
    qDebug() <<    cmmdata_rx->host;
    qDebug() <<    cmmdata_rx->user ;
    qDebug() <<    cmmdata_rx->cmm ;
    qDebug() <<    cmmdata_rx->message ;
    qDebug() <<    cmmdata_rx->ETX ;
}
void Server::slot_Display(CommandData *arg){
    qDebug()<<"void Server::slot_Display(CommandData *arg)";
    ui->te_diplaylog->append(QString("host num : %1").arg(cmmdata_rx->host));
    ui->te_diplaylog->append(QString("user : %1").arg(cmmdata_rx->user));
    ui->te_diplaylog->append(QString("command : %1").arg(cmmdata_rx->cmm));
    ui->te_diplaylog->append(QString("message : %1").arg(cmmdata_rx->message));
}
