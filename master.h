#pragma once

#include <QObject>
#include <QSerialPort>
#include <QMetaEnum>

class QTcpServer;

class Master : public QObject
{
    Q_OBJECT

public:
    explicit Master(QSerialPort *serialPort, QTcpServer *server, QObject *parent = 0);

Q_SIGNALS:
    void dataReady(const QByteArray &byteArray);

public Q_SLOTS:
    void writeData(const QByteArray &byteArray);

private Q_SLOTS:
    void readyRead();
    void errorOccurred(QSerialPort::SerialPortError error);
    void newConnection();

private:
    template<typename T> static const char *enumToKey(T value)
    {
        Q_STATIC_ASSERT_X(QtPrivate::IsQEnumHelper<T>::Value, "QMetaEnum::fromType only works with enums declared as Q_ENUM or Q_FLAG");

        const QMetaObject *metaObject = qt_getEnumMetaObject(T());
        const char *nameOfEnum = qt_getEnumName(T());
        int index = metaObject->indexOfEnumerator(nameOfEnum);
        if(index == -1)
            return "!!ENUM_NOT_FOUND!!";
        auto metaEnum = metaObject->enumerator(index);
        return metaEnum.valueToKey((int)value);
    }

    QSerialPort *m_serialPort;
    QTcpServer *m_server;
};
