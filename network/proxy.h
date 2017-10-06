#ifndef PROXY_H
#define PROXY_H

#include <QObject>
#include <QTcpSocket>
#include "utils/types.h"
#include "utils/logger.h"
#include "messages/imessage.h"
#include "io/binaryreader.h"
#include "io/binarywriter.h"

class Console;

class Proxy : public QObject
{
    Q_OBJECT
private:
    ByteArray buffer;

public:
    Proxy(Logger* _logger, QString _role, QString _color, QObject *parent = nullptr);

    virtual bool start();
    virtual void stop();
    virtual void send(IMessage* message);
    virtual void send(QByteArray data);
    virtual void setFastForward(bool enabled);

protected:
    QTcpSocket* socket;
    QString role;
    QString color;
    Logger* logger;
    bool fastForward;

    virtual void onMessage(IMessage* message) = 0;
    virtual void onData(QByteArray data) = 0;

protected slots:
    virtual void onReadyRead();
    virtual void onStateChanged(QAbstractSocket::SocketState state);

signals:
    void isInGame();
};

#endif // PROXY_H
