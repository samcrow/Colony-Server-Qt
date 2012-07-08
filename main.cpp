#include <QtGui/QApplication>
#include <QCoreApplication>
#include "colonyserver.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setApplicationName("Colony Server");
    QCoreApplication::setOrganizationName("Sam Crow");
    QCoreApplication::setOrganizationDomain("org.samcrow");
    QCoreApplication::setApplicationVersion("1.0-alpha");

    ColonyServer w;
    w.show();

    return a.exec();
}
