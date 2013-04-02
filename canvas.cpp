#include "canvas.h"
#include "Utils.h"
#include "Link.h"
#include "network.h"
#include <vector>
#include <QDebug>
#include <math.h>
#include <QGraphicsLineItem>
#include <QtWidgets/QColorDialog>

extern int axis_number;

Canvas::Canvas(QObject *parent) :
    QGraphicsScene(parent)
{
}

void Canvas::initialize(){
    links.clear();
    x, y = 0;

    brushSize = 15;
    paintToggle = false;
    paintPen.setColor(Qt::red);
    paintBrush.setColor(Qt::red);
    paintBrush.setStyle(Qt::SolidPattern);
    paintPen.setWidth(2);
    paintPen.setStyle(Qt::SolidLine);

    blackBrush.setStyle(Qt::SolidPattern);
    blackPen.setStyle(Qt::SolidLine);
    blackPen.setWidth(5);

    rootLink = new Link();
    links.push_back(rootLink);
    for(int i = 1; i < NUM_LINKS; i++){
        Link* tempLink = new Link();
        tempLink->setPrevious(links[i-1]);
        links[i-1]->setNext(tempLink);
        links.push_back(tempLink);
    }
    links[0]->setLength(150);
    links[1]->setLength(100);
    links[2]->setLength(75);
    links[0]->setTheta(90);
    updateLinks();
}

void Canvas::updateLinks(){
    Link* currLink = rootLink;
    while(true) {
        delete currLink->getDrawnLine();
        QGraphicsLineItem* newLine = this->addLine(currLink->getLine(),blackPen);
        currLink->setDrawnLine(newLine);
        if(currLink->getNext() == NULL)
            break;
        currLink = currLink->getNext();
    }

    x = calcX();
    y = calcY();
    paint();
}

void Canvas::rotateCW()
{
    double newTheta = (links[axis_number-1]->getTheta()+BASE_ANGLE);
    links[axis_number-1]->setTheta(newTheta);
    emit sendMsg(CW, axis_number);
    updateLinks();
}

void Canvas::rotateCCW()
{
    double newTheta = (links[axis_number-1]->getTheta()-BASE_ANGLE);
    links[axis_number-1]->setTheta(newTheta);
    emit sendMsg(CCW, axis_number);
    updateLinks();
}

void Canvas::addX()
{
    //newX = x+XYMOVE;
    newX = x-XYMOVE;
    newY = y;
    emit sendMsg(ADDX, 0);
    worldMove();
}

void Canvas::subX()
{
    //newX = x-XYMOVE;
    newX = x+XYMOVE;
    newY = y;
    emit sendMsg(SUBX, 0);
    worldMove();
}

void Canvas::addY()
{
    newX = x;
    newY = y+XYMOVE;
    emit sendMsg(ADDY, 0);
    worldMove();
}

void Canvas::subY()
{
    newX = x;
    newY = y-XYMOVE;
    emit sendMsg(SUBY, 0);
    worldMove();
}

/* This function traverses through the robot's links and keeps a running total of the
 * links' projections onto the x-axis to calculate the end effector x-coordinate.
 */
double Canvas::calcX(){
    double x0 = 0;
    Link* currLink = rootLink;
    while(true){
        x0 += currLink->getLength()*cos(currLink->getOrientation()*DEG_TO_RAD);
        if(currLink->getNext() == NULL)
            break;
        currLink = currLink->getNext();
    }
    return x0;
}

double Canvas::calcY(){
    double y0 = 0;
    Link* currLink = rootLink;
    while(true){
        y0 += currLink->getLength()*sin(currLink->getOrientation()*DEG_TO_RAD);
        if(currLink->getNext() == NULL)
            break;
        currLink = currLink->getNext();
    }
    return y0;
}

double dabs(double k){
    if(k > 0) return k;
    else return -k;
}

void Canvas::worldMove(){
    double sld = dabs(sqrt(pow(newX,2)+pow(newY,2)));
    if(sld > 325) return;
    double alpha, beta, psi, theta1, theta2, theta3 = 0;
    double tempX, tempY = 0;
    double l1 = links[0]->getLength();
    double l2 = links[1]->getLength();
    if(sld > 305){
        alpha = atan2(newY,newX)*RAD_TO_DEG;
    } else if(sld > 125){
        alpha = (sld-125)-90-(90-atan2(newY,newX)*RAD_TO_DEG);
    } else {
        alpha = -atan2(newY,newX)*RAD_TO_DEG;
        alpha = 180-alpha;
    }
    tempX = newX-links[2]->getLength()*cos(alpha*DEG_TO_RAD);
    tempY = newY-links[2]->getLength()*sin(alpha*DEG_TO_RAD);
    theta2 = acos((pow(tempX,2)+pow(tempY,2)-pow(l1,2)-pow(l2,2))/(2*l1*l2))*RAD_TO_DEG;
    psi = acos((pow(tempX,2)+pow(tempY,2)+pow(l1,2)-pow(l2,2))/(2*l1*sqrt(pow(tempX,2)+pow(tempY,2))))*RAD_TO_DEG;
    beta = atan2(tempY,tempX)*RAD_TO_DEG;
    if(theta2 <= 0){
        theta1 = beta + psi;
    } else {
        theta1 = beta - psi;
    }
    theta3 = alpha-theta1-theta2;
    if(isnan(theta1)) return;
    if(isnan(theta2)) return;
    if(isnan(theta3)) return;
    links[0]->setTheta(theta1);
    links[1]->setTheta(theta2);
    links[2]->setTheta(theta3);
    updateLinks();
}

void Canvas::paintClicked() {
    paintToggle = !paintToggle;
    paint();
    sendMsg(PAINT, 0);
}

void Canvas::paint(){
    Link* link = links[2];
    QPoint endEffector(link->getLine().x2(), link->getLine().y2());
    if (paintToggle)
        this->addEllipse((int)endEffector.x()- brushSize/2,(int)endEffector.y()- brushSize/2,brushSize,brushSize,paintPen,paintBrush);
}

void Canvas::changeColor(){
    QColor color = QColorDialog::getColor();
    const QColor newColor(color.red(), color.green(), color.blue());
    paintBrush.setColor(newColor);
    paintPen.setColor(newColor);
    paint();
}

void Canvas::changeSize(int newSize){
    brushSize = newSize;
}


void Canvas::setX(double x0){
    newX = x0;
}

void Canvas::setY(double y0){
    newY = y0;
}
