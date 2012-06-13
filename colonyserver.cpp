#include "colonyserver.hpp"
#include "ui_colonyserver.h"


ColonyServer::ColonyServer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ColonyServer),
    server(),
    clients()
{
    ui->setupUi(this);

    connect(&server, SIGNAL(newConnection()), this, SLOT(newConnection()));

    if(!server.listen(QHostAddress::Any, 7510)){
        qDebug() << "Error listening for connections!\n";
    }
    qDebug() << "Done initiating listening\n";

    serverThread = new ServerThread(this);
    serverThread->start();
}

void ColonyServer::newConnection(){
    qDebug() << "New connection received!\n";

    QTcpSocket* newSocket = server.nextPendingConnection();

    newSocket->write("Hello. You have connected to the colony server.\n");

    clients.append(newSocket);
}

ColonyServer::~ColonyServer()
{
    delete ui;
    serverThread->quit();
    while(!serverThread->isFinished()){}//Wait for the thread to finish quitting
    delete serverThread;
}
