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

    scene->setSceneRect(rect);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setMouseTracking(true);
    scene->initialize();

    connect(ui->setBtn, SIGNAL(clicked()), this, SLOT(setup()));
    connect(ui->resetBtn, SIGNAL(clicked()), this, SLOT(reset()));
    connect(ui->loadFile, SIGNAL(clicked()), this, SLOT(loadFromFile()));
}

mainWindow::~mainWindow()
{
    delete ui;
}

QVector<QPointF> mainWindow::botLoc(QString posStr) {
    QVector <QPointF> vec;
    //QString posStr = ui->botPos->toPlainText();
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

QVector<QPointF> mainWindow::lightLoc(QString posStr) {
    QVector <QPointF> vec;
   // QString posStr = ui->lightPos->toPlainText();
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
int **mainWindow::kMatrix(QString kStr) {
    int *matrix[2];
    matrix[0] = new int[2];
    matrix[1] = new int[2];
   // QString kStr = ui->kMatrix->toPlainText();
    QStringList list = kStr.split(QRegExp("\\s"));
    if (list.size() != 4)
    {
        qDebug() << "ERROR: Invalid matrix. Using the default (go towards the light).";
        matrix[0][0] = 0;
        matrix[0][1] = 1;
        matrix[1][0] = 1;
        matrix[1][1] = 0;
    }
    else
    {
        matrix[0][0] = list[0].toInt();
        matrix[0][1] = list[1].toInt();
        matrix[1][0] = list[2].toInt();
        matrix[1][1] = list[3].toInt();
    }
    qDebug() << "K MATRIX:";
    qDebug() << "[" << matrix[0][0] << matrix[0][1];
    qDebug() << " " << matrix[1][0] << matrix[1][1] << "]";
    return matrix;
}

void mainWindow::parseFile(int &bots, int &lights, QVector<QPointF> &botPos, QVector<QPointF> &lightPos, int **matrix) {
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File..."), "C:\\", tr("Files (*.*)"));
}

void mainWindow::setup() {
    int bots = ui->numBots->text().toInt();
    int lights = ui->numLights->text().toInt();
    scene->setup(bots, lights, botLoc(ui->botPos->toPlainText()),
                 lightLoc(ui->lightPos->toPlainText()), kMatrix(ui->kMatrix->toPlainText()));
    ui->numBots->setEnabled(false);
    ui->numLights->setEnabled(false);
    ui->kMatrix->setEnabled(false);
    ui->botPos->setEnabled(false);
    ui->lightPos->setEnabled(false);
    ui->setBtn->setEnabled(false);
    ui->loadFile->setEnabled(false);
}

void mainWindow::reset() {
    scene->clear();
    ui->numBots->setEnabled(true);
    ui->numLights->setEnabled(true);
    ui->kMatrix->setEnabled(true);
    ui->botPos->setEnabled(true);
    ui->lightPos->setEnabled(true);
    ui->setBtn->setEnabled(true);
    ui->loadFile->setEnabled(true);
}

void mainWindow::loadFromFile() {
    int bots , lights;
    QVector<QPointF> botPos, lightPos;
    int **kmatrix;
    parseFile(bots, lights, botPos, lightPos, kmatrix);
    //scene->setup(bots, lights, botLoc(ui->botPos->toPlainText()),
     //            lightLoc(ui->lightPos->toPlainText()), kMatrix(ui->kMatrix->toPlainText()));
    ui->numBots->setEnabled(false);
    ui->numLights->setEnabled(false);
    ui->kMatrix->setEnabled(false);
    ui->botPos->setEnabled(false);
    ui->lightPos->setEnabled(false);
    ui->setBtn->setEnabled(false);
    ui->loadFile->setEnabled(false);
}
