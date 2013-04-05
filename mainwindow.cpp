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

    //rect.setX(-rect.width()/2);
    //rect.setX(-(rect.width()-10)/2);
    //rect.setWidth(ui->graphicsView->width()-5);
    //rect.setHeight(ui->graphicsView->height()-5);
    scene->setSceneRect(rect);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setMouseTracking(true);
    scene->initialize();

    //ui->graphicsView->rotate(180);

    connect(ui->setBtn, SIGNAL(clicked()), this, SLOT(setup()));
    connect(ui->resetBtn, SIGNAL(clicked()), this, SLOT(reset()));

}

mainWindow::~mainWindow()
{
    delete ui;
}

QVector<QPointF> mainWindow::botLoc() {
    QVector <QPointF> vec;
    QString posStr = ui->botPos->toPlainText();
    QStringList list = posStr.split(QRegExp("\\s"));
    qreal x, y;
    for (int i = 0; i < list.size(); i++)
    {
        if (i % 2 == 0)
            x = list[i].toInt();
        else
        {
            y = list[i].toInt();
            QPointF point = QPointF(x, y);
            vec.push_back(point);
        }
    }
    for (int i = 0; i < vec.size(); i++)
    {
        qDebug() << "Point " << i << " = (" << vec[i].x() << ", " << vec[i].y() << ")";
    }
    return vec;
}

QVector<QPointF> mainWindow::lightLoc() {
    QVector <QPointF> vec;
    QString posStr = ui->lightPos->toPlainText();
    QStringList list = posStr.split(QRegExp("\\s"));
    qreal x, y;
    for (int i = 0; i < list.size(); i++)
    {
        if (i % 2 == 0)
            x = list[i].toInt();
        else
        {
            y = list[i].toInt();
            QPointF point = QPointF(x, y);
            vec.push_back(point);
        }
    }
    for (int i = 0; i < vec.size(); i++)
    {
        qDebug() << "Point " << i << " = (" << vec[i].x() << ", " << vec[i].y() << ")";
    }
    return vec;
}

void mainWindow::setup() {
    int bots = ui->numBots->text().toInt();
    int lights = ui->numLights->text().toInt();
    QVector<QPointF> botPos = botLoc();
    QVector<QPointF> lightPos = lightLoc();
    scene->setup(bots, lights, botPos, lightPos);
    ui->numBots->setEnabled(false);
    ui->numLights->setEnabled(false);
    ui->kMatrix->setEnabled(false);
    ui->botPos->setEnabled(false);
    ui->lightPos->setEnabled(false);
    ui->setBtn->setEnabled(false);
    ui->loadFile->setEnabled(false);
}

void mainWindow::reset() {
    ui->numBots->setEnabled(true);
    ui->numLights->setEnabled(true);
    ui->kMatrix->setEnabled(true);
    ui->botPos->setEnabled(true);
    ui->lightPos->setEnabled(true);
    ui->setBtn->setEnabled(true);
    ui->loadFile->setEnabled(true);
}
