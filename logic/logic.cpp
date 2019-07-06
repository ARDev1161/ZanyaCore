#include "logic.h"


Mat Logic::getOutMat() const
{
    return *outMat;
}

void Logic::setOutMat(Mat &value)
{
    *outMat = value;
}

void Logic::setSrcMat(Mat *value)
{
    srcMat = value;
    logicProcess();
}

Logic::Logic()
{
    initLogic();
}

void Logic::initLogic()
{
    srcMat = new Mat();
    outMat = new Mat();
}

void Logic::logicProcess()
{
//    srcMat->copyTo(outMat);
    outMat = srcMat;
}
