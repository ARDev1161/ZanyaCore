#include "zanyacore.h"
#include "ui_ZanyaCore.h"

ZanyaCore::ZanyaCore(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ZanyaCore)
{
    ui->setupUi(this);

    outputMat = imread("../ZanyaCore/data/images/no_picture.jpeg");

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
    zanyaControl = new Control();

    camHolder = new CamSettingsHolder();
    idHolder = new JoystickIdHolder();

    joystickDialog = new JoystickDialog(idHolder, this);
    speechDialog = new SpeechDialog(this);
    connectDialog = new ConnectDialog(this);
}

void ZanyaCore::connMenu()
{
    connect(joystickDialog, &JoystickDialog::accepted, this, &ZanyaCore::fetchJoystickId);

    // File menu
    connect(ui->action_Joystick, SIGNAL(triggered()), this, SLOT(joystickDialogOpen()));
    connect(ui->actionE_xit, SIGNAL(triggered(bool)), this, SLOT(close()));

    // Zanya menu
    connect(ui->action_Connect, SIGNAL(triggered()), this, SLOT(connectDialogOpen()));
    connect(ui->action_Halt, SIGNAL(triggered()), this, SLOT(zanyaHalt()));
    connect(ui->action_Reboot, SIGNAL(triggered()), this, SLOT(zanyaReboot()));
    connect(ui->actionCamera, SIGNAL(triggered()), this, SLOT(calibDialogOpen()));

    // Speech dialog
    connect(ui->action_Speech, SIGNAL(triggered()), this, SLOT(speechDialogOpen()));
}

void ZanyaCore::joystickDialogOpen()
{
    joystickDialog->exec();
}

void ZanyaCore::connectDialogOpen()
{
    if(tcpThread == nullptr){
       tcpThread = new TCP(zanyaControl, zanyaSensors, hostName);
       tcpThread->addThread();
    }

    connectDialog->exec();
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

void ZanyaCore::resizeEvent(QResizeEvent *event)
{
    QImage qimgOut((uchar*) outputMat.data, outputMat.cols, outputMat.rows, outputMat.step, QImage::Format_RGB888);

    ui->OutLabel->setPixmap(QPixmap::fromImage(qimgOut).scaled(
                    this->width() - 16,
                    this->height() - 60
                    ));
}

void ZanyaCore::speechDialogOpen()
{
    speechDialog->exec();
}

void ZanyaCore::zanyaHalt()
{
    zanyaControl->setFlagHalt(true);
}

void ZanyaCore::zanyaReboot()
{
    zanyaControl->setFlagRestart(true);
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

void ZanyaCore::outMat(Mat &toOut)
{
    QImage qimgOut((uchar*) toOut.data, toOut.cols, toOut.rows, toOut.step, QImage::Format_RGB888);

    ui->OutLabel->setPixmap(QPixmap::fromImage(qimgOut).scaled(
                                this->width() - 16,
                                this->height() - 60
                                ));
}

void ZanyaCore::undistortMat(Mat &inMat, Mat &outMat)
{
    if(camHolder->getReady())
        outMat = camHolder->remap(inMat);
    else
        outMat = inMat;
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
