#ifndef VIBRO_H
#define VIBRO_H


class Vibro
{
    int power = 0;
    int time = 0;

public:
    void setVibro(int vibroPower, int vibroTime);

    int getVibroPower();
    int getVibroTime();
};

#endif // VIBRO_H
