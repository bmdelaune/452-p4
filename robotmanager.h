#ifndef ROBOTMANAGER_H
#define ROBOTMANAGER_H

#include <vector>
#include "robot.h"
#include "lightsource.h"
#include <QParallelAnimationGroup>

using namespace std;

class RobotManager
{
public:

    RobotManager();
    void addRobot(Robot* robot) { robot->setId(m_robots.size()); m_robots.push_back(robot); }

    void addLight(LightSource* light) { light->setId(m_lights.size()); m_lights.push_back(light); }
    void updateVelocities();
    double getIntensity(LightSource *light, Robot *robot, Robot::Side side);
    void clear();
    void moveRobots();
    void setKMatrix(int** _kMatrix) {m_kmatrix = _kMatrix; }

private:
    vector<Robot*> m_robots;
    vector<LightSource*> m_lights;
    QParallelAnimationGroup* m_animations;
    int** m_kmatrix;

};

#endif // ROBOTMANAGER_H
