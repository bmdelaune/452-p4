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
    c = new Connector(this);
    c->setup(ui->netStatus, ui->ipEdit, ui->modeBtn, ui->delayBtn, scene);
    disableButtons();

    QRectF rect = ui->graphicsView->rect();

    rect.setX(-(rect.width()-10)/2);
    rect.setWidth(ui->graphicsView->width()-5);
    rect.setHeight(ui->graphicsView->height()-5);
    scene->setSceneRect(rect);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setMouseTracking(true);
    scene->initialize();

    ui->graphicsView->rotate(180);

    connect(ui->cwiseBtn, SIGNAL(clicked()), scene, SLOT(rotateCW()));
    connect(ui->ccwiseBtn, SIGNAL(clicked()), scene, SLOT(rotateCCW()));
    connect(ui->xPlus, SIGNAL(clicked()), scene, SLOT(addX()));
    connect(ui->xMinus, SIGNAL(clicked()), scene, SLOT(subX()));
    connect(ui->yPlus, SIGNAL(clicked()), scene, SLOT(addY()));
    connect(ui->yMinus, SIGNAL(clicked()), scene, SLOT(subY()));
    connect(ui->paintBtn, SIGNAL(clicked()), scene, SLOT(paintClicked()));
    //connect(ui->brushColor, SIGNAL(clicked()), scene, SLOT(changeColor()));
    //connect(ui->brushSlider, SIGNAL(valueChanged(int)), scene, SLOT(changeSize(int)));
    connect(ui->connectClient, SIGNAL(clicked()), c, SLOT(cconnect()));
    connect(ui->modeBtn, SIGNAL(clicked()), c, SLOT(changeMode()));
    connect(ui->modeBtn, SIGNAL(clicked()), this, SLOT(disableButtons()));
    connect(c, SIGNAL(enableButtons()), this, SLOT(disableButtons()));
    connect(scene, SIGNAL(sendMsg(int,int)), c, SLOT(sendCommand(int, int)));
    connect(ui->delayBtn, SIGNAL(clicked()), c, SLOT(changeDelay()));
}

void mainWindow::disableButtons() {
    if (!c->client || !c->connected)
    {
        ui->axisList->setEnabled(false);
        ui->cwiseBtn->setEnabled(false);
        ui->ccwiseBtn->setEnabled(false);
        ui->xPlus->setEnabled(false);
        ui->xMinus->setEnabled(false);
        ui->yPlus->setEnabled(false);
        ui->yMinus->setEnabled(false);
        ui->paintBtn->setEnabled(false);    
    }
    else if (!c->client && c->connected)
    {
        ui->ipEdit->setEnabled(false);
        ui->connectClient->setEnabled(false);
        ui->paintBtn->setEnabled(false);
        ui->delayBtn->setEnabled(true);
       //ui->brushSlider->setEnabled(false);
        //ui->brushColor->setEnabled(false);
    }
    else
    {
        ui->axisList->setEnabled(true);
        ui->cwiseBtn->setEnabled(true);
        ui->ccwiseBtn->setEnabled(true);
        ui->xPlus->setEnabled(true);
        ui->xMinus->setEnabled(true);
        ui->yPlus->setEnabled(true);
        ui->yMinus->setEnabled(true);
        ui->paintBtn->setEnabled(true);
        ui->delayBtn->setEnabled(false);
        //ui->brushSlider->setEnabled(true);
        //ui->brushColor->setEnabled(true);
    }
}

/*void mainWindow::dragMoveEvent(QDragMoveEvent * e)
{
    //e->acceptProposedAction();
    QPointF pt = ui->graphicsView->mapToScene(e->pos());
    scene->setX(pt.x()+10);
    scene->setY(pt.y()+25);
    qDebug() <<"x: "<<pt.x();
    qDebug() <<"y: "<<pt.y();
    scene->worldMove();
}*/

void mainWindow::on_axisList_itemClicked(QListWidgetItem *item)
{
    QString qstr_axis_number =0;
    qstr_axis_number = item->text();
    axis_number = qstr_axis_number.toInt();
    qDebug()<<"axis number clicked: "<<axis_number<<endl;
}

mainWindow::~mainWindow()
{
    delete ui;
}
