#ifndef ROBOT_H
#define ROBOT_H

#include <QGraphicsItem>
#include <QPainter>
#include "sensor.h"
#include "wheel.h"

class Robot : public QGraphicsItem
{
public:

    enum Side { RIGHT, LEFT };
    Robot(QGraphicsItem *parent = 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    void setId(int id) { m_id = id; }
    int getId() { return m_id; }

    Sensor *getSensor(Side side);
    Wheel* getWheel(Side side);

private:

    int m_id;

    QPixmap pixmap;
    Sensor* m_leftSensor;
    Sensor* m_rightSensor;

    Wheel* m_leftWheel;
    Wheel* m_rightWheel;

};

#endif // ROBOT_H
