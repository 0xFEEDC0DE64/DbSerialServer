#include <QCoreApplication>
#include <QDir>
#include <QSettings>
#include <QSerialPort>
#include <QTcpServer>

#include "utils/netutils.h"

#include "master.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("serialserver");
    QCoreApplication::setOrganizationDomain("brunner.ninja");
    QCoreApplication::setOrganizationName("0xFEEDC0DE64");

    const auto configPath = QDir(QCoreApplication::applicationDirPath()).absoluteFilePath(QCoreApplication::applicationName() + QStringLiteral(".ini"));
    QSettings settings(configPath, QSettings::IniFormat);

    qDebug() << "Opening serialport...";
    auto serialPort = new QSerialPort;
    serialPort->setPortName(settings.value("serial/port").toString());
    serialPort->setBaudRate(settings.value("serial/baudrate").toInt());
    if(!serialPort->open(QIODevice::ReadWrite))
    {
        qWarning() << serialPort->errorString();
        qFatal("could not open serialport");
        return -1;
    }

    qDebug() << "Starting tcp server...";
    auto server = new QTcpServer;

    if(!server->listen(parseHostAddress(settings.value("server/address", "Any").toString()),
                       (quint16)settings.value("server/port", 1234).toUInt()))
    {
        qWarning() << server->errorString();
        qFatal("could not start listening");
        return -2;
    }

    new Master(serialPort, server, &app);

    return app.exec();
}
