#include "colony.hpp"

Colony::Colony(int colonyNumber, int inX, int inY, bool isActive)
{
    id = colonyNumber;
    x = inX;
    y = inY;
    active = isActive;
}

int Colony::getID(){
    return id;
}

double Colony::getX(){
    return x;
}

double Colony::getY(){
    return y;
}

bool Colony::isActive(){
    return active;
}

void Colony::setX(double inX){
    x = inX;
}

void Colony::setY(double inY){
    y = inY;
}

void Colony::setActive(bool isActive){
    active = isActive;
}

QString Colony::toString(){
    QString string;
    QTextStream stream(&string);

    stream << "Colony #" << id << " at (" << x << ", " << y << "), active=" << active << ".";
    return string;
}
