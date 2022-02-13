QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

INCLUDEPATH += .
INCLUDEPATH += /usr/local/include
INCLUDEPATH += /usr/local/include/opencv4
INCLUDEPATH += /usr/local/include/opencv4/opencv2
INCLUDEPATH += /usr/local/include/opencv4/opencv2/core
INCLUDEPATH += /usr/local/include/opencv4/opencv2/highgui
INCLUDEPATH += /usr/local/include/opencv4/opencv2/imgproc
INCLUDEPATH += /usr/local/include/opencv4/opencv2/flann
INCLUDEPATH += /usr/local/include/opencv4/opencv2/photo
INCLUDEPATH += /usr/local/include/opencv4/opencv2/video
INCLUDEPATH += /usr/local/include/opencv4/opencv2/features2d
INCLUDEPATH += /usr/local/include/opencv4/opencv2/objdetect
INCLUDEPATH += /usr/local/include/opencv4/opencv2/calib3d
INCLUDEPATH += /usr/local/include/opencv4/opencv2/ml
INCLUDEPATH += /usr/local/include/opencv4/opencv2/contrib

LIBS += `pkg-config opencv4 --cflags --libs`

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
