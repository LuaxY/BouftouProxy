#include "client.h"
#include "server.h"

Client::Client(Logger* _logger, QObject *parent) :
    Proxy(_logger, "SRV", "#e74c3c", parent)
{
}

bool Client::start(Server* _server)
{
    server = _server;
    Proxy::start();

    QString ip = "213.248.126.39";
    ushort port = 5555;

    socket->connectToHost(ip, port);

    if (!socket->waitForConnected(5000)) {
        logger->log(role, color, LOG_ERROR, QString("Unable to connect to %1:%2 (timeout 5s)").arg(ip).arg(port));
        return false;
    }

    return true;
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
