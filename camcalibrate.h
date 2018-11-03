#ifndef CAMCALIBRATE_H
#define CAMCALIBRATE_H

#include <QDialog>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

namespace Ui {
class CamCalibrate;
}

class CamCalibrate : public QDialog
{
    Q_OBJECT


    bool started = false;

    int numBoards = 0;
    int numCornersHor;
    int numCornersVer;
    int numSquares;

    int successes=0;

    Size board_sz;

    vector<Point2f> *corners;

    vector<vector<Point2f>> image_points;
    vector<vector<Point3f>> object_points;

    vector<Point3f> *obj;

    vector<Mat> rvecs;
    vector<Mat> tvecs;

    Mat *sourceMat;
    Mat gray;

    Mat distCoeffs;
    Mat intrinsic;

    Ui::CamCalibrate *ui;

public:
    explicit CamCalibrate(Mat *source, QWidget *parent = 0);
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
