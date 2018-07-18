#pragma once

#include <QMainWindow>
#include "kernel/network.hpp"
#include "kernel/handler.hpp"
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();
    public slots:
        void peerReceiverAvailable();
    private slots:
        void on_connectToPeer_clicked();
        void slotTimerAlarm();

    private:
        Ui::MainWindow *ui;
        QTimer *timer;
        Network *network;
        Handler *handler;

    bool receive = false;
    const QString my_ipv6 = Network::local_ipv6();
};
