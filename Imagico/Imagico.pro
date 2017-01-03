#-------------------------------------------------
#
# Project created by QtCreator 2016-12-11T23:06:57
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Imagico
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ajouterdialogfiche.cpp \
    fichetechniqueimage.cpp \
    recherchedialogfiche.cpp \
    triedialogfiche.cpp \
    logindialog.cpp \
    utilisateur.cpp

HEADERS  += mainwindow.h \
    ajouterdialogfiche.h \
    fichetechniqueimage.h \
    recherchedialogfiche.h \
    triedialogfiche.h \
    logindialog.h \
    utilisateur.h

FORMS    += mainwindow.ui \
    ajouterdialogfiche.ui \
    recherchedialogfiche.ui \
    triedialogfiche.ui \
    logindialog.ui

RESOURCES += \
    ressources.qrc

DISTFILES +=


