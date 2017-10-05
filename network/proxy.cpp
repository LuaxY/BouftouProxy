#include "proxy.h"
#include "packet.h"
#include "utils/hexdump.h"

#include <QDebug>

Proxy::Proxy(QObject *parent, QString _role) : QObject(parent), role(_role)
{
    socket = new QTcpSocket(this);
    logger = Logger::instance();
}

void Proxy::start()
{
    connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(onStateChanged(QAbstractSocket::SocketState)));
}

void Proxy::stop()
{
    socket->close();
}

void Proxy::send(IMessage* message)
{
    Packet packet;
    ByteArray buffer;

    packet.serialize(message, buffer);

    logger.dump(hexdump(buffer.data(), buffer.size()));

    socket->write(buffer.data(), buffer.size());

    delete message;
}

void Proxy::onReadyRead()
{
    QByteArray data = socket->readAll();

    ByteArray readedByes(data.data(), data.data() + data.length());
    buffer.insert(buffer.end(), readedByes.begin(), readedByes.end());

    logger.dump(hexdump(buffer.data(), buffer.size()));

    IMessage* message = nullptr;
    bool isFromClient = false;
    Packet packet;

    if (role == "CLI") isFromClient = true;

    while ((message = packet.deserialize(buffer, isFromClient))) {
        logger.log(role, INFO, message->getName());
        onMessage(message);
    }
}

void Proxy::onStateChanged(QAbstractSocket::SocketState state)
{

}
