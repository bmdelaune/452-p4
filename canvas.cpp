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

    LightSource* lightSource = new LightSource();
    m_robotManager->setLightSource(lightSource);
    this->addItem(lightSource);
}

void Canvas::createRobot(Robot *robot)
{
    m_robotManager->addRobot(robot);
    this->addItem(robot);
}

QVector<QPointF> Canvas::generateLoc(int num) {
    QVector<QPointF> vec;
    int x = 1;
    for (int i = 0; i < num; i++)
    {
        QPointF point;
        point.setX(i);
        point.setY(i);
        /*if (i % 4 == 0)
        {
            point.setX(300 - (50 * x));
            point.setY(300 - (50 * x));
        }
        else if (i % 3 == 0)
        {
            point.setX(300 - (50 * x));
            point.setY(-300 + (50 * x));
            x++;
        }
        else if (i % 2 == 0)
        {
            point.setX(-300 + (50 * x));
            point.setY(-300 + (50 * x));
        }
        else
        {
            point.setX(-300 + (50 * x));
            point.setY(300 - (50 * x));
        }*/
        qDebug() << "POINT" << i << "is" << point.x() << "," << point.y();
        vec.push_back(point);
    }
    return vec;
}

void Canvas::setup(int bots, QVector<QPointF> locations) {
    if (bots == 0)
    {
        bots = 1;
        qDebug() << "ERROR: Invalid number of robots. Defaulting to 1.";
    }
    if (locations.size() < bots)
    {
        locations.clear();
        locations = generateLoc(bots);
        qDebug() << "ERROR: Not enough locations. Using the default locations.";
    }
    Robot* robot;
    for(int i = 0; i < bots; i++) {
        robot = new Robot();
        robot->setPos(locations[i]);
        createRobot(robot);
    }
}


