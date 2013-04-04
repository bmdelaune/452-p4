#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QString>
#include <QPointF>
#include <QGraphicsView>
#include "mainwindow.h"

extern int axis_number;

mainWindow::mainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new Canvas(this);

    QRectF rect = ui->graphicsView->rect();

    rect.setX(-(rect.width()-10)/2);
    rect.setWidth(ui->graphicsView->width()-5);
    rect.setHeight(ui->graphicsView->height()-5);
    scene->setSceneRect(rect);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setMouseTracking(true);
    scene->initialize();

    ui->graphicsView->rotate(180);

    connect(ui->setBtn, SIGNAL(clicked()), this, SLOT(setup()));
    connect(ui->resetBtn, SIGNAL(clicked()), this, SLOT(reset()));

}

mainWindow::~mainWindow()
{
    delete ui;
}

void mainWindow::setup() {
    ui->numBots->setEnabled(false);
    ui->kMatrix->setEnabled(false);
    ui->initPos->setEnabled(false);
    ui->setBtn->setEnabled(false);
    ui->loadFile->setEnabled(false);
}

void mainWindow::reset() {
    ui->numBots->setEnabled(true);
    ui->kMatrix->setEnabled(true);
    ui->initPos->setEnabled(true);
    ui->setBtn->setEnabled(true);
    ui->loadFile->setEnabled(true);
}
