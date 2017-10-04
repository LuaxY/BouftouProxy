#ifndef PACKET_H
#define PACKET_H

#include "messages/imessage.h"
#include "io/binaryreader.h"
#include "io/binarywriter.h"

class Packet
{
public:
    Packet();

    void serialize(IMessage* message, ByteArray& buffer);
    IMessage* deserialize(ByteArray& buffer);

private:
    ushort getMessageId(ushort header);
    ushort getMessageSizeType(ushort header);
    uint getMessageSize(ushort sizeType, BinaryReader& reader);
    ushort computeSizeType(uint size);
    ushort computeHeader(ushort id, ushort sizeType);
};

#endif // PACKET_H
