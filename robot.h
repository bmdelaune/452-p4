#ifndef ROBOT_H
#define ROBOT_H

#include <QGraphicsItem>
#include <QGraphicsWidget>
#include <QPainter>
#include <QDebug>
#include "sensor.h"
#include "wheel.h"

class Robot : public QGraphicsWidget
{
public:
    enum Side { LEFT, RIGHT };
    Robot(int id);
    ~Robot();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    void setId(int id) { m_id = id; }
    int getId() { return m_id; }
    //void setPos(QPointF pos);
    QPointF getSensorPos(Side side);
    Sensor *getSensor(Side side);
    double getTheta() { return m_theta; }
    Wheel* getWheel(Side side);
    QPointF calculateNewPosition(double time);
    void setPos(const QPointF &pos);

private:
    int m_id;
    QPixmap pixmap;
    Sensor* m_leftSensor;
    Sensor* m_rightSensor;
    double m_theta;
    Wheel* m_leftWheel;
    Wheel* m_rightWheel;
};

#endif // ROBOT_H
