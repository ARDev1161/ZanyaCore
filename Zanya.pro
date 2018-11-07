#-------------------------------------------------
#
# Project created by QtCreator 2018-10-18T06:43:04
#
#-------------------------------------------------

QT       += core gui multimedia network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimediawidgets

TARGET = Zanya
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        zanyacore.cpp \
        logic/logic.cpp \
        joystick/v_joystick_adapter.cpp \
        joystick/joystickdialog.cpp \
        joystick/getstatebyjoy.cpp \
        joystick/joystickidholder.cpp \
        joystick/joystickstateworker.cpp \
        joystick/joystick.cpp \
        control/light.cpp \
        control/motors.cpp \
        control/servos.cpp \
        control/system.cpp \
        control/vibro.cpp \
        control/control.cpp \
        sensors/accelerometer.cpp \
        sensors/gyroscope.cpp \
        sensors/motorencoders.cpp \
        sensors/temperature.cpp \
        sensors/sensors.cpp \
        network/tcp/tcpcontrol.cpp \
        network/tcp/tcpsensors.cpp \
        network/tcp/tcpworker.cpp \
        network/tcp/tcp.cpp \
        network/protobuf/control.pb.cc \
        network/protobuf/sensors.pb.cc \
        camera/camcalibrate.cpp \
        camera/camsettingsholder.cpp \
        camera/calibrator.cpp \
        camera/calibratorworker.cpp \
        threads/session.cpp \
        threads/worker.cpp \
    network/connectdialog.cpp

CONFIG += precompile_header
PRECOMPILED_HEADER = pch.h

HEADERS += \
        pch.h \
        zanyacore.h \
        logic/logic.h \
        joystick/v_joystick_adapter.h \
        joystick/joystickdialog.h \
        joystick/getstatebyjoy.h \
        joystick/joystickidholder.h \
        joystick/joystickstateworker.h \
        joystick/joystick.h \
        control/light.h \
        control/motors.h \
        control/servos.h \
        control/system.h \
        control/vibro.h \
        control/control.h \
        sensors/accelerometer.h \
        sensors/gyroscope.h \
        sensors/motorencoders.h \
        sensors/temperature.h \
        sensors/sensors.h \
        network/tcp/tcpcontrol.h \
        network/tcp/tcpsensors.h \
        network/tcp/tcpworker.h \
        network/tcp/tcp.h \
        network/protobuf/control.pb.h \
        network/protobuf/sensors.pb.h \
        camera/camcalibrate.h \
        camera/camsettingsholder.h \
        camera/calibrator.h \
        camera/calibratorworker.h \
        threads/session.h \
        threads/worker.h \
    network/connectdialog.h

FORMS += \
        mainwindow.ui \
        joystick/joystickdialog.ui \
        camera/camcalibrate.ui \
    network/connectdialog.ui

INCLUDEPATH += /usr/local/include/opencv4/

INCLUDEPATH += /usr/include/SDL/

LIBS += -lSDL

LIBS += -L$$LIBS_PATH /
LIBS += -lprotobuf \
        -lopencv_core \
        -lopencv_calib3d \
        -lopencv_ml \
        -lopencv_dnn \
        -lopencv_features2d \
        -lopencv_flann \
        -lopencv_imgproc \
        -lopencv_imgcodecs \
        -lopencv_highgui \
        -lopencv_objdetect \
        -lopencv_photo \
        -lopencv_shape \
        -lopencv_stitching \
        -lopencv_superres \
        -lopencv_video \
        -lopencv_videoio \
        -lopencv_videostab \

DISTFILES += \
        network/protobuf/control.proto \
        network/protobuf/sensors.proto \
        README.md \
        data/images/no_picture.jpeg

SUBDIRS += \
        Zanya.pro
