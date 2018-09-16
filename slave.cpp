#include "slave.h"

#include <QTcpSocket>
#include <QHostAddress>

Slave::Slave(QTcpSocket *socket, QObject *parent) :
    QObject(parent),
    m_socket(socket)
{
    m_socket->setParent(this);

    qDebug() << this << "connected from" << m_socket->peerAddress();

    connect(m_socket, &QIODevice::readyRead, this, &Slave::readyRead);
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(deleteLater()));
}

void Slave::writeData(const QByteArray &byteArray)
{
    m_socket->write(byteArray);
}

void Slave::readyRead()
{
    Q_EMIT dataReady(m_socket->readAll());
}

void Slave::disconnected()
{
    qDebug() << this << "disconnected!";
}
