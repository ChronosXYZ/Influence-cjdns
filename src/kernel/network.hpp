#pragma once

#include <QtNetwork>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkInterface>

class Network : public QObject
{
    Q_OBJECT

    private:
        QUdpSocket* udpSocket;
    public:
        Network(bool is_server = true);
        static QString local_ipv6();
    public slots:
        void sendDatagram(QJsonObject j, QString s);
    signals:
        void json_received(QJsonObject &jsonReceived);
    private slots:
        void processTheDatagram();
};
