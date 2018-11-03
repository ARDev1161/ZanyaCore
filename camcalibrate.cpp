#include "camcalibrate.h"
#include "ui_camcalibrate.h"

CamCalibrate::CamCalibrate(Mat *source, QWidget *parent) :
    QDialog(parent),
    sourceMat(source),
    ui(new Ui::CamCalibrate)
{
    ui->setupUi(this);
}

CamCalibrate::~CamCalibrate()
{
    delete ui;
}

void CamCalibrate::on_buttonBox_accepted()
{

}

void CamCalibrate::on_buttonBox_rejected()
{

}

void CamCalibrate::outMat(Mat &ToOut)
{
    QImage qimgOut((uchar*) ToOut.data, ToOut.cols, ToOut.rows, ToOut.step,QImage::Format_RGB888);
    ui->OutLabel->setPixmap(QPixmap::fromImage(qimgOut));
}

void CamCalibrate::frameUpdate()
{
    outMat(*sourceMat);
}


