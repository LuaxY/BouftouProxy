#include "imessage.h"

IMessage::IMessage(ushort _id, ByteArray _data) : id(_id), data(_data)
{

}

ushort IMessage::getId()
{
    return id;
}

ByteArray IMessage::getData()
{
    return data;
}

QString IMessage::getName()
{
    switch (id) {
    case 1:
        return "ProtocolRequired";
        break;
    case 3:
        return "HelloConnectMessage";
        break;
    case 182:
        return "BasicPingMessage";
        break;
    case 183:
        return "BasicPongMessage";
        break;
    }

    return QString("UnknownMessage (%1)").arg(id);
}
