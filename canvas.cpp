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

void Canvas::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << event->scenePos();

}

void Canvas::initialize(){


    m_robotManager = new RobotManager();
    m_robotManager->setCanvas(this);
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
        point.setX(100 * (i+1) + 500);
        point.setY(100 * (i+1));
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

    this->addLine(0,0,400,400);
    if (bots == 0)
    {
        bots = 2;
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
        robot = new Robot(i);

        robot->setPos(botLoc[i]);

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
    m_robotManager->startAnimation();

}
