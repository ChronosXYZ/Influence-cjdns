#include "handler.hpp"

Handler::Handler()
{
    network = new Network(false);
    connect(network, &Network::json_received, this, &Handler::handle);
}


void Handler::handle(QJsonObject jsonReceived)
{
    QJsonObject jsonSend;
    if(jsonReceived["action"] == "createSession" && !jsonReceived.contains("status"))
    {
        jsonSend["peerID"] = QHostAddress("fc8f:cc50:70b0:3731:d686:a75e:94f2:f44f").toString();
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
