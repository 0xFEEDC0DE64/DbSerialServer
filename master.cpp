#include "master.h"

#include <QSerialPort>
#include <QTcpServer>
#include <QCoreApplication>

#include "slave.h"

Master::Master(QSerialPort *serialPort, QTcpServer *server, QObject *parent) :
    QObject(parent),
    m_serialPort(serialPort),
    m_server(server)
{
    m_serialPort->setParent(this);
    connect(m_serialPort, &QIODevice::readyRead, this, &Master::readyRead);
    connect(m_serialPort, &QSerialPort::errorOccurred, this, &Master::errorOccurred);

    m_server->setParent(this);
    connect(m_server, SIGNAL(newConnection()), this, SLOT(newConnection()));

    qDebug() << "startup successfull!";
}

void Master::writeData(const QByteArray &byteArray)
{
    m_serialPort->write(byteArray);
}

void Master::readyRead()
{
    Q_EMIT dataReady(m_serialPort->readAll());
}

void Master::errorOccurred(QSerialPort::SerialPortError error)
{
    if(error == QSerialPort::NoError) //actually occured! qt is dumb
        return;

    qWarning() << error << enumToKey(error);
    qFatal("error occured in serial port");
    qApp->quit();
}

void Master::newConnection()
{
    auto socket = m_server->nextPendingConnection();
    if(socket)
    {
        auto slave = new Slave(socket, this);
        connect(slave, &Slave::dataReady, this, &Master::writeData);
        connect(this, &Master::dataReady, slave, &Slave::writeData);
    }
}
