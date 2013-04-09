#include "robotmanager.h"
#include <math.h>
#include <Utils.h>
#include <QTimeLine>
#include <QPropertyAnimation>


RobotManager::RobotManager()
{
}

/*
 *  for each robot
 *      for each sensor
 *          get intensity == 'light / distance'
 *          get speed witk K matrix
 *
 *      set robot speed
 *
 */
// NOTE: w1 in the K-Matrix is left velocity
void RobotManager::updateVelocities()
{
    double velocityLeft;
    double velocityRight;
    for (int i=0; i<m_robots.size(); i++) {
        double leftIntensity = 0;
        double rightIntensity = 0;
        for (int s=0; s< m_lights.size(); s++) {

            leftIntensity += getIntensity(m_lights[s], m_robots[i], Robot::LEFT);
            rightIntensity += getIntensity(m_lights[s], m_robots[i], Robot::RIGHT);

        }

        velocityLeft = m_kmatrix[0][0] * leftIntensity + m_kmatrix[0][1] * rightIntensity;
        velocityRight = m_kmatrix[1][0] * leftIntensity + m_kmatrix[1][1] * rightIntensity;
        Robot* robot = m_robots[i];
        robot->getWheel(Robot::LEFT)->setVelocity(velocityLeft);
        robot->getWheel(Robot::RIGHT)->setVelocity(velocityRight);

    }

}

// get intensity from sensor left/right
double RobotManager::getIntensity(LightSource* light, Robot* robot, Robot::Side side)
{
    QPointF sensorPos = robot->mapToScene(robot->getSensorPos(side));
    // qDebug() << "Sensor Pos:" << sensorPos << robot->mapToScene(robot->getSensorPos(side));
    QPointF lightPos = light->pos();
    // qDebug() << "light Pos:" << lightPos << light->mapToScene(lightPos);

    double diffX = sensorPos.x() - lightPos.x();
    double diffY = sensorPos.y() - lightPos.y();

    double distance = sqrt( diffX*diffX + diffY*diffY  );

    return light->getIntensity() / distance ;
}

void RobotManager::clear() {
    m_robots.clear();
    m_lights.clear();
}

void RobotManager::moveRobots() {

    double offset = 50;
    m_animations = new QParallelAnimationGroup;
    QPropertyAnimation *posAnimation;
    QPropertyAnimation *rotAnimation;
    Robot* robot;
    for (int i=0; i<m_robots.size(); i++){
        robot = m_robots[i];

        posAnimation = new QPropertyAnimation(robot, "pos");
        rotAnimation = new QPropertyAnimation(robot, "rotation");

        posAnimation->setDuration(1000);
        posAnimation->setEasingCurve(QEasingCurve::Linear);
        QPointF offset = robot->calculateNewPosition(10);
        qDebug() << "Pos: " << robot->pos() << offset;

        posAnimation->setStartValue(robot->pos());
        posAnimation->setEndValue(robot->calculateNewPosition(10) + robot->pos());
        qDebug() << "Angle: " << robot->rotation() << robot->getTheta();
        rotAnimation->setDuration(1000);
        rotAnimation->setEasingCurve(QEasingCurve::Linear);
        rotAnimation->setStartValue(robot->rotation());
        rotAnimation->setEndValue( robot->getTheta());

        m_animations->addAnimation(posAnimation);
        m_animations->addAnimation(rotAnimation);

    }

    m_animations->start();
    /* int rw = ROBOT_WIDTH;
    for(int i = 0; i < m_robots.size(); i++){
        Robot* current = m_robots[i];
        double velRight = current->getWheel(Robot::RIGHT)->getVelocity();
        double velLeft = current->getWheel(Robot::LEFT)->getVelocity();
        double radius = ((velRight*rw/2)-(velLeft*rw/2))/(velRight-velLeft);
        double theta = velLeft/(radius+rw/2);
        double xL = (radius+rw/2)*(1-cos(theta));
        double yL = (radius+rw/2)*(sin(theta));
        double xR = (radius-rw/2)*(1-cos(theta));
        double yR = (radius-rw/2)*(sin(theta));
        current->getWheel(Robot::LEFT)->setLoc(
                    QPointF(current->getWheel(Robot::LEFT)->getLoc().x()+xL,
                            current->getWheel(Robot::LEFT)->getLoc().y()+yL));
        current->getWheel(Robot::RIGHT)->setLoc(
                    QPointF(current->getWheel(Robot::RIGHT)->getLoc().x()+xR,
                            current->getWheel(Robot::RIGHT)->getLoc().y()+yR));
        current->update(current->sceneBoundingRect());
    }*/
}
