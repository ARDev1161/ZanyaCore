#include "camcalibrate.h"
#include "ui_camcalibrate.h"

CamCalibrate::CamCalibrate(Mat *source, CamSettingsHolder *holder, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CamCalibrate)
{
    ui->setupUi(this);

    camHolder = holder;
    sourceMat = source;
}

CamCalibrate::~CamCalibrate()
{
    delete ui;
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

    numSquares = numCornersHor * numCornersVer;
    boardSize = Size(numCornersHor, numCornersVer);

    intrinsic = Mat(3, 3, CV_32FC1);
    intrinsic.ptr<float>(0)[0] = 1;
    intrinsic.ptr<float>(1)[1] = 1;


    for(int j=0; j < numSquares; j++)
            obj.push_back(Point3f(j / numCornersHor, j % numCornersHor, 0.0f));

    started = true;
}

void CamCalibrate::getCalibInfo()
{
        cvtColor(*sourceMat, gray, COLOR_BGR2GRAY);

        bool found = findChessboardCorners(gray, boardSize, corners, CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE | CALIB_CB_FILTER_QUADS | CALIB_CB_FAST_CHECK);
        if(found){
            cornerSubPix(gray, corners, Size(11, 11), Size(-1, -1), TermCriteria(TermCriteria::EPS | TermCriteria::MAX_ITER, 30, 0.1));

            drawChessboardCorners(*sourceMat, boardSize, corners, found);

            image_points.push_back(corners);
            object_points.push_back(obj);

            successes++;

            calibrateCamera(object_points, image_points, gray.size(), intrinsic, distCoeffs, rvecs, tvecs);

            camHolder->setDistCoeffs(distCoeffs);
            camHolder->setIntrinsic(intrinsic);
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

void CamCalibrate::on_buttonBox_accepted()
{
        camHolder->setReady(true);
}

void CamCalibrate::on_buttonBox_rejected()
{

}
