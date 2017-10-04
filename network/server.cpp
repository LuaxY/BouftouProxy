#include "server.h"
#include "client.h"
#include <QAbstractSocket>

Server::Server(QObject *parent) :
    Proxy(parent),
    QTcpServer(parent),
    client(nullptr)
{

}

void Server::start(ushort port)
{
    Proxy::start();
    listen(QHostAddress::Any, port);
}

void Server::incomingConnection(int descriptor)
{
    if (socket->state() != QAbstractSocket::UnconnectedState) {
        return;
    }

    if (!socket->setSocketDescriptor(descriptor)) {
        // TODO: error
        return;
    }

    client = new Client();
    client->start(this);
}

void Server::onMessage(IMessage *message)
{
    // TODO: alter messages;

    client->send(message);
}

