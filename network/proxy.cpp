#include "proxy.h"
#include "packet.h"
#include "utils/hexdump.h"

Proxy::Proxy(Logger *_logger, QString _role, QString _color, QObject *parent) :
    QObject(parent),
    socket(nullptr),
    role(_role),
    color(_color),
    fastForward(false)
{
    logger = _logger;
}

bool Proxy::start()
{
    socket = new QTcpSocket(this);

    connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(onStateChanged(QAbstractSocket::SocketState)));

    return true;
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

    QString color2;
    if (color == "#3498db") color2 = "#f1c40f";
    if (color == "#e74c3c") color2 = "#2ecc71";

    logger->dump(color2, hexdump(buffer.data(), buffer.size()));

    socket->write(buffer.data(), buffer.size());

    delete message;
}

void Proxy::send(QByteArray data)
{
    socket->write(data);
}

void Proxy::setFastForward(bool enabled)
{
    fastForward = enabled;
}

void Proxy::onReadyRead()
{
    QByteArray data = socket->readAll();

    if (fastForward) {
        onData(data);
        return;
    }

    ByteArray readedByes(data.data(), data.data() + data.length());
    buffer.insert(buffer.end(), readedByes.begin(), readedByes.end());

    logger->dump(color, hexdump(buffer.data(), buffer.size()));

    IMessage* message = nullptr;
    bool isFromClient = false;
    Packet packet;

    if (role == "CLI") isFromClient = true;

    while ((message = packet.deserialize(buffer, isFromClient))) {
        logger->log(role, color, INFO, message->getName());
        onMessage(message);
    }
}

void Proxy::onStateChanged(QAbstractSocket::SocketState state)
{
    QString stateName = QString::number(state);

    if (state == QAbstractSocket::UnconnectedState) stateName = "UnconnectedState";
    if (state == QAbstractSocket::HostLookupState) stateName = "HostLookupState";
    if (state == QAbstractSocket::ConnectingState) stateName = "ConnectingState";
    if (state == QAbstractSocket::ConnectedState) stateName = "ConnectedState";
    if (state == QAbstractSocket::BoundState) stateName = "BoundState";
    if (state == QAbstractSocket::ClosingState) stateName = "ClosingState";
    if (state == QAbstractSocket::ListeningState) stateName = "ListeningState";

    logger->log(role, color, DEBUG, stateName);
}
