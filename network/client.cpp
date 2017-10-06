#include "client.h"
#include "server.h"

Client::Client(Logger* _logger, QObject *parent) :
    Proxy(_logger, "SRV", "#e74c3c", parent)
{
}

bool Client::start(Server* _server, QString ip, short port)
{
    server = _server;
    Proxy::start();

    socket->connectToHost(ip, port);

    if (!socket->waitForConnected(5000)) {
        logger->log(role, color, LOG_ERROR, QString("Unable to connect to %1:%2 (timeout 5s)").arg(ip).arg(port));
        return false;
    }

    return true;
}

void Client::onMessage(IMessage *message)
{
    if (message->getName() == "CharactersListMessage") {
        setFastForward(true);
    }

    if (message->getName() == "SelectedServerDataMessage") {
        ByteArray hack;
        BinaryWriter writer(hack);
        BinaryReader reader(message->getData());

        short serverId = reader.readVarShort();
        std::string ip = reader.readUTF();
        ushort port = reader.readUShort();
        bool canCreateNewCharacter = reader.readBool();
        int ticketLength = reader.readVarUhInt();
        ByteArray ticket = reader.readBytes(ticketLength);

        writer.writeVarShort(serverId);
        writer.writeUTF("127.0.0.1");
        writer.writeUShort(5555);
        writer.writeBool(canCreateNewCharacter);
        writer.writeVarInt(ticketLength);
        writer.writeBytes(ticket, false);

        message->setData(hack);

        server->send(message);
        server->setNext(QString::fromStdString(ip), port);
        server->stop();

        return;
    }

    server->send(message);
}

void Client::onData(QByteArray data)
{
    server->send(data);
}
