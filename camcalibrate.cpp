#include "camcalibrate.h"
#include "ui_camcalibrate.h"

CamCalibrate::CamCalibrate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CamCalibrate)
{
    ui->setupUi(this);
}

CamCalibrate::~CamCalibrate()
{
    delete ui;
}
