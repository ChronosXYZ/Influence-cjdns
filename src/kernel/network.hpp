#pragma once

#include <QtNetwork>
#include <QJsonObject>
#include <QJsonDocument>

class Network : public QObject
{
    Q_OBJECT

    private:
        QUdpSocket* udpSocket;
    public:
        Network();
    public slots:
        void sendDatagram(QJsonObject j, QString s);
    signals:
        void json_received(QJsonObject &jsonReceived);
    private slots:
        void processTheDatagram();
};
