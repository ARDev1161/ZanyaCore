#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "joystickstateworker.h"
#include "joystickdialog.h"

class Joystick: public QObject
{
    Q_OBJECT

public:
    Joystick(int id, Control *control);
    ~Joystick();

    void addThread();
    void stopThreads();


private:
    int joyId;

    Control *zanyaControl;

signals:
    void stopAll(); //остановка всех потоков
};

#endif // JOYSTICK_H
