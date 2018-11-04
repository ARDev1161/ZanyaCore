#ifndef CAMSETTINGSHOLDER_H
#define CAMSETTINGSHOLDER_H

#include <opencv2/opencv.hpp>

using namespace cv;

class CamSettingsHolder
{
    bool ready;

    Mat distCoeffs;
    Mat intrinsic;

public:
    CamSettingsHolder();
    Mat getIntrinsic() const;
    void setIntrinsic(const Mat &value);

    Mat getDistCoeffs() const;
    void setDistCoeffs(const Mat &value);

    bool getReady() const;
    void setReady(bool value);
};

#endif // CAMSETTINGSHOLDER_H
