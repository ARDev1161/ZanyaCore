#ifndef LIGHT_H
#define LIGHT_H


class Light
{
    int ledPower = 0;
    bool xenonEnable = false;

public:
    bool getXenon();
    void setXenon(bool xenonEn);

    void setLedPower(int power);
    int getLedPower();
};

#endif // LIGHT_H
