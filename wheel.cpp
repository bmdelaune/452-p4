#include "wheel.h"

Wheel::Wheel()
{
}

double Wheel::getVelocity(){
    return velocity;
}

void Wheel::setVelocity(double v){
    velocity = v;
}

QPointF Wheel::getLoc(){
    return loc;
}

void Wheel::setLoc(QPointF f){
    loc.setX(f.x());
    loc.setY(f.y());
}
