#ifndef IMESSAGE_H
#define IMESSAGE_H

#include "utils/types.h"

#include <QString>

class IMessage
{
public:
    IMessage(ushort _id, uint _instanceId, ByteArray _data);

    ushort getId();
    uint getInstanceId();
    ByteArray getData();
    QString getName();

protected:
    ushort id;
    uint instanceId;
    ByteArray data;
};

#endif // IMESSAGE_H
