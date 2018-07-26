#include "handler.hpp"

Handler::Handler()
{
    using namespace std::placeholders;

    handlers = {
        {"checkPeer", std::bind(&Handler::checkPeer, this, _1)},
        {"checkPeerSuccess", std::bind(&Handler::checkPeerSuccessMethod, this, _1)},
        {"createChat", std::bind(&Handler::createChatMethod, this, _1)},
        {"createChatSuccess", std::bind(&Handler::createChatSuccessMethod, this, _1)},
        {"createChatFailed", std::bind(&Handler::createChatFailedMethod, this, _1)},
        {"msgSend", std::bind(&Handler::msgReceiveMethod, this, _1)},
        {"leftChat", std::bind(&Handler::peerReceiverLeftFromChatMethod, this, _1)}
    };
    peerReceiver = new QString();
    network = new Network();
    connect(network, &Network::jsonReceived, this, &Handler::handle);
}


void Handler::handle(QJsonObject jsonReceived)
{
    QString action = jsonReceived["action"].toString();
    *peerReceiver = jsonReceived["peerID"].toString();
    handlers[action](jsonReceived);
}

void Handler::checkPeer(QJsonObject jsonReceived)
{
    QJsonObject jsonSend;
    jsonSend["peerID"] = *network->myIPv6;
    jsonSend["action"] = "checkPeerSuccess";
    network->sendDatagram(jsonSend, *peerReceiver);
}

void Handler::checkPeerSuccessMethod(QJsonObject jsonReceived)
{
    emit checkPeerSuccess();
}

Handler::~Handler()
{
    delete peerReceiver;
    delete network;
    //delete handlers;
}

void Handler::createChatMethod(QJsonObject jsonReceived)
{
    QWidget *parent = 0;
    QString msgTitle;
    QString msg;
    msgTitle += "Create chat";
    msg += tr("Peer ");
    msg += *peerReceiver;
    msg += tr(" want to create chat with you.\n");
    msg += tr("Do you want to create chat?");
    int ret = QMessageBox::warning(parent, msgTitle, msg, QMessageBox::Yes | QMessageBox::No);
    if(ret == QMessageBox::Yes)
    {
        QJsonObject jsonSend;
        jsonSend["peerID"] = *network->myIPv6;
        jsonSend["action"] = "createChatSuccess";
        jsonSend["chatID"] = jsonReceived["chatUUID"].toString();
        network->sendDatagram(jsonSend, *peerReceiver);
        emit createChatSuccess(jsonReceived["peerID"].toString(), jsonReceived["chatUUID"].toString());
    }
    else
    {
        QJsonObject jsonSend;
        jsonSend["peerID"] = *network->myIPv6;
        jsonSend["action"] = "createChatFailed";
        network->sendDatagram(jsonSend, *peerReceiver);
    }
}

void Handler::createChatFailedMethod(QJsonObject jsonReceived)
{
    QString msg;
    msg += tr("Peer ");
    msg += *peerReceiver;
    msg += tr(" refused to create a chat with you");
    QWidget *parent = 0;
    QMessageBox::critical(parent, tr("Create chat failed!"), msg, QMessageBox::Ok);
    emit createChatFailed();
}

void Handler::createChatSuccessMethod(QJsonObject jsonReceived)
{
    emit createChatSuccess(jsonReceived["peerID"].toString(), jsonReceived["chatID"].toString());
}

void Handler::msgReceiveMethod(QJsonObject jsonReceived)
{
    emit msgReceived(jsonReceived["peerID"].toString(), jsonReceived["chatID"].toString(), jsonReceived["msgText"].toString());
}

void Handler::peerReceiverLeftFromChatMethod(QJsonObject jsonReceived)
{
    emit peerReceiverLeftFromChat(jsonReceived["peerID"].toString(), jsonReceived["chatID"].toString());
}
