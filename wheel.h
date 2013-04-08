#ifndef WHEEL_H
#define WHEEL_H

#include <QPointF>

class Wheel
{
public:
    Wheel();
    double getVelocity();
    void setVelocity(double);
    QPointF getLoc();
    void setLoc(QPointF);
private:
    double velocity;
    QPointF loc;
};

#endif // WHEEL_H
