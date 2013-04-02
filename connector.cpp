#include "network.h"

extern int axis_number;

void getMyIP() {
    QNetworkInterface *qni = new QNetworkInterface();
    QList<QHostAddress> ips;
    QList<QString> ipstr;
    QString str;
    ips = qni->allAddresses();
    for (int i = 0; i < ips.size(); i++)
    {
        str = ips.at(i).toString();
        qDebug() << i << " : " << str;
    }
}

Connector::Connector(QWidget *parent)
    :  QObject(parent) {
    connected = false;
    client = true;
    delay = false;
    connect(&clientSock, SIGNAL(connected()), this, SLOT(ready()));
    connect(&server, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
    connect(this, SIGNAL(hasCmd()), this, SLOT(execute()));
}

Connector::~Connector() {}

void Connector::setup(QLabel *ql, QLineEdit *le, QPushButton *mBtn, QPushButton *dBtn, Canvas *c) {
    status = ql;
    ipBox = le;
    modeBtn = mBtn;
    delayBtn = dBtn;
    canvas = c;
    connect(this, SIGNAL(addY()), canvas, SLOT(addY()));
    connect(this, SIGNAL(subY()), canvas, SLOT(subY()));
    connect(this, SIGNAL(addX()), canvas, SLOT(addX()));
    connect(this, SIGNAL(subX()), canvas, SLOT(subX()));
    connect(this, SIGNAL(paint()), canvas, SLOT(paintClicked()));
}

void Connector::cconnect() {
    // client setup
    clientSock.abort();
    ip = ipBox->text();
    if (QString::compare(ip, "") == 0)
    {
        status->setText("NETWORK STATUS: No IP specified. Disconnected.");
        return;
    }
    QHostAddress host(ip);
    status->setText("NETWORK STATUS: Connecting to " + ip + "...");
    clientSock.connectToHost(host, PORT);
}

void Connector::ready() {
    // client connection is ready
    if (clientSock.state() != 3)
    {
        qDebug() << "CONNECTION STATUS " << clientSock.state();
        qDebug() << "CONNECTION ERROR " << clientSock.error();
        status->setText("NETWORK STATUS: Error connecting to " + ip + ". Disconnected.");
        connected = false;
    }
    else
    {
        status->setText("NETWORK STATUS: Connected to " + ip);
        connected = true;
        emit enableButtons();
    }
}

void Connector::changeMode() {
    // disconnect other socket, swap mode
    cdisconnect();
    client = !client;
    // server mode - start server
    if (!client)
    {
        modeBtn->setText("Client Mode");
        status->setText("NETWORK STATUS: Awaiting connection...");
        //ipBox->setEnabled(false);
        //connBtn->setEnabled(false);
        server.listen(QHostAddress::Any, PORT);
    }
    // client mode - wait for connect order
    else
    {
        modeBtn->setText("Server Mode");
        status->setText("NETWORK STATUS: Disconnected.");
        //ipBox->setEnabled(true);
        //connBtn->setEnabled(true);
    }
}

void Connector::changeDelay() {
    delay = !delay;
    if (delay)
        delayBtn->setText("Synchronized Mode");
    else
        delayBtn->setText("Delay Mode");
}

void Connector::acceptConnection() {
    serverSock = server.nextPendingConnection();
    status->setText("NETWORK STATUS: Connected as server.");
    connected = true;
    connect(serverSock, SIGNAL(readyRead()), this, SLOT(readCommands()));
}

void Connector::sendCommand(int command, int axis) {
    // if server, ignore
    if (!client)
        return;
    if (!connected)
    {
        qDebug() << "SEND ERROR: NOT CONNECTED";
        return;
    }
    char buf[2] = {command, axis};
    qDebug() << "SENDING: " << (int) buf[0] << ", " << (int) buf[1];
    clientSock.write(buf);
}

void Connector::readCommands() {
    if (client)
    {
        qDebug() << "READ - NOT SERVER";
        return;
    }
    char buf[2] = {0};
    serverSock->read(buf, serverSock->bytesAvailable());
    int command = int(buf[0]);
    int axis = int(buf[1]);

    if (delay)
    {
        cmdQ.enqueue(qMakePair(command, axis));
        QTimer::singleShot(2000, this, SLOT(timesUp()));
    }
    else
    {
        switch(command)
        {
        case CW:
            axis_number = next.second;
            canvas->rotateCW();
            break;
        case CCW:
            axis_number = next.second;
            canvas->rotateCCW();
            break;
        case ADDY:
            emit addY();
            break;
        case SUBY:
            emit subY();
            break;
        case ADDX:
            emit addX();
            break;
        case SUBX:
            emit subX();
            break;
        case PAINT:
            emit paint();
            break;
        default:
            qDebug() << "RECEIVE ERROR:" << next.first;
            break;
        }
    }
}

void Connector::cdisconnect() {
    if (!client && (server.isListening() || serverSock->state() != 0))
    {
        server.close();
        //serverSock->close();
        connected = false;
        status->setText("NETWORK STATUS: Disconnected.");
    }
    else if (client && connected)
    {
        clientSock.close();
        connected = false;
        status->setText("NETWORK STATUS: Disconnected.");
    }
}

void Connector::timesUp()
{
    QPair<int, int> next = cmdQ.dequeue();
    switch(next.first)
    {
    case CW:
        axis_number = next.second;
        canvas->rotateCW();
        break;
    case CCW:
        axis_number = next.second;
        canvas->rotateCCW();
        break;
    case ADDY:
        emit addY();
        break;
    case SUBY:
        emit subY();
        break;
    case ADDX:
        emit addX();
        break;
    case SUBX:
        emit subX();
        break;
    case PAINT:
        emit paint();
        break;
    default:
        qDebug() << "RECEIVE ERROR:" << next.first;
        break;
}
}
