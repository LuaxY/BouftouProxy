#include "proxy.h"
#include "packet.h"

#include <QDebug>

Proxy::Proxy(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket(this);
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

    socket->write(buffer.data(), buffer.size());

    delete message;
}

void Proxy::onReadyRead()
{
    QByteArray data = socket->readAll();

    ByteArray readedByes(data.data(), data.data() + data.length());
    buffer.insert(buffer.end(), readedByes.begin(), readedByes.end());

    IMessage* message = nullptr;
    Packet packet;

    while ((message = packet.deserialize(buffer))) {
        qDebug() << message->getName();
        onMessage(message);
    }
}

void Proxy::onStateChanged(QAbstractSocket::SocketState state)
{

}
