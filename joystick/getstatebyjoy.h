#ifndef GETSTATEBYJOY_H
#define GETSTATEBYJOY_H

#include <QVector>
#include <QTimer>
#include <QObject>
#include <QDebug>
#include "v_joystick_adapter.h"
#include "control/control.h"

class GetStateByJoystick : public QObject
{
    Q_OBJECT

    Control *zanyaControl;

    VJoystickAdapter* joyAdapter;

    enum { MAX_JOYSTICK_BUTTONS = 30 };

    QVector<bool> buttonVector;

    int LoopTime=50;

    bool loopFlag;

    int joyId;

    int joystickXaxis = 0;
    int joystickYaxis = 0;
    int joystickZLTaxis = 0;
    int joystickXrotation = 0;
    int joystickYrotation = 0;
    int joystickZRTaxis = 0;

    int joystickPOV0 = 0;

public:
    GetStateByJoystick(int id, Control *control, QObject *parent = nullptr);
    ~GetStateByJoystick();
    void stop();

private:
    void setAvaliableJoystick();
    void translateToControl();

private slots:
    void connectToJoystick();
    void disconnectFromJoystick();

    void axisSetup(int id, int state);
    void hatSetup(int id, int state);
    void buttonSetup(int id, bool state);
    void ballSetup(int id, int stateX, int stateY);
};

#endif // GETSTATEBYJOY_H
