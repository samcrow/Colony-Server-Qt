#ifndef COLONY_HPP
#define COLONY_HPP

#include <QDebug>
#include <QTextStream>

/**
  Stores data for one colony
  @author Sam Crow
  */
class Colony
{
public:
    Colony(int colonyNumber, int inX, int inY, bool isActive);

    //getters
    int getID();
    double getX();
    double getY();
    bool isActive();

    //setters
    void setX(double inX);
    void setY(double inY);
    void setActive(bool isActive);

    QString toString();

protected:
    /** Distance in meters east of the orgin (The orgin is at the southwest corner) */
    double x;

    /** Distance in meters north of the origin (The origin is at the southwest corner) */
    double y;

    /** The colony number */
    int id;

    /** If the colony is currently active */
    bool active;
};

#endif // COLONY_HPP
