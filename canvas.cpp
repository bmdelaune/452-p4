#include "canvas.h"
#include "Utils.h"
#include <vector>
#include <QDebug>
#include "robot.h"

Canvas::Canvas(QObject *parent) :
    QGraphicsScene(parent)
{
}

void Canvas::initialize(){
    Robot* robot = new Robot();
    robot->setPos(100, 100);
    this->addItem(robot);
}


