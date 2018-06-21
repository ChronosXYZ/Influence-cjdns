#include "network.hpp"
Network::Network(bool is_server)
{
    udpSocket = new QUdpSocket(this);
    if (is_server)
    {
        udpSocket->bind(QHostAddress::AnyIPv6, 6552);
        connect(udpSocket, SIGNAL(readyRead()), this, SLOT(processTheDatagram()));
    }
}

void Network::sendDatagram(QJsonObject j, QString s)
{
    QHostAddress ip = QHostAddress(s);
    QByteArray baDatagram;
    //QDataStream out(&baDatagram, QIODevice::WriteOnly);
    QJsonDocument jbuff = QJsonDocument(j);
    quint16 p = 6552;
    baDatagram = jbuff.toJson(QJsonDocument::Compact);
    udpSocket->writeDatagram(baDatagram, ip, p);
}

void Network::processTheDatagram()
{
    QByteArray baDatagram;
    do {
        baDatagram.resize(udpSocket->pendingDatagramSize ()) ;
        udpSocket->readDatagram (baDatagram.data(), baDatagram.size()) ;
    } while (udpSocket->hasPendingDatagrams()) ;

    QJsonDocument jbuff = QJsonDocument::fromJson(baDatagram);
    QJsonObject j = QJsonObject(jbuff.object());
    //QDataStream in(&baDatagram, QIODevice::ReadOnly);
    //in >> jbuff.fromBinaryData(baDatagram);
    emit json_received(j);
}
