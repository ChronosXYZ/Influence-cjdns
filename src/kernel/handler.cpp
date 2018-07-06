#include "handler.hpp"

Handler::Handler()
{
    using namespace std::placeholders;

    handlers = {
        {"createSession", std::bind(&Handler::createSession, this, _1)},
        {"createSessionSuccess", std::bind(&Handler::createSessionSuccessMethod, this, _1)}
    };
    network = new Network();
    connect(network, &Network::json_received, this, &Handler::handle);
}


void Handler::handle(QJsonObject jsonReceived)
{
    QString action = jsonReceived["action"].toString();
    handlers[action](jsonReceived);
}

void Handler::createSession(QJsonObject jsonReceived)
{
    QJsonObject jsonSend;
    jsonSend["peerID"] = my_ipv6;
    jsonSend["action"] = "createSessionSuccess";
    QString peerReceiver = jsonReceived["peerID"].toString();
    network->sendDatagram(jsonSend, peerReceiver);
}

void Handler::createSessionSuccessMethod(QJsonObject jsonReceived)
{
    emit createSessionSuccess();
}
