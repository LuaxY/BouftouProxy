#ifndef IMESSAGE_H
#define IMESSAGE_H

#include "utils/types.h"

#include <QString>

class IMessage
{
public:
    IMessage(ushort _id, ByteArray _data);

    ushort getId();
    ByteArray getData();
    QString getName();

protected:
    ushort id;
    ByteArray data;
};

#endif // IMESSAGE_H
