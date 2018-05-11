#ifndef NETWORK_H
#define NETWORK_H

#include "lib/json/json.hpp"
#include <QUdpSocket>
using json = nlohmann::json;

class network
{
    public:
        send(QString str, QHostAddress ip);
    private:
        sendPing(QHostAddress ip);
};

#endif // NETWORK_H
