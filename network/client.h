#ifndef CLIENT_H
#define CLIENT_H

#include "proxy.h"

class Server;

class Client : public Proxy
{
public:
    Client(QObject *parent = nullptr);

    void start(Server *_server);

private:
    Server* server;

    void onMessage(IMessage* message);

private slots:
    void onStateChanged(QAbstractSocket::SocketState state);
};

#endif // CLIENT_H
