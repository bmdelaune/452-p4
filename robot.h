#ifndef ROBOT_H
#define ROBOT_H

#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
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
    //void setPos(QPointF pos);
    QPointF getSensorPos(Side side) { return sensorPos[side]; }
    Sensor *getSensor(Side side);
    Wheel* getWheel(Side side);
    void setTheta(double t);
    QPointF calculateNewPosition(Robot* robot, double time);
    QPointF calculateNewPositionRight(Robot* robot, double time);
    double theta, lastTheta;
    //QPointF rightWheelPrev, leftWheelPrev;
    bool trigger;
    QPointF sensorPos[2];
    //double lwpv;
    //double rwpv;

private:
    int m_id;
    QPixmap pixmap;
    Sensor* m_leftSensor;
    Sensor* m_rightSensor;

    Wheel* m_leftWheel;
    Wheel* m_rightWheel;
    bool initial;

    QPointF lastFL, lastFR;
};

#endif // ROBOT_H
