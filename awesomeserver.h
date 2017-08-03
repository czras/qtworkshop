#pragma once

#include <QTcpServer>

class AwesomeServer
{
public:
    AwesomeServer(int port);

    bool listen();

protected:
    int port;
    QTcpServer *server = nullptr;
};
