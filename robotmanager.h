#ifndef ROBOTMANAGER_H
#define ROBOTMANAGER_H

#include <vector>
#include "robot.h"
#include "lightsource.h"
#include <QGraphicsItemAnimation>

using namespace std;

class RobotManager : public QObject
{
    Q_OBJECT
public:

    RobotManager(QObject *parent = 0);
    ~RobotManager() {}
    void addRobot(Robot* robot) { robot->setId(m_robots.size()); m_robots.push_back(robot); }
    void addLight(LightSource* light) { light->setId(m_lights.size()); m_lights.push_back(light); }
    void updateVelocities();
    double getIntensity(LightSource *light, Robot *robot, Robot::Side side);
    void clearMgr();
    void setKMatrix(int** _kMatrix) {m_kmatrix = _kMatrix; }

public slots:
    void moveRobots();

private:
    vector<Robot*> m_robots;
    vector<LightSource*> m_lights;
    QGraphicsItemAnimation* animation;
    int** m_kmatrix;


};

#endif // ROBOTMANAGER_H
