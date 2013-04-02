#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QListWidgetItem>
#include <QMouseEvent>
#include "canvas.h"
#include "network.h"

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
    void on_axisList_itemClicked(QListWidgetItem *item);
    void disableButtons();
    
private:
    Ui::MainWindow *ui;
    Canvas* scene;
    Connector *c;
};

#endif // MAINWINDOW_H
