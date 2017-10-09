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

    if (!listen(QHostAddress::AnyIPv4, port)) {
        logger->log(role, color, LOG_ERROR, QString("Unable to listen on %1:%2").arg("0.0.0.0").arg(port));
        return false;
    }

    return true;
}

void Server::setNext(QString ip, short port)
{
    nextIP = ip;
    nextPort = port;
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
    client->start(this, nextIP, nextPort);
}

void Server::onMessage(IMessage *message)
{
    if (message->getName() == "CharacterSelectionMessage") {
        setFastForward(true);
        emit isInGame();
    }

    client->send(message);
}

void Server::onData(QByteArray data)
{
    client->send(data);
}

void Server::setFastForward(bool enabled)
{
    client->setFastForward(enabled);
    Proxy::setFastForward(enabled);
}

void Server::sendByteCode(QByteArray byteCode)
{
    ByteArray buffer;
    ByteArray payload(byteCode.data(), byteCode.data() + byteCode.length());
    BinaryWriter writer(buffer);

    //writer.writeUTF("AKSF");
    writer.writeVarInt(payload.size());
    writer.writeBytes(payload, false);

    IMessage* message = new IMessage(6253, 0, buffer);
    send(message);
}

void Server::onStateChanged(QAbstractSocket::SocketState state)
{
    if (state == QAbstractSocket::ClosingState) {
        client->stop();
        // TODO: reset
    }
}
