#ifndef ROBOTMANAGER_H
#define ROBOTMANAGER_H

#include <vector>
#include "robot.h"
#include "lightsource.h"
#include <QParallelAnimationGroup>
#include <QObject>

using namespace std;

class Canvas;

class RobotManager : public QObject
{
    Q_OBJECT

signals:

public slots:
    void startAnimation();
public:
    explicit RobotManager (QObject *parent = 0);
    ~RobotManager();
    void addRobot(Robot* robot) { robot->setId(m_robots.size()); m_robots.push_back(robot); }

    void addLight(LightSource* light) { light->setId(m_lights.size()); m_lights.push_back(light); }
    void updateVelocities();
    double getIntensity(LightSource *light, Robot *robot, Robot::Side side);
    void clear();
    void moveRobots();
    void setKMatrix(int** _kMatrix) {m_kmatrix = _kMatrix; }
    void setCanvas(Canvas* canvas) { m_canvas = canvas; }
private:
    vector<Robot*> m_robots;
    vector<LightSource*> m_lights;
    QParallelAnimationGroup* m_animations;
    int** m_kmatrix;
    Canvas* m_canvas;

};

#endif // ROBOTMANAGER_H
