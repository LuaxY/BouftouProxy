#ifndef PROXY_H
#define PROXY_H

#include <QObject>
#include <QTcpSocket>
#include "utils/types.h"
#include "utils/logger.h"
#include "messages/imessage.h"

class Proxy : public QObject
{
    Q_OBJECT
private:
    ByteArray buffer;
    QString role;
    Logger logger;

public:
    Proxy(QObject *parent = nullptr, QString _role = "UNK");

    virtual void start();
    virtual void stop();
    virtual void send(IMessage* message);

protected:
    QTcpSocket* socket;

    virtual void onMessage(IMessage* message) = 0;

protected slots:
    virtual void onReadyRead();
    virtual void onStateChanged(QAbstractSocket::SocketState state);
};

#endif // PROXY_H
