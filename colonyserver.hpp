#ifndef COLONYSERVER_HPP
#define COLONYSERVER_HPP

#include "serverthread.hpp"
#include "clientdatamodel.hpp"
#include "csvloader.hpp"
#include "mapdraw.hpp"

#include <QMainWindow>
#include <QDebug>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QList>
#include <QThread>
#include <QListWidget>
#include <QMetaEnum>
#include <QGraphicsScene>
#include <QRegExp>

namespace Ui {
class ColonyServer;
}

class ColonyServer : public QMainWindow
{
    Q_OBJECT

public:
    explicit ColonyServer(QWidget *parent = 0);
    ~ColonyServer();

private:
    Ui::ColonyServer *ui;

    QTcpServer server;
    ClientDataModel clients;

    //This is now a list of pointers to colonies,
    //because the program will have to move them around everywhere and modify the objects they point to.
    QList<Colony *> colonies;

    ServerThread *serverThread;

    QGraphicsScene scene;

private slots:
    void newConnection();
    void socketError(QAbstractSocket::SocketError);
    void dataReceived();
};

#endif // COLONYSERVER_HPP
