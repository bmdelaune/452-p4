#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsScene>
#include <vector>
#include <QtAlgorithms>
#include "robotmanager.h"

class Canvas : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Canvas(QObject *parent = 0);
    void initialize();

signals:

public slots:
    void setup(int bots, int lights, QVector<QPointF> botLoc, QVector<QPointF> lightLoc, int **matrix);
    void clear();
    void move();

private:
    QVector<QPointF> defaultBotLoc(int num);
    QVector<QPointF> defaultLightLoc(int num);
    void createRobot(Robot* robot);
    void createLight(LightSource *light);

    QBrush blackBrush;
    QPen blackPen;
    QBrush paintBrush;
    QPen paintPen;

    int **kmatrix;
    RobotManager* m_robotManager;
};

#endif // CANVAS_H
