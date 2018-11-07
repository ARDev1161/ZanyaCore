#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initFields();
    connMenu();

    startTimer();
    startCap();
}

MainWindow::~MainWindow()
{
    capture.release();
    delete ui;
}

void MainWindow::initFields()
{
    sourceMat = imread(NO_PICTURE);
    outputMat = sourceMat;

    zanyaControl = new Control();

    camHolder = new CamSettingsHolder();

    idHolder = new JoystickIdHolder();
    joystickDialog = new JoystickDialog(idHolder, this);

    connect(joystickDialog, &JoystickDialog::accepted, this, &MainWindow::fetchJoystickId);
}

void MainWindow::frameUpdate()
{
    if(capture.read(sourceMat)){
        worker();
    }
}

void MainWindow::startCap()
{
    capture.open(SOURCE_STREAM);

    if(!capture.isOpened())
        return;

    frameUpdate();
}

void MainWindow::startTimer()
{
    tmrTimer = new QTimer(this);
    connect(tmrTimer,SIGNAL(timeout()),this,SLOT(frameUpdate()));
    connect(tmrTimer, &QTimer::timeout, this, &MainWindow::timeout);
    tmrTimer->start(LoopTime); //msec
}

void MainWindow::outMat(Mat &toOut)
{
    QImage qimgOut((uchar*) toOut.data, toOut.cols, toOut.rows, toOut.step,QImage::Format_RGB888);
    ui->OutLabel->setPixmap(QPixmap::fromImage(qimgOut));
}

void MainWindow::worker()
{
    flip(sourceMat, sourceMat, 1);
    cv::resize(sourceMat, sourceMat, Size(320, 240));

    undistortMat(sourceMat, outputMat);

    zanyaLogic->setSrcMat(&outputMat);
    outputMat = zanyaLogic->getOutMat();

    outMat(outputMat);
}

void MainWindow::undistortMat(Mat &inMat, Mat &outMat)
{
    if(camHolder->getReady())
        outMat = camHolder->remap(inMat);
    else
        outMat = inMat;
}

void MainWindow::zanyaHalt()
{
    zanyaControl->setFlagHalt(true);
}

void MainWindow::zanyaReboot()
{
    zanyaControl->setFlagRestart(true);
}

void MainWindow::calibDialogOpen()
{
    CamCalibrate *calibDialog;
    calibDialog = new CamCalibrate(&sourceMat, camHolder, this);

    connect(this, &MainWindow::timeout, calibDialog, &CamCalibrate::frameUpdate);
    connect(calibDialog, &CamCalibrate::finished, calibDialog, &CamCalibrate::deleteLater);

    if(camHolder->getReady())camHolder->setReady(false);
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
    // File menu
    connect(ui->action_Joystick, SIGNAL(triggered()), this, SLOT(menuJoystick()));
    // Zanya menu
    connect(ui->action_Halt, SIGNAL(triggered()), this, SLOT(zanyaHalt()));
    connect(ui->action_Reboot, SIGNAL(triggered()), this, SLOT(zanyaReboot()));
    connect(ui->actionCamera, SIGNAL(triggered()), this, SLOT(calibDialogOpen()));
}
