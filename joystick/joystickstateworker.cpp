#include "joystickstateworker.h"

JoystickStateWorker::JoystickStateWorker(int id, Control *control)
{
    joyId = id;
    zanyaControl = control;
    joyState = nullptr;
}

JoystickStateWorker::~JoystickStateWorker()
{
    if (joyState != nullptr)
        delete joyState;
}

void JoystickStateWorker::process()
{
    joyState = new GetStateByJoystick(joyId, zanyaControl);
}

void JoystickStateWorker::stop()
{
    if(joyState != nullptr)
            joyState->stop();
}

void JoystickStateWorker::changeJoystickId(int id)
{
    joyId = id;
}
