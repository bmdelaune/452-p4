#include "robot.h"
#include "Utils.h"
#include <math.h>

Robot::Robot(int id)
{
    m_id = id;
    m_leftWheel = new Wheel();
    m_rightWheel = new Wheel();
    m_theta = 0;
}

Robot::~Robot() {

}

QRectF Robot::boundingRect() const
{
    return QRectF(-ROBOT_WIDTH, 0, ROBOT_WIDTH*2, ROBOT_HEIGHT);
}



void Robot::paint(QPainter *painter,
            const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if (pixmap.isNull()) {
        painter->setBrush(Qt::transparent);
        painter->setPen(Qt::black);

        // qDebug() << "RobotPos" << this->pos();
        //double theta = PI/2 - asin((getWheel(LEFT)->getLoc().y()-getWheel(RIGHT)->getLoc().y())/ROBOT_WIDTH);
        //QPointF frontLeft = QPointF(getWheel(LEFT)->getLoc().x()+ROBOT_HEIGHT*cos(theta),(getWheel(LEFT)->getLoc().y()-ROBOT_HEIGHT*sin(theta)));
        //QPointF frontRight = QPointF(getWheel(RIGHT)->getLoc().x()+ROBOT_HEIGHT*cos(theta),(getWheel(RIGHT)->getLoc().y()-ROBOT_HEIGHT*sin(theta)));
        QPointF frontLeft = getSensorPos(LEFT);
        QPointF frontRight = getSensorPos(RIGHT);
        painter->drawRect(-ROBOT_WIDTH/2, 0, ROBOT_WIDTH, ROBOT_HEIGHT);
        painter->drawEllipse(-5 -ROBOT_WIDTH/2 , 0, 5, 10);
        painter->drawEllipse(ROBOT_WIDTH -ROBOT_WIDTH/2, 0, 5, 10);

        //this->setPos(QPointF(0, ROBOT_HEIGHT));
/*
        qDebug() << "fL("<<frontLeft.x()<<","<<frontLeft.y()<<")";
        qDebug() << "fR("<<frontRight.x()<<","<<frontRight.y()<<")";
        qDebug() << "bL("<<getWheel(LEFT)->getLoc().x()<<","<<getWheel(LEFT)->getLoc().y()<<")";
        qDebug() << "bR("<<getWheel(RIGHT)->getLoc().x()<<","<<getWheel(RIGHT)->getLoc().y()<<")";

        */
        //QPointF points[4] = {frontRight, frontLeft, getWheel(LEFT)->getLoc(), getWheel(RIGHT)->getLoc()};
        //painter->drawPolygon(points,4);

    } else {
        painter->scale(.2272, .2824);
        painter->drawPixmap(QPointF(-15 * 4.4, -50 * 3.54), pixmap);
    }
}

QPointF Robot::calculateNewPosition(double t)
{
    //The point in question is the location of the left wheel of the robot. This can be changed later

    // get current location values
    Wheel* leftWheel = getWheel(LEFT);
    Wheel* rightWheel = getWheel(RIGHT);

    /*double dot_product = xLocLeft * xLocRight + yLocLeft * yLocRight;
    double magLeft = sqrt(pow(xLocLeft,2)+pow(yLocLeft,2));
    double magRight = sqrt(pow(xLocRight,2)+pow(yLocRight,2));
    double theta = acos(dot_product / (magLeft * magRight));*/

    double velLeft = leftWheel->getVelocity();
    double velRight = rightWheel->getVelocity();
    double x = pos().x();
    double y = pos().y();
    double theta0 = m_theta * DEG_TO_RAD;

    double targetXLoc = 0;
    double targetYLoc = 0;

    double R = ROBOT_WIDTH/2.0 * (velLeft + velRight) / (velRight - velLeft);
    double angVel = (velRight - velLeft)/ROBOT_WIDTH;

    double iccX = x - R*sin(theta0);
    double iccY = y - R*cos(theta0);

    double coswt = cos(angVel*t);
    double sinwt = sin(angVel*t);

    double xp = (x-iccX)*coswt - (y-iccY)*sinwt + iccX - x;
    double yp = (x-iccX)*sinwt + (y-iccY)*coswt + iccY - y;
    double tp = theta0 + angVel*t;

    m_theta = tp * RAD_TO_DEG;
    /*
    double theta0 = m_theta * DEG_TO_RAD;
    double theta = (velRight - velLeft) * time / ROBOT_WIDTH + theta0;

    m_theta = theta * RAD_TO_DEG;
    targetXLoc += ROBOT_WIDTH*((velRight+velLeft)/(2*(velRight-velLeft)))*
                                (sin((velRight-velLeft)*time/ROBOT_WIDTH+ theta0)-sin(theta0));

    targetYLoc -= ROBOT_WIDTH*((velRight+velLeft)/(2*(velRight-velLeft)))*
                                (cos((velRight-velLeft)*time/ROBOT_WIDTH+theta0)-cos(theta0));

    */
    qDebug() << "velocities" << velLeft << velRight;
    qDebug() << "Pos:" << pos();
    qDebug() << "m_theta" << m_theta;
    qDebug() << QPointF(xp, yp);

    return QPointF(xp, yp);
}

QPointF Robot::getSensorPos(Robot::Side side)
{
    //qDebug() << "ROBOT: " << m_id;

    // theta is from 0 going up physically, while rotation goes the opposite
    double theta = -1*rotation();
    // Calculate the whole rectangle
    // #YOLO
    QPointF leftWheel = pos(); // left wheel is the pos() of the object
    QPointF rightWheel = QPointF(ROBOT_WIDTH * cos (theta*DEG_TO_RAD),
                                 ROBOT_WIDTH * sin (-1*theta * DEG_TO_RAD)) + leftWheel;

    QPointF leftSensor = QPointF(ROBOT_HEIGHT * sin (theta*DEG_TO_RAD),
                                 ROBOT_HEIGHT* cos (theta * DEG_TO_RAD)) + leftWheel;

    QPointF rightSensor = QPointF(ROBOT_HEIGHT * sin (theta*DEG_TO_RAD),
                                 ROBOT_HEIGHT* cos (theta * DEG_TO_RAD)) + rightWheel;

/*
    qDebug() << "left wheel: " << leftWheel << mapFromScene(leftWheel);
    qDebug() << "right wheel: " << rightWheel << mapFromScene(rightWheel);
    qDebug() << "left sensor: " << leftSensor;
    qDebug() << "right sensor: " << rightSensor;

    qDebug() << "fig rotation: " << rotation() ;
    qDebug() << "theta" << theta;
*/
    QPointF point = (side == LEFT) ? leftSensor : rightSensor;

    // qDebug() << "sensor: " << side << point << this->mapToScene(point) << "angle" << theta * RAD_TO_DEG;
    return point;
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
