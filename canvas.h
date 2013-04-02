#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsScene>
#include "Link.h"
#include <vector>

class Canvas : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Canvas(QObject *parent = 0);
    void initialize();
    void updateLinks();
signals:
    void sendMsg(int command, int axis);
public slots:
    void rotateCW();
    void rotateCCW();

    void addX();
    void subX();
    void addY();
    void subY();

    void paintClicked();
    void changeColor();
    void changeSize(int newSize);

    void worldMove();

    //sets the 'newX' or 'newY' variable, the desired end effector coordinate value
    void setX(double);
    void setY(double);

private:

    QBrush blackBrush;
    QPen blackPen;
    QBrush paintBrush;
    QPen paintPen;

    Link* rootLink;
    std::vector<Link*> links;

    //keeps track of the current end effector location
    double x;
    double y;

    //keeps track of the desired end effector location
    double newX;
    double newY;

    //returns the value of the respective end effector coordinate
    double calcX();
    double calcY();

    bool paintToggle;
    int brushSize;

    void paint();

};

#endif // CANVAS_H
