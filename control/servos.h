#ifndef SERVOS_H
#define SERVOS_H


class Servos
{
    int xAngle = 90;
    int yAngle = 90;

public:
    void setXAngle(int angle);
    void setYAngle(int angle);

    int getXAngle();
    int getYAngle();
};

#endif // SERVOS_H
