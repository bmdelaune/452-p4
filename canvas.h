#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsScene>
#include <vector>

class Canvas : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Canvas(QObject *parent = 0);
    void initialize();

signals:

public slots:


private:

    QBrush blackBrush;
    QPen blackPen;
    QBrush paintBrush;
    QPen paintPen;



};

#endif // CANVAS_H
