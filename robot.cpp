#include "robot.h"
#include "Utils.h"

Robot::Robot(QGraphicsItem *parent)
     : QGraphicsItem(parent)
 {

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
         painter->drawRect(x, y, ROBOT_WIDTH, ROBOT_HEIGHT);

     } else {
         painter->scale(.2272, .2824);
         painter->drawPixmap(QPointF(-15 * 4.4, -50 * 3.54), pixmap);
     }
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
