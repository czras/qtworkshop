#include <QCoreApplication>
#include <QCommandLineParser>

#include <QDebug>

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

    qDebug() << "Hello workshop" << parser.value(portOption);

    return app.exec();
}