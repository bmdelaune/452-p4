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

    void setIntensity(double intensity) { m_intensity = intensity; }
    double getIntensity() { return m_intensity; }

    void setId(int id) { m_id = id; }
    int getId() { return m_id; }

signals:
    
public slots:
    
private:
    QPixmap m_pixmap;
    QPointF m_offset;
    double m_intensity;
    int m_id;

};

#endif // LIGHTSOURCE_H
