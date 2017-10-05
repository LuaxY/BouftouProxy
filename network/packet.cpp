#include "packet.h"

Packet::Packet()
{

}

void Packet::serialize(IMessage* message, ByteArray& buffer)
{
    BinaryWriter writer(buffer);

    uint size = message->getData().size();
    ushort sizeType = computeSizeType(size);
    ushort header = computeHeader(message->getId(), sizeType);

    writer.writeUShort(header);

    if (message->getInstanceId() > 0) {
        writer.writeUInt(message->getInstanceId());
    }

    switch (sizeType) {
    case 1:
        writer.writeByte(size);
        break;
    case 2:
        writer.writeShort(size);
        break;
    case 3:
        uint high = (size >> 16) & 255;
        uint low = size & 65535;
        writer.writeByte(high);
        writer.writeShort(low);
        break;
    }

    writer.writeBytes(message->getData(), false);
}

IMessage* Packet::deserialize(ByteArray& buffer, bool isFromClient)
{
    BinaryReader reader(buffer);
    ushort header = 0;
    uint instanceId = 0;
    uint countReadedBytes = 0;

    if (reader.bytesAvailable() < sizeof(header)) {
        return nullptr;
    }

    header = reader.readUShort();
    countReadedBytes += sizeof(header);

    if (isFromClient) {
        if (reader.bytesAvailable() < sizeof(instanceId)) {
            return nullptr;
        }

        instanceId = reader.readUInt();
        countReadedBytes += sizeof(instanceId);
    }

    ushort id = getMessageId(header);
    ushort sizeType = getMessageSizeType(header);
    ByteArray data;

    if (sizeType > 0) {
        if (reader.bytesAvailable() < sizeType) {
            return nullptr;
        }

        uint size = getMessageSize(sizeType, reader);
        countReadedBytes += sizeType;

        if (reader.bytesAvailable() < size) {
            return nullptr;
        }

        data = reader.readBytes(size);
        countReadedBytes += size;
    }

    buffer.erase(buffer.begin(), buffer.begin() + countReadedBytes);

    return new IMessage(id, instanceId, data);
}

ushort Packet::getMessageId(ushort header)
{
    return header >> 2;
}

ushort Packet::getMessageSizeType(ushort header)
{
    return static_cast<ushort>(header & 3);
}

uint Packet::getMessageSize(ushort sizeType, BinaryReader &reader)
{
    uint size = 0;

    switch (sizeType) {
    case 1:
        size = static_cast<uint>(reader.readByte());
        break;
    case 2:
        size = reader.readUShort();
        break;
    case 3:
        size = static_cast<uint>(
            ((reader.readByte() & 255) << 16) +
            ((reader.readByte() & 255) << 8) +
             (reader.readByte() & 255));
        break;
    default:
        break;
    }

    return size;
}

ushort Packet::computeSizeType(uint size)
{
    if (size > 65535) return 3;
    if (size > 255)   return 2;
    if (size > 0)     return 1;
    return 0;
}

ushort Packet::computeHeader(ushort id, ushort sizeType)
{
    return id << 2 | sizeType;
}
