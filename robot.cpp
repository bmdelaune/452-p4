#include "robot.h"
#include "Utils.h"
#include <math.h>

Robot::Robot(QGraphicsItem *parent)
     : QGraphicsItem(parent)
{
    m_leftWheel = new Wheel();
    m_rightWheel = new Wheel();
    theta = 0;
    initial = true;
    trigger = false;
}

QRectF Robot::boundingRect() const
{

    //return QRectF(x(), y(), ROBOT_WIDTH, ROBOT_HEIGHT);
    return QRectF(-50,-50,850,650);
}

void Robot::paint(QPainter *painter,
            const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPointF frontLeft, frontRight;
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if (pixmap.isNull()) {
        painter->setBrush(Qt::transparent);
        painter->setPen(Qt::black);

       // theta = PI/2 - asin((getWheel(LEFT)->getLoc().y()-getWheel(RIGHT)->getLoc().y())/ROBOT_WIDTH);
       // qDebug() << "TAKING ASIN" << getWheel(LEFT)->getLoc().y()-getWheel(RIGHT)->getLoc().y();
        if (isnan(theta))
        {
            qDebug() << "UH OH THETA DIED";
            theta = lastTheta;
        }
        if (initial)
        {
            getWheel(LEFT)->setLoc(QPointF(pos().x(), pos().y() + ROBOT_HEIGHT));
            getWheel(RIGHT)->setLoc(QPointF(pos().x() + ROBOT_WIDTH, pos().y() + ROBOT_HEIGHT));
            frontLeft = sensorPos[LEFT] = pos();
            frontRight = sensorPos[RIGHT] = QPointF(pos().x() + ROBOT_WIDTH, pos().y());
            lastFL = frontLeft;
            lastFR = frontRight;
            lastTheta = 0;
            initial = false;
            qDebug() << "pos" << pos();
        }
        else if (trigger)
        {
            //getWheel(LEFT)->setLoc(calculateNewPosition(this, 10));
            //getWheel(RIGHT)->setLoc(QPointF(ROBOT_WIDTH * cos(theta), ROBOT_WIDTH * sin(theta)));
            float diffX = getWheel(LEFT)->getLoc().x() - getWheel(RIGHT)->getLoc().x();
            float diffY = getWheel(LEFT)->getLoc().y() - getWheel(RIGHT)->getLoc().y();
            float newslope = -1 * (diffX/diffY);
            float phi = atan(newslope);
            float newy = ROBOT_HEIGHT * sin(phi);
            float newx = ROBOT_HEIGHT * cos(phi);
            //qDebug() << "diffx" << diffX << "diffy" << diffY;
            //qDebug() << "newx" << newx << "newy" << newy;
            if (getWheel(Robot::LEFT)->getVelocity() > getWheel(Robot::RIGHT)->getVelocity())
            {
                //qDebug() << "Turning right." << newslope;
                frontLeft = QPointF(getWheel(LEFT)->getLoc().x() - newx, getWheel(LEFT)->getLoc().y() - newy);
                frontRight = QPointF(getWheel(RIGHT)->getLoc().x() - newx, getWheel(RIGHT)->getLoc().y() - newy);
            }
            else if (getWheel(Robot::LEFT)->getVelocity() < getWheel(Robot::RIGHT)->getVelocity())
            {
                //qDebug() << "Turning left.";
                frontLeft = QPointF(getWheel(LEFT)->getLoc().x() - newx, getWheel(LEFT)->getLoc().y() - newy);
                frontRight = QPointF(getWheel(RIGHT)->getLoc().x() - newx, getWheel(RIGHT)->getLoc().y() - newy);
            }
            sensorPos[LEFT] = frontLeft;
            sensorPos[RIGHT] = frontRight;
            lastFR = frontRight;
            lastFL = frontLeft;
            lastTheta = theta;
            trigger = false;
        }
        else
        {
            frontRight = lastFR;
            frontLeft = lastFL;
            theta = lastTheta;
        }
        qDebug() << " ";
        qDebug() << "LS" << sensorPos[LEFT];
        qDebug() << "RS" << sensorPos[RIGHT];
        qDebug() << "fL("<<frontLeft.x()<<","<<frontLeft.y()<<")";
        qDebug() << "fR("<<frontRight.x()<<","<<frontRight.y()<<")";
        qDebug() << "bL("<<getWheel(LEFT)->getLoc().x()<<","<<getWheel(LEFT)->getLoc().y()<<")";
        qDebug() << "bR("<<getWheel(RIGHT)->getLoc().x()<<","<<getWheel(RIGHT)->getLoc().y()<<")";
        qDebug() << " ";

        QPointF points[4] = {frontRight, frontLeft, getWheel(LEFT)->getLoc(), getWheel(RIGHT)->getLoc()};
        painter->drawPolygon(points,4);

    } else {
        painter->scale(.2272, .2824);
        painter->drawPixmap(QPointF(-15 * 4.4, -50 * 3.54), pixmap);
    }
}

