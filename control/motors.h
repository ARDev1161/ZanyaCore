#ifndef MOTORS_H
#define MOTORS_H


class Motors
{
    int lPower = 0;
    int rPower = 0;
    int lTime = 0;
    int rTime = 0;

public:
    void setLeftMotor(int power, int time);
    void setRightMotor(int power, int time);

    int getLeftMotorPower();
    int getRightMotorPower();
    int getLeftMotorTime();
    int getRightMotorTime();
};

#endif // MOTORS_H
