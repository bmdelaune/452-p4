#ifndef WHEEL_H
#define WHEEL_H

#include <QPointF>

class Wheel
{
public:
    Wheel();
    double getVelocity();
    void setVelocity(double);
private:
    double velocity;
};

#endif // WHEEL_H
