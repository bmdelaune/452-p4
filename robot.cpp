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

         painter->drawRect(ROBOT_WIDTH/2, ROBOT_HEIGHT/2, ROBOT_WIDTH, ROBOT_HEIGHT);
     } else {
         painter->scale(.2272, .2824);
         painter->drawPixmap(QPointF(-15 * 4.4, -50 * 3.54), pixmap);
     }
 }
