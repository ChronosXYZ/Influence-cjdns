#include "handler.hpp"

Handler::Handler()
{
    network = new Network();
    connect(network, &Network::json_received, this, &Handler::handle);
}


void Handler::handle(QJsonObject jsonReceived)
{
    QJsonObject jsonSend;
    if(jsonReceived["action"] == "createSession" && !jsonReceived.contains("status"))
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
