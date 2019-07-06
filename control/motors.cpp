#include "motors.h"

void Motors::setLeftMotor(int power, int time)
{
    lPower = power;
    lTime = time;
}

void Motors::setRightMotor(int power, int time)
{
    rPower = power;
    rTime = time;
}

int Motors::getLeftMotorPower()
{
    return lPower;
}

int Motors::getRightMotorPower()
{
    return rPower;
}

int Motors::getLeftMotorTime()
{
    return lTime;
}

int Motors::getRightMotorTime()
{
    return rTime;
}
