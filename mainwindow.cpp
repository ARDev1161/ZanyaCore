#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    zanyaControl = new Control();

    idHolder = new JoystickIdHolder();
    joystickDialog = new JoystickDialog(idHolder, this);
    connect(joystickDialog, &JoystickDialog::accepted, this, &MainWindow::fetchJoystickId);

    connMenu();
    startCap();
    startTimer();

}

MainWindow::~MainWindow()
{
    capture.release();
    delete ui;
}

void MainWindow::frameUpdate()
{
    if(capture.read(sourceMat)){
        worker();
    }
}

void MainWindow::startCap()
{
    capture.open(0); //"udpsrc port=1488 ! application/x-rtp, encoding-name=H264 ! "
                  //"rtph264depay ! h264parse ! avdec_h264 ! videoconvert ! appsink");
    if(!capture.isOpened()){
        return;
    }
    frameUpdate();
}

void MainWindow::startTimer()
{
    tmrTimer = new QTimer(this);
    connect(tmrTimer,SIGNAL(timeout()),this,SLOT(frameUpdate()));
    connect(tmrTimer, &QTimer::timeout, this, &MainWindow::timeout);
    tmrTimer->start(LoopTime); //msec
}

void MainWindow::outMat(Mat &ToOut)
{
    QImage qimgOut((uchar*) ToOut.data, ToOut.cols, ToOut.rows, ToOut.step,QImage::Format_RGB888);
    ui->OutLabel->setPixmap(QPixmap::fromImage(qimgOut));
}

void MainWindow::worker()
{
    flip(sourceMat, sourceMat, 1);
    cv::resize(sourceMat, sourceMat, Size(320, 240));
    outMat(sourceMat);
    undistortMat();
}

void MainWindow::undistortMat(/*Mat &inMat, Mat &outMat*/)
{

}

void MainWindow::calibDialogOpen()
{
    CamCalibrate *calibDialog;
    calibDialog = new CamCalibrate(&sourceMat, this);
    connect(this, &MainWindow::timeout, calibDialog, &CamCalibrate::frameUpdate);
    connect(calibDialog, &CamCalibrate::finished, calibDialog, &CamCalibrate::deleteLater);
    calibDialog->exec();
}

void MainWindow::menuJoystick()
{
    joystickDialog->exec();
}

void MainWindow::fetchJoystickId()
{
    if (idHolder == nullptr)
        return;

    //implement here
    int id = idHolder->getJoyId();

    joyThread = new Joystick(id, zanyaControl);
    joyThread->addThread();

    tcpThread = new TCP(zanyaControl, zanyaSensors, hostName);
    tcpThread->addThread();

}

void MainWindow::connMenu()
{
    connect(ui->actionCamera, SIGNAL(triggered()), this, SLOT(calibDialogOpen()));
    connect(ui->action_Joystick, SIGNAL(triggered()), this, SLOT(menuJoystick()));
}
