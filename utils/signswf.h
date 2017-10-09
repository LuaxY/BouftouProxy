#ifndef SIGNSWF_H
#define SIGNSWF_H

#include "logger.h"

#include <QByteArray>
#include <QFileInfo>

class SignSwf
{
private:
    QFileInfo* swfFileInfo;
    QString publicKey;
    QString privateKey;
    Logger* logger;

public:
    SignSwf(QFileInfo* _swfFileInfo, QString _publicKey, QString _privateKey, Logger* _logger);

    QByteArray sign();
};

#endif // SIGNSWF_H
