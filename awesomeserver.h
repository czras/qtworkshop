#pragma once

#include <QTcpServer>

class AwesomeServer : public QObject
{
    Q_OBJECT

public:
    AwesomeServer(int port);

    bool listen();

protected slots:
    void newClientConnected();
    void newMessage();

protected:
    int port;
    QTcpServer *server = nullptr;
};
