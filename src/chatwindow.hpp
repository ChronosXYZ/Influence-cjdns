#pragma once

#include <QWidget>
#include <QJsonObject>
#include "kernel/handler.hpp"
#include "kernel/network.hpp"

namespace Ui {
    class ChatWindow;
}

class ChatWindow : public QWidget
{
    Q_OBJECT

    public:
        explicit ChatWindow(QString pID, QString cUUID, Handler *h, Network *n, QWidget *parent = 0);
        ~ChatWindow();
        QString chatID;
        QString peerID;
        Handler *handler;
        Network *network;
        void displayMsg(QString msgText);
        void peerReceiverLeftFromChat();
    private:
        Ui::ChatWindow *ui;
        void sendMessage(QString msgText);
        void leftFromChat();
    signals:
        void deleteChat(QString cID);
    private slots:
        void sendMsgButtonClicked();
};
