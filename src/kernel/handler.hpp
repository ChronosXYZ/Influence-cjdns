#pragma once

#include "network.hpp"
#include <QJsonObject>

class Handler : public QObject
{
    Q_OBJECT

    const QString my_ipv6 = Network::local_ipv6();

    public:
        Handler();
    signals:
        void checkPeerSuccess();
    private:
        Network *network;
        void createSession(QJsonObject jsonReceived);
        std::map<QString, std::function<void(QJsonObject)>> handlers;
        void checkPeerSuccessMethod(QJsonObject jsonReceived);
    private slots:
        void handle(QJsonObject jsonReceived);
};
