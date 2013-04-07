#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QListWidgetItem>
#include <QMouseEvent>
#include <QFileDialog>
#include "canvas.h"

namespace Ui {
    class MainWindow;
}

class mainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit mainWindow(QWidget *parent = 0);
    ~mainWindow();

public slots:
    void setup();
    void reset();
    void loadFromFile();
    
private:
    Ui::MainWindow *ui;
    Canvas* scene;
    QVector<QPointF> botLoc(QString posStr);
    QVector<QPointF> lightLoc(QString posStr);
    int **kMatrix(QString kStr);
    void parseFile(int &bots, int &lights, QVector<QPointF> &botPos, QVector<QPointF> &lightPos, int **matrix);

};

#endif // MAINWINDOW_H
