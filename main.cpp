#include <QCoreApplication>
#include <QCommandLineParser>

#include <QDebug>

#include "awesomeserver.h"

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    app.setApplicationVersion("0.1.0");

    QCommandLineOption portOption {
            QStringList {"p", "port"},
            "Use this port to accept incoming connections",
            "bind-port",
            "3000"
    };

    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addVersionOption();

    parser.addOption(portOption);

    parser.process(app);

    AwesomeServer server(parser.value(portOption).toInt());

    if (server.listen() == false) {
        qDebug() << "Failed to listen on given port";
        return 1;
    }

    return app.exec();
}