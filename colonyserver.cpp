#include "colonyserver.hpp"
#include "ui_colonyserver.h"


ColonyServer::ColonyServer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ColonyServer),
    server(),
    clients()
{
    ui->setupUi(this);

    ui->statusBar->showMessage("Colony server initialized.", 2000);

    connect(&server, SIGNAL(newConnection()), this, SLOT(newConnection()));

    if(!server.listen(QHostAddress::Any, 7510)){
        qDebug() << "Error listening for connections!";
    }
    qDebug() << "Done initiating listening";

    serverThread = new ServerThread(this);
    serverThread->start();
}

void ColonyServer::newConnection(){
    qDebug() << "New connection received!";

    QTcpSocket* newSocket = server.nextPendingConnection();

    //Get the IP address of the client and add it to the list
    QString clientName = newSocket->peerAddress().toString();
    ui->clientList->insertItem(ui->clientList->count()-1, clientName);

    connect(newSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketError(QAbstractSocket::SocketError)));

    newSocket->write("Hello. You have connected to the colony server.\n");

    clients.append(newSocket);
}

void ColonyServer::socketError(QAbstractSocket::SocketError error){

    QObject *sendingObject = sender();
    //Should have something like this Java: assert(sendingObject instanceof QTcpSocket);
    //Something will go horribly wrong soon if the sender isn't a QTcpSocket.
    QTcpSocket *clientWithError = static_cast<QTcpSocket*>(sendingObject);

    QString errorText;
    QMetaObject meta = QAbstractSocket::staticMetaObject;
    for (int i=0; i < meta.enumeratorCount(); ++i) {
        QMetaEnum m = meta.enumerator(i);
        if (m.name() == QLatin1String("SocketError")) {
            errorText = QLatin1String(m.valueToKey(error));
            break;
        }
    }
    ui->statusBar->showMessage("Error communicating with " + clientWithError->peerAddress().toString() + ": "+errorText, 3000);
    qDebug() << errorText;
}

ColonyServer::~ColonyServer()
{
    delete ui;
    serverThread->quit();
    while(!serverThread->isFinished()){}//Wait for the thread to finish quitting
    delete serverThread;
}
