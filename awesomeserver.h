#pragma once

#include <QTcpServer>

class AwesomeServer : public QObject
{
    Q_OBJECT

public:
    AwesomeServer(int port);

    bool listen();

protected:
    QString processMessage(const QString &msg);

protected slots:
    void newClientConnected();
    void newMessage();
    void clientDisconnected();

protected:
    int port;
    QTcpServer *server = nullptr;
};
