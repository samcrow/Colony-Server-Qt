#ifndef MAPDRAW_HPP
#define MAPDRAW_HPP

#include <QObject>
#include <QGraphicsScene>
#include <QDebug>
#include <QRect>
#include <QList>
#include <QListIterator>
#include "colony.hpp"

class MapDraw : public QObject
{
    Q_OBJECT
public:
    explicit MapDraw(QObject *parent = 0);

    void draw(QList<Colony *> * colonies, QGraphicsScene *scene);

    QRect getColonyRect(QList<Colony *> *colonies);
signals:

public slots:

private:


};

#endif // MAPDRAW_HPP
