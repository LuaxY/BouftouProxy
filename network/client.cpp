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

        QString proxyIP = "127.0.0.1";
        ushort proxyPort = 5555;

        writer.writeVarShort(serverId);
        writer.writeUTF(proxyIP.toStdString());
        writer.writeUShort(proxyPort);
        writer.writeBool(canCreateNewCharacter);
        writer.writeVarInt(ticketLength);
        writer.writeBytes(ticket, false);

        message->setData(hack);

        logger->log(role, color, SUCCESS, QString("Modified game server address to %1:%2").arg(proxyIP).arg(proxyPort));

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
