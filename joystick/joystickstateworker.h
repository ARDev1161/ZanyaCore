#ifndef JOYSTICKSTATEWORKER_H
#define JOYSTICKSTATEWORKER_H

#include "getstatebyjoy.h"


class JoystickStateWorker : public QObject
{
    Q_OBJECT

    int joyId = -1;
    GetStateByJoystick *joyState;

    Control *zanyaControl;

    void changeJoystickId(int id);


public:
    JoystickStateWorker(int id, Control *control);
    ~JoystickStateWorker();

public slots:
    void process();
    void stop();

signals:
    void finished();
};

#endif // JOYSTICKSTATEWORKER_H
