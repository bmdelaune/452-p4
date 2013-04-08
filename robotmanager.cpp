#include "robotmanager.h"
#include <math.h>
#include <Utils.h>


RobotManager::RobotManager()
{
}

// get intensity from sensor left/right
double RobotManager::getIntensity(int id, Robot::Side side)
{
    QPointF robotPos = m_robots[id]->getSensor(side)->loc;
    QPointF lightPos = m_lights[id]->pos();

    double diffX = robotPos.x() - lightPos.x();
    double diffY = robotPos.y() - lightPos.y();

    double distance = sqrt( diffX*diffX + diffY*diffY  );

    return distance;
}

void RobotManager::clear() {
    m_robots.clear();
    m_lights.clear();
}

void RobotManager::moveRobots(){
    int rw = ROBOT_WIDTH;
    for(int i = 0; i < m_robots.size(); i++){
        Robot* current = m_robots[i];
        double vR = current->getWheel(Robot::RIGHT)->getVelocity();
        double vL = current->getWheel(Robot::LEFT)->getVelocity();
        double r = ((vR*rw/2)-(vL*rw/2))/(vR-vL);
        double theta = sL/(r+rw/2);
        double xL = (r+rw/2)(1-cos(theta));
        double yL = (r+rw/2)(sin(theta));
        double xR = (r-rw/2)(1-cos(theta));
        double yR = (r-rw/2)(sin(theta));

    }
}
