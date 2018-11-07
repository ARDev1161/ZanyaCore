#ifndef TCPWORKER_H
#define TCPWORKER_H

#include "tcpcontrol.h"
#include "tcpsensors.h"


class TCPWorker: public QObject
{
    Q_OBJECT

    TCPControl *tcpControl;
    TCPSensors *tcpSensors;

    Control *zanyaControl;
    Sensors *zanyaSensors;

    QString *hostName;

public:
    TCPWorker(Control *control, Sensors *sensors, QString *hostname);
    ~TCPWorker();

public slots:
    void process();
    void stop();

signals:
    void finished();
};

#endif // TCPWORKER_H
