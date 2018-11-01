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

    connJoy();
    startCap();
    startTimer();
}

MainWindow::~MainWindow()
{
    delete ui;
    capture.release();
    SDL_Quit();
}

void MainWindow::FrameUpdate()
{
    if(capture.read(Src)){
        Worker();
    }
}

void MainWindow::startCap()
{
    capture.open(0); //"udpsrc port=1488 ! application/x-rtp, encoding-name=H264 ! "
                  //"rtph264depay ! h264parse ! avdec_h264 ! videoconvert ! appsink");
    if(!capture.isOpened()){
        return;
    }
    FrameUpdate();
}

void MainWindow::startTimer()
{
    tmrTimer = new QTimer(this);
    connect(tmrTimer,SIGNAL(timeout()),this,SLOT(FrameUpdate()));
    tmrTimer->start(LoopTime); //msec
}

void MainWindow::outMat(Mat &ToOut)
{
    QImage qimgOut((uchar*) ToOut.data, ToOut.cols, ToOut.rows, ToOut.step,QImage::Format_RGB888);
    ui->OutLabel->setPixmap(QPixmap::fromImage(qimgOut));
}

void MainWindow::Worker()
{
    flip(Src, Src, 1);
    cv::resize(Src, Src, Size(320, 240));
    outMat(Src);
    undistortMat();

    qDebug() << zanyaControl->getXAngle() << "\t" << zanyaControl->getYAngle() << endl;
}

void MainWindow::undistortMat(/*Mat &inMat, Mat &outMat*/)
{

}

void MainWindow::MenuJoystick()
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

void MainWindow::connJoy()
{
    connect(ui->action_Joystick, SIGNAL(triggered()), this, SLOT(MenuJoystick()));
}
