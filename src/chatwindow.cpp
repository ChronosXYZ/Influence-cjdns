#include "chatwindow.hpp"
#include "ui_chatwindow.h"

ChatWindow::ChatWindow(QString pID, QString cUUID, Handler *h, Network *n, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatWindow)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    chatID = cUUID;
    peerID = pID;
    handler = h;
    network = n;
    ui->peerIDLabel->setText(ui->peerIDLabel->text() + pID);
    ui->chatIDLabel->setText(ui->chatIDLabel->text() + cUUID);
    connect(ui->sendMsgButton, &QAbstractButton::clicked, this, &ChatWindow::sendMsgButtonClicked);
}
ChatWindow::~ChatWindow()
{
    leftFromChat();
    emit deleteChat(chatID);
    delete ui;
    this->deleteLater();
}

void ChatWindow::sendMessage(QString msgText)
{
    QJsonObject jSend;
    jSend["action"] = "msgSend";
    jSend["peerID"] = *network->myIPv6;
    jSend["chatID"] = chatID;
    jSend["msgText"] = msgText;
    network->sendDatagram(jSend, peerID);
    QDateTime date(QDateTime::currentDateTime());
    ui->chatEdit->append("<i>[" + date.toString() + "]</i> " + tr("<b>You</b>: ") + msgText);
}

void ChatWindow::sendMsgButtonClicked()
{
    QString msg = ui->msgEdit->text();
    sendMessage(msg);
    ui->msgEdit->setText("");
}

void ChatWindow::displayMsg(QString msgText)
{
    QDateTime date(QDateTime::currentDateTime());
    ui->chatEdit->append("<i>[" + date.toString() + "]</i> " + "<b>" + peerID + "</b>" + ": " + msgText);
}

void ChatWindow::leftFromChat()
{
    QJsonObject json;
    json["action"] = "leftChat";
    json["peerID"] = *network->myIPv6;
    json["chatID"] = chatID;
    network->sendDatagram(json, peerID);
}

void ChatWindow::peerReceiverLeftFromChat()
{
    QString msg;
    msg += tr("Peer ");
    msg += peerID;
    msg += tr(" left from this chat.");
    QMessageBox::warning(this, tr("Peer receiver left from chat!"), msg, QMessageBox::Ok);
    ui->chatEdit->append("<b>" + peerID + "</b>" + tr(" left from this chat."));
    ui->msgEdit->setEnabled(false);
    ui->sendMsgButton->setEnabled(false);
}
