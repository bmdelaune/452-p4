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


    QGraphicsItemAnimation* animation = new QGraphicsItemAnimation(this);
     m_robotManager = new RobotManager(animation);
   /* LightSource* lightSource = new LightSource();
    m_robotManager->setLightSource(lightSource);
    this->addItem(lightSource);*/
}

void Canvas::createRobot(Robot *robot)
{
    m_robotManager->addRobot(robot);
    this->addItem(robot);
}

void Canvas::createLight(LightSource *light)
{
    m_robotManager->addLight(light);
    this->addItem(light);
}

QVector<QPointF> Canvas::defaultBotLoc(int num) {
    QVector<QPointF> vec;
    for (int i = 0; i < num; i++)
    {
        QPointF point;
        point.setX(50 * (i+1));
        point.setY(50 * (i+1));
        qDebug() << "BOTLOC" << i << "is" << point.x() << "," << point.y();
        vec.push_back(point);
    }
    return vec;
}

QVector<QPointF> Canvas::defaultLightLoc(int num) {
    QVector<QPointF> vec;
    for (int i = 0; i < num; i++)
    {
        QPointF point;
        point.setX(400 * (i+1));
        point.setY(400 * (i+1));
        qDebug() << "LIGHTLOC" << i << "is" << point.x() << "," << point.y();
        vec.push_back(point);
    }
    return vec;
}

void Canvas::setup(int bots, int lights, QVector<QPointF> botLoc, QVector<QPointF> lightLoc, int **matrix) {
    if (bots == 0)
    {
        bots = 1;
        qDebug() << "ERROR: Invalid number of robots. Defaulting to 1.";
    }
    if (lights == 0)
    {
        lights = 1;
        qDebug() << "ERROR: Invalid number of lights. Defaulting to 1.";
    }

    if (botLoc.size() < bots)
    {
        botLoc.clear();
        botLoc = defaultBotLoc(bots);
        qDebug() << "ERROR: Not enough robot locations. Using the default locations.";
    }
    if (lightLoc.size() < bots)
    {
        lightLoc.clear();
        lightLoc = defaultLightLoc(lights);
        qDebug() << "ERROR: Not enough light locations. Using the default locations.";
    }
    m_robotManager->setKMatrix(matrix);
    Robot* robot;
    for(int i = 0; i < bots; i++) {
        robot = new Robot();
        robot->setPos(botLoc[i]);
        robot->setTransformOriginPoint(-0.5 * QPointF(ROBOT_WIDTH/2, ROBOT_HEIGHT/2));
        createRobot(robot);
    }
    LightSource *light;
    for (int i = 0; i < lights; i++)
    {
        light = new LightSource();
        light->setPos(lightLoc[i]);
        // TODO: take intensity from a file
        light->setIntensity(100);
        createLight(light);
    }
}

void Canvas::clear() {
    m_robotManager->clear();
    qDeleteAll(this->items());
}

void Canvas::move()
{
    //m_robotManager->updateVelocities();
    m_robotManager->moveRobots();
}

