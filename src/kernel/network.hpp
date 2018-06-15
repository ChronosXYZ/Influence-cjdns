#include "../lib/json/json.hpp"
#include <QtNetwork>

class Network
{
    using json = nlohmann::json;

    private:
        QUdpSocket* udpSocket;
    public:
        Network();
    public slots:
        void sendDatagram();
    private slots:
        void readPendingDatagrams();
};
