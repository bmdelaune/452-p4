#include "Link.h"
#include <stdlib.h>
#include <math.h>
#include "Utils.h"

Link::Link()
{
    theta = 0;
    next = NULL;
    previous = NULL;
    line = NULL;
}

Link::~Link(){
    delete this;
}

double Link::getLength(){
    return length;
}

void Link::setLength(double l){
    length = l;
}

double Link::getTheta(){
    return theta;
}

void Link::setTheta(double t){
    theta = t;
}

double Link::getOrientation(){
    if(previous == NULL){
        return theta;
    } else {
        return theta+previous->getOrientation();
    }
}

Link* Link::getNext(){
    return next;
}

void Link::setNext(Link* n){
    next = n;
}

Link* Link::getPrevious(){
    return previous;
}

void Link::setPrevious(Link* p){
    previous = p;
}

QLine Link::getLine(){
    if(previous == NULL){
        return QLine(0,0,length*cos(theta*DEG_TO_RAD),length*sin(theta*DEG_TO_RAD));
    } else {
        QLine prevLine = previous->getLine();
        double orientation = getOrientation()*DEG_TO_RAD;
        return QLine(prevLine.x2(),prevLine.y2(),prevLine.x2()+length*cos(orientation),prevLine.y2()+length*sin(orientation));
    }
}

void Link::setDrawnLine(QGraphicsLineItem* newLine){
    line = newLine;
}

QGraphicsLineItem* Link::getDrawnLine(){
    return line;
}
