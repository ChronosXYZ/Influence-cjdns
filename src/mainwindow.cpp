#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    network = new Network();
    handler = new Handler();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_connectToPeer_clicked()
{
    QJsonObject j;
    j["peerID"] = QHostAddress("::1").toString();
    j["action"] = "createSession";
    QString s = ui->peerID->text();
    network->sendDatagram(j, s);
    timer = new QTimer();
    connect(handler, &Handler::createSessionSuccess, this, &MainWindow::peerReceiverConnected);
    connect(timer, SIGNAL(timeout()), this, SLOT(slotTimerAlarm()));
    timer->start(10000);
}

void MainWindow::slotTimerAlarm()
{
    if(!receive)
    {
        int ret = QMessageBox::critical(this,QObject::tr("Error"),tr("Timeout Error"));
        timer->stop();
        delete timer;
    }

}

void MainWindow::peerReceiverConnected()
{
    receive = true;
    int ret = QMessageBox::information(this,QObject::tr("Info"),tr("Peer available!"));
}
