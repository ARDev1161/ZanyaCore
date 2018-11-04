#ifndef CAMCALIBRATE_H
#define CAMCALIBRATE_H

#include <QDialog>
#include "camera/camsettingsholder.h"

using namespace cv;
using namespace std;

namespace Ui {
class CamCalibrate;
}

class CamCalibrate : public QDialog
{
    Q_OBJECT


    bool started = false;

    int numCornersHor;
    int numCornersVer;
    int numSquares;

    int successes=0;

    Ui::CamCalibrate *ui;

    CamSettingsHolder *camHolder;

    vector<Point2f> corners;

    vector<vector<Point2f>> image_points;
    vector<vector<Point3f>> object_points;

    vector<Point3f> obj;

    vector<Mat> rvecs;
    vector<Mat> tvecs;

    Size boardSize;

    Mat *sourceMat;

    Mat gray;
    Mat out;

    Mat distCoeffs;
    Mat intrinsic;


public:
    explicit CamCalibrate(Mat *source, CamSettingsHolder *holder, QWidget *parent = 0);
    ~CamCalibrate();

public slots:
    void frameUpdate();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void on_pushButton_clicked();


private:
    void outMat(Mat &ToOut);
    void initFields();
    void getCalibInfo();
};

#endif // CAMCALIBRATE_H
