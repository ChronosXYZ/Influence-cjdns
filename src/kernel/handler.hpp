#pragma once

#include "network.hpp"
#include <QJsonObject>
#include <QMessageBox>

class Handler : public QObject
{
    Q_OBJECT

    public:
        Handler();
        ~Handler();
        QString *peerReceiver;
    private:
        Network *network;
        void checkPeer(QJsonObject jsonReceived);
        std::map<QString, std::function<void(QJsonObject)>> handlers;
        void checkPeerSuccessMethod(QJsonObject jsonReceived);
        void createChatMethod(QJsonObject jsonReceived);
        void createChatSuccessMethod(QJsonObject jsonReceived);
        void createChatFailedMethod(QJsonObject jsonReceived);
        void msgReceiveMethod(QJsonObject jsonReceived);
        void peerReceiverLeftFromChatMethod(QJsonObject jsonReceived);
    signals:
        void checkPeerSuccess();
        void createChatSuccess(QString peerID, QString chatID);
        void createChatFailed();
        void msgReceived(QString peerID, QString chatID, QString msgText);
        void peerReceiverLeftFromChat(QString peerID, QString chatID);
    private slots:
        void handle(QJsonObject jsonReceived);
};