QPointF Robot::calculateNewPosition(Robot* robot, double time)
{
    //The point in question is the location of the left wheel of the robot. This can be changed later

    // get current location values
    Wheel* leftWheel = getWheel(LEFT);
    Wheel* rightWheel = getWheel(RIGHT);
    double xLocLeft = leftWheel->getLoc().x();
    double yLocLeft = leftWheel->getLoc().y();
    double xLocRight = rightWheel->getLoc().x();
    double yLocRight = rightWheel->getLoc().y();
    double velLeft = leftWheel->getVelocity();
    double velRight = rightWheel->getVelocity();
    double targetXLoc = xLocLeft;
    double targetYLoc = yLocLeft;
    theta = (velLeft - velRight) * time / ROBOT_WIDTH + lastTheta;
    qDebug() << "vl" << velLeft << "vr" << velRight << "time" << time << "lT" << lastTheta;

    if (velRight == velLeft){
        qDebug() << "GO STRAIGHT";
    }
    else {
        targetXLoc += ROBOT_WIDTH*((velRight+velLeft)/(2*(velRight-velLeft)))*(sin((velRight-velLeft)*time/ROBOT_WIDTH+theta)-sin(theta));
        targetYLoc += ROBOT_WIDTH*((velRight+velLeft)/(2*(velRight-velLeft)))*(cos((velRight-velLeft)*time/ROBOT_WIDTH+theta)-cos(theta));
    }

    return QPointF(targetXLoc, targetYLoc);
}
/*
QPointF Robot::calculateNewPositionRight(Robot* robot, double time)
{
    //The point in question is the location of the left wheel of the robot. This can be changed later

    // get current location values
    QPointF leftWheel = leftWheelPrev;
    QPointF rightWheel = rightWheelPrev;
    double xLocLeft = leftWheel.x();
    double yLocLeft = leftWheel.y();
    double xLocRight = rightWheel.x();
    double yLocRight = rightWheel.y();
    /*double dot_product = xLocLeft * xLocRight + yLocLeft * yLocRight;
    double magLeft = sqrt(pow(xLocLeft,2)+pow(yLocLeft,2));
    double magRight = sqrt(pow(xLocRight,2)+pow(yLocRight,2));
    double theta = acos(dot_product / (magLeft * magRight));

    double velLeft = lwpv;
    double velRight = rwpv;
    double targetXLoc = xLocRight;
    double targetYLoc = yLocRight;
    double localtheta = lastTheta;
    //theta = (velLeft - velRight) * time / ROBOT_WIDTH + lastTheta;
    qDebug() << "vl" << velLeft << "vr" << velRight << "time" << time << "lT" << lastTheta;

    if (velRight == velLeft){
        qDebug() << "GO STRAIGHT";
    }
    else {
        targetXLoc += ROBOT_WIDTH*((velRight+velLeft)/(2*(velRight-velLeft)))*(sin((velRight-velLeft)*time/ROBOT_WIDTH+localtheta)-sin(localtheta));
        targetYLoc += ROBOT_WIDTH*((velRight+velLeft)/(2*(velRight-velLeft)))*(cos((velRight-velLeft)*time/ROBOT_WIDTH+localtheta)-cos(localtheta));
    }

    return QPointF(targetXLoc, targetYLoc);
}*/

void Robot::setTheta(double t)
{
    theta = t;
}

/*QPointF Robot::getSensorPos(Robot::Side side)
{

    //double theta = PI/2 - asin((getWheel(LEFT)->getLoc().y()-getWheel(RIGHT)->getLoc().y())/ROBOT_WIDTH);
    //return QPointF(getWheel(side)->getLoc().x()+ROBOT_HEIGHT*cos(theta), getWheel(side)->getLoc().y()-ROBOT_HEIGHT*sin(theta));
}*/

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
