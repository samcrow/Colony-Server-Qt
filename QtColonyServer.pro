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
	serverthread.cpp

HEADERS  += colonyserver.hpp \
	serverthread.hpp

FORMS    += colonyserver.ui
