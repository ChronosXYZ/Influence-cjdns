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
    connect(handler, &Handler::checkPeerSuccess, this, &MainWindow::peerReceiverAvailable);
    connect(handler, &Handler::createChatSuccess, this, &MainWindow::createChat);
    connect(handler, &Handler::createChatFailed, this, &MainWindow::createChatFailedMethod);
    connect(handler, &Handler::msgReceived, this, &MainWindow::msgReceivedMethod);
    connect(handler, &Handler::peerReceiverLeftFromChat, this, &MainWindow::peerReceiverLeftFromChatMethod);
    ui->myIP->setText(*network->myIPv6);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete network;
    delete handler;
    delete timer;
}

void MainWindow::on_connectToPeer_clicked()
{
    setButtonToWaiting();
    QJsonObject j;
    j["peerID"] = *network->myIPv6;
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
        QMessageBox::critical(this, tr("Error"), tr("Timeout Error"));
        timer->stop();
        setButtonToConnect();
    }

}

void MainWindow::peerReceiverAvailable()
{
    receive = true;
    int ret = QMessageBox::information(this, tr("Peer Available!"),
                                         tr("Peer Available!\n Do you want to create chat?"), QMessageBox::Yes | QMessageBox::No);
    if(ret == QMessageBox::Yes)
    {
        createChatSendDatagram(*handler->peerReceiver);
    }
    else
    {
        setButtonToConnect();
    }
}

void MainWindow::setButtonToWaiting() // Function, which sets button "connectToPeer" in status "Waiting..."
{
    ui->connectToPeer->setEnabled(false);
    ui->connectToPeer->setText(tr("Waiting..."));
}

void MainWindow::setButtonToConnect() // Function, which sets button "connectToPeer" in status "Connect"
{
    ui->connectToPeer->setEnabled(true);
    ui->connectToPeer->setText(tr("Connect"));
}

void MainWindow::createChatSendDatagram(QString peerReceiver)
{
    QUuid chatID = QUuid::createUuid();
    QJsonObject jSend;
    jSend["action"] = "createChat";
    jSend["peerID"] = *network->myIPv6;
    jSend["chatUUID"] = chatID.toString();
    network->sendDatagram(jSend, peerReceiver);
}

void MainWindow::createChat(QString peerID, QString chatID)
{
    pChatWindows.push_back(new ChatWindow(peerID, chatID, handler, network));
    connect(pChatWindows.back(), &ChatWindow::deleteChat, this, &MainWindow::deleteChatMethod);
    pChatWindows.back()->show();
    setButtonToConnect();
}

void MainWindow::createChatFailedMethod()
{
    setButtonToConnect();
}

void MainWindow::deleteChatMethod(QString cID)
{
    for(int i = 0; i < pChatWindows.size(); i++)
    {
        if(pChatWindows.at(i)->chatID == cID)
        {
            pChatWindows.remove(i);
            break;
        }
    }
}

void MainWindow::msgReceivedMethod(QString peerID, QString chatID, QString msgText)
{
    for(int i = 0; i < pChatWindows.size(); i++)
    {
        if(pChatWindows.at(i)->peerID == peerID && pChatWindows.at(i)->chatID == chatID)
        {
            pChatWindows.at(i)->displayMsg(msgText);
        }
    }
}

void MainWindow::peerReceiverLeftFromChatMethod(QString peerID, QString chatID)
{
    for(int i = 0; i < pChatWindows.size(); i++)
    {
        if(pChatWindows.at(i)->peerID == peerID && pChatWindows.at(i)->chatID == chatID)
        {
            pChatWindows.at(i)->peerReceiverLeftFromChat();
        }
    }
}
