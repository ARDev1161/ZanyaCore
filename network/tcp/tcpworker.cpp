#include "tcpworker.h"

TCPWorker::TCPWorker(Control *control, Sensors *sensors, QString *hostname)
{
    zanyaControl = control;
    zanyaSensors = sensors;
    hostName = hostname;
}

TCPWorker::~TCPWorker()
{
    if (tcpControl != nullptr)
        delete tcpControl;

    if (tcpSensors != nullptr)
        delete tcpSensors;
}

void TCPWorker::process()
{
    tcpControl = new TCPControl(zanyaControl, hostName);

    //tcpSensors = new TCPSensors(zanyaSensors, hostName);
}

void TCPWorker::stop()
{
    if(tcpControl != nullptr)
            tcpControl->stop();

    if(tcpSensors != nullptr)
            tcpSensors->stop();
}
