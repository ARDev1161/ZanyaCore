#include "system.h"

void System::setFlagRestart(bool flag)
{
    restart = flag;
}

void System::setFlagHalt(bool flag)
{
    halt = flag;
}

bool System::getFlagRestart()
{
    return restart;
}

bool System::getFlagHalt()
{
    return halt;
}
