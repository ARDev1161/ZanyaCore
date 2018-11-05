#ifndef LOGIC_H
#define LOGIC_H

#include "opencv2/opencv.hpp"


using namespace cv;
class Logic
{
    Mat *srcMat;
    Mat *outMat;

public:
    Logic();


    void initLogic();
    void logicProcess();

    Mat getOutMat() const;
    void setOutMat(Mat &value);

    void setSrcMat(Mat *value);
};

#endif // LOGIC_H
