#ifndef NETWORK_H
#define NETWORK_H

#include <QNetworkInterface>
#include <QTcpSocket>
#include <QTcpServer>
#include <QLabel>
#include <QLineEdit>
#include <QObject>
#include <QPushButton>
#include <QTimer>
#include <QTest>
#include <QQueue>
#include "canvas.h"

#define CW 1
#define CCW 2
#define ADDY 3
#define SUBY 4
#define ADDX 5
#define SUBX 6
#define PAINT 7
#define PORT 9009

void getMyIP();

class Connector : public QObject {
    Q_OBJECT
public:
    bool client; // true if client, false if server
    bool connected, delay;
    Connector(QWidget *parent = 0);
    ~Connector();
    void setup(QLabel *ql, QLineEdit *le, QPushButton *mBtn, QPushButton *dBtn, Canvas *c);
signals:
    void enableButtons();
    void addY();
    void subY();
    void addX();
    void subX();
    void paint();
    void hasCmd(int size);
public slots:
    void cconnect();
    void ready();
    void acceptConnection();
    void changeMode();
    void changeDelay();
    void sendCommand(int command, int axis);
    void readCommands();
    void execute(int size);
    void cdisconnect();
    void timesUp();
private:
    QString ip;
    QTcpServer server;
    QTcpSocket *serverSock;
    QTcpSocket clientSock;
    QLabel *status;
    QLineEdit *ipBox;
    QPushButton *modeBtn, *delayBtn;
    Canvas *canvas;
    QQueue<QPair<int, int> > cmdQ;
};

#endif // NETWORK_H
