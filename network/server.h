#ifndef SERVER_H
#define SERVER_H

#include "proxy.h"
#include <QTcpServer>
#include <QObject>

class Client;

class Server : public Proxy, public QTcpServer
{
public:
    Server(Logger *_logger, QObject *parent = nullptr);

    bool start(ushort port);
    void setNext(QString ip, short port);
    void setFastForward(bool enabled);

private:
    Client* client;
    QString nextIP;
    short nextPort;

    void incomingConnection(int descriptor);
    void onMessage(IMessage* message);
    void onData(QByteArray data);
};

#endif // SERVER_H
