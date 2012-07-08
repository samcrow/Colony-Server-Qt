#-------------------------------------------------
#
# Project created by QtCreator 2012-06-13T12:51:54
#
#-------------------------------------------------

QT       += core gui network timer

TARGET = QtColonyServer
TEMPLATE = app


SOURCES += main.cpp\
		colonyserver.cpp \
	serverthread.cpp \
    colony.cpp \
    clientdatamodel.cpp \
    csvloader.cpp \
    mapdraw.cpp

HEADERS  += colonyserver.hpp \
	serverthread.hpp \
    colony.hpp \
    clientdatamodel.hpp \
    csvloader.hpp \
    mapdraw.hpp

FORMS    += colonyserver.ui
