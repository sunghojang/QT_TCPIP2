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
    connect(server, SIGNAL(dataReceived(QTcpSocket*,QByteArray)), SLOT(slot_receiveprocess(QTcpSocket*,QByteArray)));
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
        QByteArray *buffer = new QByteArray();
        qint32 *s = new qint32(0);
        buffers.insert(socket, buffer);
        sizes.insert(socket, s);
        cmmprcs.insert(socket, en_Null);
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
                buffer->remove(0, 4);
            }
            if (size > 0 && buffer->size() >= size) // If data has received completely, then emit our SIGNAL with the data
            {
                QByteArray data = buffer->mid(0, size);
                buffer->remove(0, size);
                size = 0;
                *s = size;
//                qDebug() << data.toHex();
//                QString DataAsString = QString::fromAscii(data.data());
//                qDebug() << DataAsString;
                emit dataReceived(socket,data);
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
void Server::slot_receiveprocess(QTcpSocket* soket,QByteArray data){
    int prcsStep = cmmprcs.value(soket);
}
