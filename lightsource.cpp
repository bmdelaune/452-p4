#include "lightsource.h"
#include "Utils.h"

#include <QObject>
#include <QPainter>
#include <QGraphicsSceneEvent>

LightSource::LightSource(QGraphicsItem *parent) :
    QGraphicsItem(parent)
{
}

QRectF LightSource::boundingRect() const
 {
     return QRectF(ROBOT_WIDTH/2, ROBOT_HEIGHT/2, ROBOT_WIDTH, ROBOT_HEIGHT);
 }

void LightSource::paint(QPainter *painter,
            const QStyleOptionGraphicsItem *option, QWidget *widget)
 {
     Q_UNUSED(option);
     Q_UNUSED(widget);
     if (m_pixmap.isNull()) {
         painter->setBrush(Qt::yellow);
         painter->drawEllipse(50, 50, LIGHT_SOURCE_RADIUS, LIGHT_SOURCE_RADIUS);
     } else {
         painter->scale(.2272, .2824);
         painter->drawPixmap(QPointF(-15 * 4.4, -50 * 3.54), m_pixmap);
     }
 }

void LightSource::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    m_offset = event->pos();
}

void LightSource::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton) {
            this->setPos(mapToParent(event->pos() - m_offset));
    }
}
