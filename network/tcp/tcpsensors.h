#ifndef TCPSENSORS_H
#define TCPSENSORS_H

#include <QtNetwork>
#include <QObject>

#include "sensors/sensors.h"
#include "network/protobuf/sensors.pb.h"

class TCPSensors: public QObject
{
    Q_OBJECT

    Sensors *zanyaSensors;
    ProtobufSensors protoSensors;

    QNetworkSession *networkSession = nullptr;
    QDataStream in;
    QTcpSocket *tcpSocket = nullptr;
    QString currentSensors;
    QString *hostName;

    int port = 7777;

public:
    TCPSensors(Sensors *sensors, QString *hostname);
    ~TCPSensors();

    void stop();

private slots:
    void requestNewControl();
    void readControl();
    void displayError(QAbstractSocket::SocketError socketError);
    void sessionOpened();

private:
    void initNetwork();

};

#endif // TCPSENSORS_H
