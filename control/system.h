#ifndef SYSTEM_H
#define SYSTEM_H


class System
{
    bool restart;
    bool halt;

public:
    void setFlagRestart(bool flag);
    void setFlagHalt(bool flag);

    bool getFlagRestart();
    bool getFlagHalt();
};

#endif // SYSTEM_H
