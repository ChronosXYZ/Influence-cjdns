#include "contactmanager.h"

ContactManager::sendPing(QHostAddress ip)
{
	json ping;
	ping["peerID"] = QHostAddress::AnyIPv6;
	ping["action"] = "ping";
	QString str = ping.dump();
	Network::send(str, ip);
}
