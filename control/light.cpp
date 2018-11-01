#include "light.h"

bool Light::getXenon()
{
    return xenonEnable;
}

void Light::setXenon(bool xenonEn)
{
    xenonEnable = xenonEn;
}

void Light::setLedPower(int power)
{
    ledPower = power;
}

int Light::getLedPower()
{
    return ledPower;
}
