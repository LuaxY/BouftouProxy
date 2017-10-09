#ifndef CLIENT_H
#define CLIENT_H

#include "proxy.h"

class Server;

class Client : public Proxy
{
public:
    Client(Logger *_logger, QObject *parent = nullptr);

    bool start(Server *_server, QString ip, short port);

private:
    Server* server;

    void onMessage(IMessage* message);
    void onData(QByteArray data);

protected slots:
    void onStateChanged(QAbstractSocket::SocketState state);
};

#endif // CLIENT_H
