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
    void addRobot(Robot* robot) { m_robots.push_back(robot); }

    void setLightSource(LightSource* lightSource) { m_lightSource = lightSource; }
private:
    vector<Robot*> m_robots;
    LightSource* m_lightSource;
};

#endif // ROBOTMANAGER_H
