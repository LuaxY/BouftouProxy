#include "client.h"
#include "server.h"

Client::Client(QObject *parent) : Proxy(parent, "SRV")
{
}

void Client::start(Server* _server)
{
    Proxy::start();
    socket->connectToHost("213.248.126.39", 5555);

    server = _server;
}

void Client::onMessage(IMessage *message)
{
    // TODO: alter messages;

    server->send(message);
}

void Client::onStateChanged(QAbstractSocket::SocketState state)
{
    /*if (state == QAbstractSocket::ClosingState) {
        server->close();
    }*/
}
