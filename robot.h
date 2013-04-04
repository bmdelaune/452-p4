#ifndef ROBOT_H
#define ROBOT_H

#include <QGraphicsItem>
#include <QPainter>

class Robot : public QGraphicsItem
{
public:
    Robot(QGraphicsItem *parent = 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

private:
    QPixmap pixmap;

};

#endif // ROBOT_H
