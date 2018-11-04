#include "camsettingsholder.h"

Mat CamSettingsHolder::getIntrinsic() const
{
    return intrinsic;
}

void CamSettingsHolder::setIntrinsic(const Mat &value)
{
    intrinsic = value;
}

Mat CamSettingsHolder::getDistCoeffs() const
{
    return distCoeffs;
}

void CamSettingsHolder::setDistCoeffs(const Mat &value)
{
    distCoeffs = value;
}

bool CamSettingsHolder::getReady() const
{
    return ready;
}

void CamSettingsHolder::setReady(bool value)
{
    ready = value;
}

CamSettingsHolder::CamSettingsHolder()
{
    ready = false;
}
