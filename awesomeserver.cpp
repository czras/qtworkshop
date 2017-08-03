#include "awesomeserver.h"

#include <QDebug>

AwesomeServer::AwesomeServer(int port)
    : port(port)
{}

bool AwesomeServer::listen()
{
    qDebug() << "Listening on port" << port;
    return false;
}