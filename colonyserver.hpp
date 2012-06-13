#ifndef COLONYSERVER_HPP
#define COLONYSERVER_HPP

#include "serverthread.hpp"

#include <QMainWindow>
#include <QDebug>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QList>
#include <QThread>

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
    QList<QTcpSocket*> clients;

    ServerThread *serverThread;

private slots:
    void newConnection();

};

#endif // COLONYSERVER_HPP
