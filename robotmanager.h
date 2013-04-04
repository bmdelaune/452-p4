#ifndef ROBOTMANAGER_H
#define ROBOTMANAGER_H

#include <vector>
#include "robot.h"


using namespace std;

class RobotManager
{
public:
    RobotManager();
    void addRobot(Robot* robot) { m_robots.push_back(robot); }


private:
    vector<Robot*> m_robots;
};

#endif // ROBOTMANAGER_H
