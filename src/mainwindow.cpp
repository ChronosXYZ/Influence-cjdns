#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    network = new Network(false);
    handler = new Handler();
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(slotTimerAlarm()));
    connect(handler, &Handler::checkPeerSuccessSuccess, this, &MainWindow::peerReceiverAvailable);
    ui->myIP->setText(my_ipv6);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_connectToPeer_clicked()
{
    ui->connectToPeer->setEnabled(false);
    ui->connectToPeer->setText("Ожидание...");
    QJsonObject j;
    j["peerID"] = my_ipv6;
    j["action"] = "checkPeer";
    QString s = ui->peerID->text();
    network->sendDatagram(j, s);
    timer->start(10000);
}

void MainWindow::slotTimerAlarm()
{
    if(receive == true)
    {
        timer->stop();
        receive = false;
    }
    else
    {
        int ret = QMessageBox::critical(this,QObject::tr("Error"),tr("Timeout Error"));
        timer->stop();
        ui->connectToPeer->setEnabled(true);
        ui->connectToPeer->setText("Подключиться");
    }

}

void MainWindow::peerReceiverAvailable()
{
    receive = true;
    int ret = QMessageBox::information(this,QObject::tr("Info"),tr("Peer Available!"));
    ui->connectToPeer->setEnabled(true);
    ui->connectToPeer->setText("Подключиться");
}
