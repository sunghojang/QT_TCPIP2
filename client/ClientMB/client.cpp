#include "client.h"
#include "ui_client.h"
static inline QByteArray IntToArray(qint32 source);
Client::Client(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    connect(ui->bt_hostconnect  ,SIGNAL(clicked(bool))  ,this,SLOT(connectToHost())             );
    get_ipaddress();
}

Client::~Client()
{
    delete ui;
}
QString Client::get_ipaddress(){
    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        qDebug()<<ipAddressesList.at(i);
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            qDebug()<<ipAddress;
            //not LocalHost, and ip is Ipv4 address
            break;
        }
    }
    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    ui->hostLineEdit->setText(ipAddress);
    return ipAddress;
}

bool Client::connectToHost()
{
    socket->connectToHost(ui->hostLineEdit->text(),
                          ui->portLineEdit->text().toInt());
    return socket->waitForConnected();
}

bool Client::writeData(QByteArray data)
{
    qDebug() << "bool Client::writeData(QByteArray data)";
    if(socket->state() == QAbstractSocket::ConnectedState)
    {
        socket->write(IntToArray(data.size())); //write size of data
        socket->write(data); //write the data itself
        return socket->waitForBytesWritten();
    }
    else
        return false;
}
QByteArray IntToArray(qint32 source) //Use qint32 to ensure that the number have 4 bytes
{
    //Avoid use of cast, this is the Qt way to serialize objects
    QByteArray temp;
    QDataStream data(&temp, QIODevice::ReadWrite);
    data << source;
    return temp;
}

void Client::on_bt_bytearrysend_clicked()
{
    writeData(QByteArray::fromHex("FEFF0633064406270645aaaaaaaaaaaaaaaaaaaaaaaaaa"));
}