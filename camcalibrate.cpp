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

void CamCalibrate::initFields()
{
    numCornersHor = ui->spinHorizontal->value();
    numCornersVer = ui->spinVertical->value();
    numBoards = ui->spinBoards->value();

    numSquares = numCornersHor * numCornersVer;
    board_sz = Size(numCornersHor, numCornersVer);

    intrinsic = Mat(3, 3, CV_32FC1);
    intrinsic.ptr<float>(0)[0] = 1;
    intrinsic.ptr<float>(1)[1] = 1;

    for(int j=0; j < numSquares; j++)
            obj->push_back(Point3f(j / numCornersHor, j % numCornersHor, 0.0f));

    started = true;
}

void CamCalibrate::getCalibInfo()
{
        cvtColor(*sourceMat, gray, COLOR_BGR2GRAY);

        bool found = findChessboardCorners(*sourceMat, board_sz, *corners, CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_FILTER_QUADS);

        if(found){
            cornerSubPix(gray, *corners, Size(11, 11), Size(-1, -1), TermCriteria(TermCriteria::EPS | TermCriteria::COUNT, 30, 0.1));
            drawChessboardCorners(*sourceMat, board_sz, *corners, found);

            image_points.push_back(*corners);
            object_points.push_back(*obj);

            successes++;
            if(successes>=numBoards) ;//break
        }
}

void CamCalibrate::frameUpdate()
{
    if(started)
        getCalibInfo();

    outMat(*sourceMat);
}



void CamCalibrate::on_pushButton_clicked()
{
    initFields();

    ui->groupBox->setEnabled(false);
}
