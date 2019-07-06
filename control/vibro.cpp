#include "vibro.h"

void Vibro::setVibro(int vibroPower, int vibroTime)
{
    power = vibroPower;
    time = vibroTime;
}

int Vibro::getVibroPower()
{
    return power;
}

int Vibro::getVibroTime()
{
    return time;
}
