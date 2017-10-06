#include "server.h"
#include "client.h"
#include <QAbstractSocket>

Server::Server(Logger* _logger, QObject *parent) :
    Proxy(_logger, "CLI", "#3498db", parent),
    QTcpServer(parent),
    client(nullptr)
{

}

bool Server::start(ushort port)
{
    Proxy::start();

    if (!listen(QHostAddress::Any, port)) {
        logger->log(role, color, LOG_ERROR, QString("Unable to listen on %1:%2").arg("0.0.0.0").arg(port));
        return false;
    }

    return true;
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

    // delete previous client
    if (client) delete client;

    client = new Client(logger);
    client->start(this);
}

void Server::onMessage(IMessage *message)
{
    // TODO: alter messages;

    client->send(message);
}

