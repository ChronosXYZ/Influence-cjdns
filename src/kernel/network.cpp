Network::Network()
{
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::AnyIPv6, 6552);
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
}
void Network::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = udpSocket->receiveDatagram();
        processTheDatagram(datagram);
    }
}
void Network::sendDatagram(json *j, QHostAddress ip)
{
    QByteArray baDatagram;
    QDataStream out(&baDatagram, QIODevice::WriteOnly);
    QString s = j.dump();
    out << s;
    udpSocket->writeDatagram(baDatagram, ip, 6552);
}
json Network::processTheDatagram()
{
    QByteArray baDatagram;
    do {
        baDatagram.resize(udpSocket->pendingDatagramSize ()) ;
        udpSocket->readDatagram (baDatagram.data(), baDatagram.size()) ;
    } while (udpSocket->hasPendingDatagrams()) ;

    QString buff;
    QDataStream in(&baDatagram, QIODevice::Readonly);
    in >> buff;
    json j = new json;
    j = json::parse(buff);
    return json;
}
