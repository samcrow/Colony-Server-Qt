#include "mapdraw.hpp"

MapDraw::MapDraw(QObject *parent) :
    QObject(parent)
{
}

/*
  Note: the colonies are defined in a coordinate system with the bottom left corner at (0,0).
  The graphics scene has the top left corner at (0,0).
  */
void MapDraw::draw(QList<Colony *> *colonies, QGraphicsScene *scene){

    QListIterator<Colony *> drawIterator(*colonies);
    while(drawIterator.hasNext()){
        Colony *colony = drawIterator.next();
        scene->addRect((qreal)colony->getX(), getColonyRect(colonies).height() - (qreal)colony->getY(), (qreal)5, (qreal)5);
    }
}

QRect MapDraw::getColonyRect(QList<Colony *> * colonies){
    //Find the most north colony
    double furthestNorth = 0;
    QListIterator<Colony *> northIterator(*colonies);
    while(northIterator.hasNext()){
        Colony *colony = northIterator.next();
        double colonyY = colony->getY();
        if(colonyY > furthestNorth){
            furthestNorth = colonyY;
        }
    }

    //Find the most east colony
    double furthestEast = 0;
    QListIterator<Colony *> eastIterator(*colonies);
    while(eastIterator.hasNext()){
        Colony *colony = eastIterator.next();
        double colonyX = colony->getX();
        if(colonyX > furthestEast){
            furthestEast = colonyX;
        }
    }

    qDebug() << "Colony size limits: " << furthestNorth << furthestEast;

    return QRect(0, 0, (int) furthestEast, (int) furthestNorth);
}
