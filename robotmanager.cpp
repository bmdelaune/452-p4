#include "robotmanager.h"
#include <math.h>


RobotManager::RobotManager()
{
}

// get intensity from sensor left/right
double RobotManager::getIntensity(int id, Robot::Side side)
{
    QPointF robotPos = m_robots[id]->getSensor(side);
    QPointF lightPos = m_lightSource->pos();

    double diffX = robotPos.x() - lightPos.x();
    double diffY = robotPos.y() - lightPos.y();

    double distance = sqrt( diffX*diffX + diffY*diffY  );

    return distance;
}
