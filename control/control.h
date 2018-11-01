#ifndef CONTROL_H
#define CONTROL_H

#include "light.h"
#include "motors.h"
#include "servos.h"
#include "vibro.h"
#include "system.h"

class Control
{
    Motors *motors;
    Light *light;
    Servos *servos;
    Vibro *vibro;
    System *system;

public:
    Control();

    void setLeftMotor(int power, int time);
    void setRightMotor(int power, int time);

    int getLeftMotorPower();
    int getRightMotorPower();
    int getLeftMotorTime();
    int getRightMotorTime();

    bool getXenon();
    void setXenon(bool xenonEn);
    void setLedPower(int power);
    int getLedPower();

    void setXAngle(int angle);
    void setYAngle(int angle);

    int getXAngle();
    int getYAngle();

    void setVibro(int vibroPower, int vibroTime);

    int getVibroPower();
    int getVibroTime();

    void setFlagRestart(bool flag);
    void setFlagHalt(bool flag);

    bool getFlagRestart();
    bool getFlagHalt();

};


#endif // CONTROL_H
