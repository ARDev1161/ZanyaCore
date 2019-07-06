#include "servos.h"

void Servos::setXAngle(int angle)
{
    xAngle = angle;
}

void Servos::setYAngle(int angle)
{
    yAngle = angle;
}

int Servos::getXAngle()
{
    return xAngle;
}

int Servos::getYAngle()
{
    return yAngle;
}
