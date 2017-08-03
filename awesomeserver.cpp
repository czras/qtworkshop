#include "awesomeserver.h"

#include <QDebug>

AwesomeServer::AwesomeServer(int port)
    : port(port),
      server(new QTcpServer())
{}

bool AwesomeServer::listen()
{
    qDebug() << "Listening on port" << port;

    return server->listen(QHostAddress::Any, port);
}