#ifndef CAMCALIBRATE_H
#define CAMCALIBRATE_H

#include <QDialog>

namespace Ui {
class CamCalibrate;
}

class CamCalibrate : public QDialog
{
    Q_OBJECT

public:
    explicit CamCalibrate(QWidget *parent = 0);
    ~CamCalibrate();

private:
    Ui::CamCalibrate *ui;
};

#endif // CAMCALIBRATE_H
