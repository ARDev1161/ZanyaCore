#include "getstatebyjoy.h"

GetStateByJoystick::GetStateByJoystick(int id, Control *control, QObject *parent) : QObject(parent),
    buttonVector(QVector<bool>(MAX_JOYSTICK_BUTTONS))
{
    joyId = id;
    zanyaControl = control;
    joyAdapter = new VJoystickAdapter();
    loopFlag = true;
    connectToJoystick();

}

GetStateByJoystick::~GetStateByJoystick()
{
    disconnectFromJoystick();
}

void GetStateByJoystick::stop()
{
    loopFlag = false;
}

void GetStateByJoystick::translateToControl()
{
    zanyaControl->setXenon(false);
    zanyaControl->setLedPower(0);
    zanyaControl->setLeftMotor(0, 0);
    zanyaControl->setRightMotor(0, 0);
    zanyaControl->setXAngle(joystickXaxis/364);
    zanyaControl->setYAngle(joystickYaxis/364);
    zanyaControl->setFlagHalt(false);
    zanyaControl->setFlagRestart(false);

}

void GetStateByJoystick::connectToJoystick()
{
    if(joyId != -1)
        if(joyAdapter->open(joyId))
        {
            connect(joyAdapter, SIGNAL(sigButtonChanged(int, bool)), this, SLOT(buttonSetup(int,bool)));
            connect(joyAdapter, SIGNAL(sigAxisChanged(int,int)), this, SLOT(axisSetup(int,int)));
            connect(joyAdapter, SIGNAL(sigHatChanged(int,int)), this, SLOT(hatSetup(int,int)));
            connect(joyAdapter, SIGNAL(sigBallChanged(int,int,int)), this, SLOT(ballSetup(int,int,int)));
        }
}

void GetStateByJoystick::disconnectFromJoystick()
{
    if(joyAdapter->isConnected())
    {
        joyAdapter->close();
        disconnect(joyAdapter, SIGNAL(sigButtonChanged(int, bool)), this, SLOT(buttonSetup(int,bool)));
        disconnect(joyAdapter, SIGNAL(sigAxisChanged(int,int)), this, SLOT(axisSetup(int,int)));
        disconnect(joyAdapter, SIGNAL(sigHatChanged(int,int)), this, SLOT(hatSetup(int,int)));
        disconnect(joyAdapter, SIGNAL(sigBallChanged(int,int,int)), this, SLOT(ballSetup(int,int,int)));
    }
    joyId = -1;
}

void GetStateByJoystick::axisSetup(int id, int state)
{
    switch(id)
    {
    case 0:
        joystickXaxis = (tr("%1").arg(state)).toInt();
        break;
    case 1:
        joystickYaxis = (tr("%1").arg(-1*state)).toInt();
        break;
    case 2:
        joystickZLTaxis = (tr("%1").arg(state)).toInt();
        break;
    case 3:
        joystickXrotation = (tr("%1").arg(state)).toInt();
        break;
    case 4:
        joystickYrotation = (tr("%1").arg(-1*state)).toInt();
        break;
    case 5:
        joystickZRTaxis = (tr("%1").arg(state)).toInt();
        break;
    }
    translateToControl();
}

void GetStateByJoystick::hatSetup(int id, int state)
{
    Q_UNUSED(id);
    joystickPOV0 = (tr("%1").arg(state)).toInt();
    translateToControl();
}

void GetStateByJoystick::buttonSetup(int id, bool state)
{
    buttonVector[id] = state;

    QString buttonTest = "";
    for(int i = 0; i < MAX_JOYSTICK_BUTTONS; ++i)
    {
        if(buttonVector[i] == true)
        {
            if(i < 10)
                buttonTest += tr("0%1  ").arg(i);
            else
                buttonTest += tr("%1").arg(i);
        }
    }
//    ui->joystickButtonsTestLabel->setText(buttonTest);
    translateToControl();
}

void GetStateByJoystick::ballSetup(int id, int stateX, int stateY)
{
    Q_UNUSED(id);
    Q_UNUSED(stateX);
    Q_UNUSED(stateY);

    translateToControl();
}
