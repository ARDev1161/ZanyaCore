#include "zanyacore.h"
#include "ui_mainwindow.h"

ZanyaCore::ZanyaCore(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initFields();
    connMenu();

    startTimer();
    startCap();
}

ZanyaCore::~ZanyaCore()
{
    capture.release();
    delete ui;
}

void ZanyaCore::initFields()
{
    sourceMat = imread(NO_PICTURE);
    outputMat = sourceMat;

    zanyaControl = new Control();

    camHolder = new CamSettingsHolder();

    idHolder = new JoystickIdHolder();
    joystickDialog = new JoystickDialog(idHolder, this);

    connect(joystickDialog, &JoystickDialog::accepted, this, &ZanyaCore::fetchJoystickId);
}

void ZanyaCore::connMenu()
{
    // File menu
    connect(ui->action_Joystick, SIGNAL(triggered()), this, SLOT(menuJoystick()));
    connect(ui->actionE_xit, SIGNAL(triggered(bool)), this, SLOT(close()));
    // Zanya menu
    connect(ui->action_Connect, SIGNAL(triggered()), this, SLOT(connectDialogOpen()));
    connect(ui->action_Halt, SIGNAL(triggered()), this, SLOT(zanyaHalt()));
    connect(ui->action_Reboot, SIGNAL(triggered()), this, SLOT(zanyaReboot()));
    connect(ui->actionCamera, SIGNAL(triggered()), this, SLOT(calibDialogOpen()));
}

void ZanyaCore::startTimer()
{
    tmrTimer = new QTimer(this);
    connect(tmrTimer,SIGNAL(timeout()),this,SLOT(frameUpdate()));
    connect(tmrTimer, &QTimer::timeout, this, &ZanyaCore::timeout);
    tmrTimer->start(loopTime); //msec
}

void ZanyaCore::startCap()
{
    capture.open(SOURCE_STREAM);

    if(!capture.isOpened())
        return;

    frameUpdate();
}

void ZanyaCore::frameUpdate()
{
    if(capture.read(sourceMat)){
        worker();
    }
}

void ZanyaCore::worker()
{
    flip(sourceMat, sourceMat, 1);
    cv::resize(sourceMat, sourceMat, Size(320, 240));

    undistortMat(sourceMat, outputMat);

    zanyaLogic->setSrcMat(&outputMat);
    outputMat = zanyaLogic->getOutMat();

    outMat(outputMat);
}

void ZanyaCore::outMat(Mat &toOut)
{
    QImage qimgOut((uchar*) toOut.data, toOut.cols, toOut.rows, toOut.step,QImage::Format_RGB888);
    ui->OutLabel->setPixmap(QPixmap::fromImage(qimgOut));
}

void ZanyaCore::undistortMat(Mat &inMat, Mat &outMat)
{
    if(camHolder->getReady())
        outMat = camHolder->remap(inMat);
    else
        outMat = inMat;
}

void ZanyaCore::zanyaHalt()
{
    zanyaControl->setFlagHalt(true);
}

void ZanyaCore::zanyaReboot()
{
    zanyaControl->setFlagRestart(true);
}

void ZanyaCore::connectDialogOpen()
{
    ConnectDialog *connDialog;
    connDialog = new ConnectDialog();

    connDialog->exec();

//    tcpThread = new TCP(zanyaControl, zanyaSensors, hostName);
//    tcpThread->addThread();
}

void ZanyaCore::calibDialogOpen()
{
    CamCalibrate *calibDialog;
    calibDialog = new CamCalibrate(&sourceMat, camHolder, this);

    connect(this, &ZanyaCore::timeout, calibDialog, &CamCalibrate::frameUpdate);
    connect(calibDialog, &CamCalibrate::finished, calibDialog, &CamCalibrate::deleteLater);

    if(camHolder->getReady())
        camHolder->setReady(false);
    calibDialog->exec();
}

void ZanyaCore::menuJoystick()
{
    joystickDialog->exec();
}

void ZanyaCore::fetchJoystickId()
{
    if (idHolder == nullptr)
        return;

    //implement here
    int id = idHolder->getJoyId();

    joyThread = new Joystick(id, zanyaControl);
    joyThread->addThread();

}
