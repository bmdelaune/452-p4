#include "canvas.h"
#include "Utils.h"
#include <vector>
#include <QDebug>
#include "robot.h"
#include "lightsource.h"


Canvas::Canvas(QObject *parent) :
    QGraphicsScene(parent)
{
}

void Canvas::initialize(){
    m_robotManager = new RobotManager();
    Robot* robot;
    for(int i=0; i<1; i++) {
        robot = new Robot();
        robot->setPos(100*i, 100);
        createRobot(robot);

    }
    LightSource* lightSource = new LightSource();
    m_robotManager->setLightSource(lightSource);
    this->addItem(lightSource);
}

void Canvas::createRobot(Robot *robot)
{
    m_robotManager->addRobot(robot);
    this->addItem(robot);
}


