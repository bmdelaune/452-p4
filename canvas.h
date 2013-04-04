#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsScene>
#include <vector>
#include "robotmanager.h"

class Canvas : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Canvas(QObject *parent = 0);
    void initialize();

signals:

public slots:


private:

    void createRobot(Robot* robot);

    QBrush blackBrush;
    QPen blackPen;
    QBrush paintBrush;
    QPen paintPen;


    RobotManager* m_robotManager;
};

#endif // CANVAS_H
