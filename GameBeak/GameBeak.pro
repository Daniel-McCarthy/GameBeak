#-------------------------------------------------
#
# Project created by QtCreator 2018-09-27T09:57:26
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = GameBeak
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

CONFIG += c++11

SOURCES += \
    src/main.cpp \
    src/MainWindow/mainwindow.cpp \
    src/Rom.cpp \
    src/Memory.cpp \
    src/Core.cpp \
    src/Cpu.cpp \
    src/Binary.cpp \
    src/Input.cpp \
    src/Gpu.cpp \
    src/Screen.cpp \
    src/canvas.cpp \
    src/Mappers/MBC1.cpp \
    src/Mappers/MBC2.cpp \
    src/Mappers/MBC5.cpp \
    src/Mappers/MBC3.cpp \
    src/Mappers/Mapper.cpp \
    src/Forms/ColorDialog.cpp

HEADERS += \
    src/MainWindow/mainwindow.h \
    src/Rom.h \
    src/Memory.h \
    src/Core.h \
    src/Cpu.h \
    src/Binary.h \
    src/Input.h \
    src/Gpu.h \
    src/Screen.h \
    src/canvas.h \
    src/Mappers/MBC1.h \
    src/Mappers/MBC2.h \
    src/Mappers/MBC3.h \
    src/Mappers/MBC5.h \
    src/Mappers/Mapper.h \
    src/Forms/ColorDialog.h

FORMS += \
    src/MainWindow/mainwindow.ui \
    src/Forms/ColorDialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
