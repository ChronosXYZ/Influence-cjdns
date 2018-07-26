#pragma once

#include <QMainWindow>
#include "kernel/network.hpp"
#include "kernel/handler.hpp"
#include "chatwindow.hpp"
#include <QUuid>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>
#include <QObject>


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();
        QVector<ChatWindow*> pChatWindows;
        void setButtonToWaiting();
        void setButtonToConnect();
    public slots:
        void peerReceiverAvailable();
    private slots:
        void on_connectToPeer_clicked();
        void slotTimerAlarm();
        void createChatFailedMethod();
        void createChat(QString peerID, QString chatID);
        void deleteChatMethod(QString cID);
        void msgReceivedMethod(QString peerID, QString chatID, QString msgText);
        void peerReceiverLeftFromChatMethod(QString peerID, QString chatID);
    private:
        void createChatSendDatagram(QString peerReceiver);
        Ui::MainWindow *ui;
        QTimer *timer;
        Network *network;
        Handler *handler;
        bool receive = false;
};
