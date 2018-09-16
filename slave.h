#ifndef SLAVE_H
#define SLAVE_H

#include <QObject>

class QTcpSocket;

class Slave : public QObject
{
    Q_OBJECT
public:
    explicit Slave(QTcpSocket *socket, QObject *parent = 0);

Q_SIGNALS:
    void dataReady(const QByteArray &byteArray);

public Q_SLOTS:
    void writeData(const QByteArray &byteArray);

private Q_SLOTS:
    void readyRead();
    void disconnected();

private:
    QTcpSocket *m_socket;
};

#endif // SLAVE_H
