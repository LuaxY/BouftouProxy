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

private:
    Client* client;

    void incomingConnection(int descriptor);
    void onMessage(IMessage* message);
};

#endif // SERVER_H
