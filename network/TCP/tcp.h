#ifndef TCP_H
#define TCP_H

#include <QObject>
#include "tcpworker.h"

class TCP: public QObject
{
    Q_OBJECT

    Control *zanyaControl;
    Sensors *zanyaSensors;

    QString *hostName;

public:
    TCP(Control *control, Sensors *sensors, QString *hostname);
    ~TCP();

    void addThread();
    void stopThreads();

signals:
    void stopAll(); //остановка всех потоков

};

#endif // TCP_H
