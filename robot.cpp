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
        qreal x = this->pos().x() - ROBOT_WIDTH/2;
        qreal y = this->pos().y() - ROBOT_HEIGHT/2;
        qDebug() << "TOP LEFT:" << x << "," << y;
        //painter->drawRect(x, y, ROBOT_WIDTH, ROBOT_HEIGHT);
        double theta = PI/2 - asin((getWheel(LEFT)->getLoc().y()-getWheel(RIGHT)->getLoc().y())/ROBOT_WIDTH);
        QPointF frontLeft = QPointF(getWheel(LEFT)->getLoc().x()+ROBOT_HEIGHT*cos(theta),(getWheel(LEFT)->getLoc().y()+ROBOT_HEIGHT*sin(theta)));
        QPointF frontRight = QPointF(getWheel(RIGHT)->getLoc().x()+ROBOT_HEIGHT*cos(theta),(getWheel(RIGHT)->getLoc().y()+ROBOT_HEIGHT*sin(theta)));
        QPointF points[4] = {getWheel(LEFT)->getLoc(),
                                          frontLeft,
                                          frontRight,
                                          getWheel(RIGHT)->getLoc()
        };
        painter->drawPolygon(points,4);
    } else {
        painter->scale(.2272, .2824);
        painter->drawPixmap(QPointF(-15 * 4.4, -50 * 3.54), pixmap);
    }
}

void Robot::setPos(QPointF pos)
{
    qDebug() << "("<<pos.x()<<","<<pos.y()<<")";
    getWheel(LEFT)->setLoc(QPointF(pos.x()-ROBOT_WIDTH/2,pos.y()-ROBOT_HEIGHT/2));
    getWheel(RIGHT)->setLoc(QPointF(pos.x()+ROBOT_WIDTH/2,pos.y()+ROBOT_HEIGHT/2));
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
