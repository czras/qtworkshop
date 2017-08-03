#include "awesomeserver.h"

#include <QDebug>

AwesomeServer::AwesomeServer(int port)
    : port(port),
      server(new QTcpServer())
{}

bool AwesomeServer::listen()
{
    qDebug() << "Listening on port" << port;

    connect(
            server,
            &QTcpServer::newConnection,
            this,
            &AwesomeServer::newClientConnected
    );

    return server->listen(QHostAddress::Any, port);
}

void AwesomeServer::newClientConnected()
{
    qDebug() << "Client connected";
}