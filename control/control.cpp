#include "control.h"

Control::Control()
{
    motors = new Motors();
    light = new Light();
    servos = new Servos();
    vibro = new Vibro();
    system = new System();
}
// Motor section
void Control::setLeftMotor(int power, int time)
{
    motors->setLeftMotor(power, time);
}

void Control::setRightMotor(int power, int time)
{
    motors->setRightMotor(power, time);
}

int Control::getLeftMotorPower()
{
    return motors->getLeftMotorPower();
}

int Control::getRightMotorPower()
{
    return motors->getRightMotorPower();
}

int Control::getLeftMotorTime()
{
    return motors->getLeftMotorTime();
}

int Control::getRightMotorTime()
{
    return motors->getRightMotorTime();
}
// Light section
bool Control::getXenon()
{
    return light->getXenon();
}

void Control::setXenon(bool xenonEn)
{
    light->setXenon(xenonEn);
}

void Control::setLedPower(int power)
{
    light->setLedPower(power);
}

int Control::getLedPower()
{
    return light->getLedPower();
}

void Control::setXAngle(int angle)
{
    servos->setXAngle(angle);
}

void Control::setYAngle(int angle)
{
    servos->setYAngle(angle);
}

int Control::getXAngle()
{
    return servos->getXAngle();
}

int Control::getYAngle()
{
    return servos->getYAngle();
}

void Control::setVibro(int vibroPower, int vibroTime)
{
    vibro->setVibro(vibroPower, vibroTime);
}

int Control::getVibroPower()
{
    return vibro->getVibroPower();
}

int Control::getVibroTime()
{
    return vibro->getVibroTime();
}

void Control::setFlagRestart(bool flag)
{
    system->setFlagRestart(flag);
}

void Control::setFlagHalt(bool flag)
{
    system->setFlagHalt(flag);
}

bool Control::getFlagRestart()
{
    return system->getFlagRestart();
}

bool Control::getFlagHalt()
{
    return system->getFlagHalt();
}
