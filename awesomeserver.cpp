#include "awesomeserver.h"

#include <QTcpSocket>
#include <QCoreApplication>
#include <QFile>

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

QString AwesomeServer::processMessage(const QString &msg)
{
    QStringList command = msg.split('|');

    // echo|hodor hodor
    // { "echo", "hodor hodor" }

    if (command.value(0) == "echo") {
        return command.value(1);
    }

    if (command.value(0) == "cat") {
        // :/path
        // :/hodor.txt
        // cat|hodor.txt

        QFile f(":/" + command.value(1));
        f.open(QFile::ReadOnly);

        return f.readAll();
    }

    if (command.value(0) == "pause") {
        server->pauseAccepting();
        qDebug() <<  "Queuing new connections";
        return "paused";
    }

    if (command.value(0) == "resume") {
        server->resumeAccepting();
        qDebug() << "Serving new connections";
        return "resumed";
    }

    if (command.value(0) == "stop") {
        server->close();
        qDebug() << "Stopped listening for new connections";
        return "stopped";
    }

    if (command.value(0) == "start") {
        server->listen(QHostAddress::Any, port);
        qDebug() << "Started listening for new connections";
        return "started";
    }

    if (command.value(0) == "exit") {
        qApp->exit(command.value(1).toInt());
        return "SHUTTING DOWN";
    }

    return "INVALID COMMAND";
}

void AwesomeServer::newClientConnected()
{
    qDebug() << "Client connected";

    while (server->hasPendingConnections()) {
        QTcpSocket *socket = server->nextPendingConnection();

        connect(
                socket,
                &QTcpSocket::readyRead,
                this,
                &AwesomeServer::newMessage
        );

        connect(
                socket,
                &QTcpSocket::disconnected,
                this,
                &AwesomeServer::clientDisconnected
        );
    }
}

void AwesomeServer::clientDisconnected()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());

    if (socket == nullptr) {
        qDebug() << "Holly shite";
        return;
    }

    qDebug() << "Client disconnected";
}

void AwesomeServer::newMessage()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());

    if (socket == nullptr) {
        qDebug() << "Holly shite";
        return;
    }

    while (socket->canReadLine()) {
        QString msg = socket->readLine().trimmed();

        if (msg.isEmpty()) {
            continue;
        }

        QString result = processMessage(msg);
        socket->write(result.toUtf8() + '\n');
    }
}