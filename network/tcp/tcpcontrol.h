#ifndef TCPCONTROL_H
#define TCPCONTROL_H

#include <QtNetwork>
#include <QObject>
#include <QMessageBox>
#include "stdlib.h"

#include "control/control.h"
#include "network/protobuf/control.pb.h"

class TCPControl: public QObject
{
    Q_OBJECT

    Control *zanyaControl;

    ProtobufControl *pControl;

    std::string *serializedControl;

    QString *hostName;

    QTcpServer *tcpServer = nullptr;
    QNetworkSession *networkSession = nullptr;

public:
    TCPControl(Control *control, QString *hostname);
    ~TCPControl();

    void stop();

private slots:
    void sessionOpened();
    void sendControl();

private:
    void initNetwork();
    void protoByControl();
    void protoInit();
    void protoSerialize();
};

#endif // TCPCONTROL_H
