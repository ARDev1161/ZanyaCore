#ifndef SENSORS_H
#define SENSORS_H

#include "accelerometer.h"
#include "gyroscope.h"
#include "motorencoders.h"
#include "temperature.h"

class Sensors
{
    int gas;
    int batteryVoltage;
    float pressure;

public:
    Accelerometer *accelerometer;
    Gyroscope *gyroscope;
    MotorEncoders *motorEncoders;
    Temperature *temperature;

    int getGas();
    int getBatteryVoltage();
    float getPressure();

    void setGas(int gases);
    void setBatteryVoltage(int voltage);
    void setPressure(float press);

};

#endif // SENSORS_H
