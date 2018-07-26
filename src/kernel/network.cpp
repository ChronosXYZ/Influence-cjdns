#include "network.hpp"

Network::Network(bool is_server)
{
    udpSocket = new QUdpSocket(this);
    if (is_server)
    {
        udpSocket->bind(QHostAddress::AnyIPv6, 6552);
        connect(udpSocket, SIGNAL(readyRead()), this, SLOT(processTheDatagram()));
    }
    myIPv6 = new QString(localIPv6());
}

void Network::sendDatagram(QJsonObject j, QString s)
{
    QHostAddress ip = QHostAddress(s);
    QByteArray baDatagram;
    QJsonDocument jbuff = QJsonDocument(j);
    quint16 p = 6552;
    baDatagram = jbuff.toJson(QJsonDocument::Compact);
    udpSocket->writeDatagram(baDatagram, ip, p);
}

void Network::processTheDatagram()
{
    QByteArray baDatagram;
    do {
        baDatagram.resize(udpSocket->pendingDatagramSize()) ;
        udpSocket->readDatagram (baDatagram.data(), baDatagram.size()) ;
    } while (udpSocket->hasPendingDatagrams()) ;

    QJsonDocument jbuff = QJsonDocument::fromJson(baDatagram);
    QJsonObject j = QJsonObject(jbuff.object());
    emit jsonReceived(j);
}

QString Network::localIPv6()
{
    QHostAddress address;
    QString addressString;
    foreach (address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv6Protocol && address != QHostAddress(QHostAddress::LocalHostIPv6) && (address.toString()).contains("fc"))
        {
            addressString = address.toString();
            break;
        }
        else
        {
            addressString = "null";
        }
    }
    return(addressString);
}

Network::~Network()
{
    delete udpSocket;
    delete myIPv6;
}
