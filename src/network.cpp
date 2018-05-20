#include "network.h"

class Network
{
    Network()
    {
        socket = new QUdpSocket(this);
        socket->bind(QHostAddress::AnyIPv6, 6552);
        connect(socket, SIGNAL(readyRead()), SLOT(read()));
    }
    void send(QString str, QHostAddress ip)
    {
        QByteArray data;
        QDataStream out(&data, QIODevice::WriteOnly);
        out << qint64(0);
        out << str;
        out.device()->seek(qint64(0));
        out << qint64(data.size() - sizeof(qint64));
        socket->writeDatagram(data, QHostAddress(ip), 6552);
    }
    void read()
    {
      QByteArray buffer;
      buffer.resize(socket->pendingDatagramSize());
      socket->readDatagram(buffer.data(), buffer.size(),
                           &sender;, &senderPort;);
      qDebug() << "Message from: " << sender.toString();
      qDebug() << "Message: " << buffer;
    }
}
