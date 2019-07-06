#include "sensors.h"

int Sensors::getGas()
{
    return gas;
}

int Sensors::getBatteryVoltage()
{
    return batteryVoltage;
}

float Sensors::getPressure()
{
    return pressure;
}

void Sensors::setGas(int gases)
{
    gas = gases;
}

void Sensors::setBatteryVoltage(int voltage)
{
    batteryVoltage = voltage;
}

void Sensors::setPressure(float press)
{
    pressure = press;
}
