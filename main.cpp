#include <QtGui/QApplication>
#include "colonyserver.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ColonyServer w;
    w.show();
    
    return a.exec();
}
