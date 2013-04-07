#ifndef ROBOTMANAGER_H
#define ROBOTMANAGER_H

#include <vector>
#include "robot.h"
#include "lightsource.h"

using namespace std;

class RobotManager
{
public:

    RobotManager();
    void addRobot(Robot* robot) { robot->setId(m_robots.size()); m_robots.push_back(robot); }

    void addLight(LightSource* light) { light->setId(m_lights.size()); m_lights.push_back(light); }
    double getIntensity(int id, Robot::Side side);
    void clear();

private:
    vector<Robot*> m_robots;
    vector<LightSource*> m_lights;
};

#endif // ROBOTMANAGER_H
