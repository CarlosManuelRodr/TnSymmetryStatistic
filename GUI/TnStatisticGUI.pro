#-------------------------------------------------
#
# Project created by QtCreator 2016-05-02T21:07:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = TnStatisticGUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ../common/TnStatistic.cpp \
    qcustomplot.cpp \
    plotdialog.cpp \
    waitdialog.cpp \
    calculationthread.cpp \
    ../common/Auxiliary.cpp

HEADERS  += mainwindow.h \
    ../common/Auxiliary.h \
    ../common/spline.h \
    ../common/TnStatistic.h \
    qcustomplot.h \
    plotdialog.h \
    waitdialog.h \
    calculationthread.h

FORMS    += mainwindow.ui \
    plotdialog.ui \
    waitdialog.ui

RESOURCES += \
    resources.qrc

RC_ICONS = icon.ico