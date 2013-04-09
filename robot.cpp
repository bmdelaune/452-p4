#include "robot.h"
#include "Utils.h"
#include <math.h>

Robot::Robot(QGraphicsItem *parent)
     : QGraphicsItem(parent)
{
    m_leftWheel = new Wheel();
    m_rightWheel = new Wheel();
}

QRectF Robot::boundingRect() const
{
    return QRectF(ROBOT_WIDTH/2, ROBOT_HEIGHT/2, ROBOT_WIDTH, ROBOT_HEIGHT);
}



void Robot::paint(QPainter *painter,
            const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if (pixmap.isNull()) {
        painter->setBrush(Qt::transparent);
        painter->setPen(Qt::black);
        //painter->drawRect(x, y, ROBOT_WIDTH, ROBOT_HEIGHT);
        double theta = PI/2 - asin((getWheel(LEFT)->getLoc().y()-getWheel(RIGHT)->getLoc().y())/ROBOT_WIDTH);
        //QPointF frontLeft = QPointF(getWheel(LEFT)->getLoc().x()+ROBOT_HEIGHT*cos(theta),(getWheel(LEFT)->getLoc().y()-ROBOT_HEIGHT*sin(theta)));
        //QPointF frontRight = QPointF(getWheel(RIGHT)->getLoc().x()+ROBOT_HEIGHT*cos(theta),(getWheel(RIGHT)->getLoc().y()-ROBOT_HEIGHT*sin(theta)));
        QPointF frontLeft = getSensorPos(LEFT);
        QPointF frontRight = getSensorPos(RIGHT);

/*
        qDebug() << "fL("<<frontLeft.x()<<","<<frontLeft.y()<<")";
        qDebug() << "fR("<<frontRight.x()<<","<<frontRight.y()<<")";
        qDebug() << "bL("<<getWheel(LEFT)->getLoc().x()<<","<<getWheel(LEFT)->getLoc().y()<<")";
        qDebug() << "bR("<<getWheel(RIGHT)->getLoc().x()<<","<<getWheel(RIGHT)->getLoc().y()<<")";

        */
        QPointF points[4] = {frontRight, frontLeft, getWheel(LEFT)->getLoc(), getWheel(RIGHT)->getLoc()};
        painter->drawPolygon(points,4);

    } else {
        painter->scale(.2272, .2824);
        painter->drawPixmap(QPointF(-15 * 4.4, -50 * 3.54), pixmap);
    }
}

void Robot::setPos(QPointF pos)
{
    qDebug() << "("<<pos.x()<<","<<pos.y()<<")";
    getWheel(LEFT)->setLoc(QPointF(pos.x()-ROBOT_WIDTH/2,pos.y()+ROBOT_HEIGHT/2));
    getWheel(RIGHT)->setLoc(QPointF(pos.x()+ROBOT_WIDTH/2,pos.y()+ROBOT_HEIGHT/2));
}

/*QPointF Robot::calculateNewPosition(Robot* robot, double time)
{
    //The point in question is the location of the left wheel of the robot. This can be changed later

    // get current location values
    Wheel leftWheel = robot->getWheel(LEFT);
    Wheel rightWheel = robot->getWheel(RIGHT);
    double xLocLeft = leftWheel->getLoc.x();
    double yLocLeft = leftWheel->getLoc.y();
    double xLocRight= rightWheel->getLoc.x();
    double yLocRight = rightWheel->getLoc.y();
    double dot_product = xLocLeft * xLocRight + yLocLeft * yLocRight;
    double magLeft = sqrt(pow(xLocLeft,2)+pow(yLocLeft,2));
    double magRight = sqrt(pow(xLocRight,2)+pow(yLocRight,2));
    double theta = acos(dot_product / (magLeft * magRight));
    double velLeft = leftWheel->getVelocity();
    double velRight = rightWheel->getVelocity();
    double targetXLoc = xLocLeft;
    double targetYLoc = yLocLeft;

    targetXLoc += ROBOT_WIDTH*((velRight+velLeft)/(2*(velRight-velLeft)))*(sin((velRight-velLeft)*time/ROBOT_WIDTH+theta)-sin(theta));
    targetYLoc += ROBOT_WIDTH*((velRight+velLeft)/(2*(velRight-velLeft)))*(cos((velRight-velLeft)*time/ROBOT_WIDTH+theta)-cos(theta));

    return QPointF(targetXLoc, targetYLoc);
}
*/
QPointF Robot::getSensorPos(Robot::Side side)
{
    double theta = PI/2 - asin((getWheel(LEFT)->getLoc().y()-getWheel(RIGHT)->getLoc().y())/ROBOT_WIDTH);
    return QPointF(getWheel(side)->getLoc().x()+ROBOT_HEIGHT*cos(theta), getWheel(side)->getLoc().y()-ROBOT_HEIGHT*sin(theta));
}

Sensor* Robot::getSensor(Robot::Side side)
{
    if (side == LEFT)
        return m_leftSensor;
    else
        return m_rightSensor;
}

Wheel* Robot::getWheel(Robot::Side side)
{
    if (side == LEFT)
        return m_leftWheel;
    else
        return m_rightWheel;
}
