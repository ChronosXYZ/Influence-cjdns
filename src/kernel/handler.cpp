#include "handler.hpp"

Handler::Handler()
{
    network = new Network();
    connect(network, &Network::json_received, this, &Handler::handle);
}


void Handler::handle(QJsonObject jsonReceived)
{
    using namespace std::placeholders;
    std::map<QString, std::function<void(QJsonObject)>> handlers = {
        {"createSession", std::bind(&Handler::createSession, this, _1)}
    };

    QString action = jsonReceived["action"].toString();
    handlers[action](jsonReceived);
}

void Handler::createSession(QJsonObject jsonReceived)
{
    QJsonObject jsonSend;
    if(jsonReceived.contains("status") != true)
    {
        jsonSend["peerID"] = my_ipv6;
        jsonSend["action"] = "createSession";
        jsonSend["status"] = true;
        QString peerReceiver = jsonReceived["peerID"].toString();
        network->sendDatagram(jsonSend, peerReceiver);
     }
     else
     {
        emit createSessionSuccess();
     }
}
