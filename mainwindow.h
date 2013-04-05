#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QListWidgetItem>
#include <QMouseEvent>
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
    
private:
    Ui::MainWindow *ui;
    Canvas* scene;
    QVector<QPointF> locations();

};

#endif // MAINWINDOW_H
