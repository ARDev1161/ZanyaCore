#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "joystickstateworker.h"
#include "joystickdialog.h"

class Joystick: public QObject
{
    Q_OBJECT

    int joyId;

    Control *zanyaControl;

public:
    Joystick(int id, Control *control);
    ~Joystick();

    void addThread();
    void stopThreads();

signals:
    void stopAll(); //остановка всех потоков
};

#endif // JOYSTICK_H
