#pragma once

#include <QtNetwork>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkInterface>

class Network : public QObject
{
    Q_OBJECT


    public:
        Network(bool is_server = true);
        ~Network();
        static QString localIPv6();
        const QString *myIPv6;
    private:
        QUdpSocket* udpSocket;
    public slots:
        void sendDatagram(QJsonObject j, QString s);
    signals:
        void jsonReceived(QJsonObject &jsonReceived);
    private slots:
        void processTheDatagram();
};
