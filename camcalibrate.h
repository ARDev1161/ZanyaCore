#ifndef CAMCALIBRATE_H
#define CAMCALIBRATE_H

#include <QDialog>
#include <opencv2/opencv.hpp>

using namespace cv;

namespace Ui {
class CamCalibrate;
}

class CamCalibrate : public QDialog
{
    Q_OBJECT

    Mat *sourceMat;

    int numBoards = 0;
    int numCornersHor;
    int numCornersVer;
    int numSquares;

public:
    explicit CamCalibrate(Mat *source, QWidget *parent = 0);
    ~CamCalibrate();

public slots:
    void frameUpdate();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::CamCalibrate *ui;

    void outMat(Mat &ToOut);
};

#endif // CAMCALIBRATE_H
