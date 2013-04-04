#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <QGraphicsItem>
#include <QPointF>

class LightSource : public QGraphicsItem
{

public:
    explicit LightSource(QGraphicsItem *parent = 0);
    

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

signals:
    
public slots:
    
private:
    QPixmap m_pixmap;
    QPointF m_offset;
};

#endif // LIGHTSOURCE_H
