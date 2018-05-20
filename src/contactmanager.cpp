#include "contactmanager.h"

ContactManager::sendPing(QHostAddress ip)
{
	json ping;
	ping["peerID"] = QHostAddress::AnyIPv6.toString();
	ping["action"] = "ping";
	QString str = ping.dump();
	send(str, ip);
}
