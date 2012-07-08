#include "colonyserver.hpp"
#include "ui_colonyserver.h"


ColonyServer::ColonyServer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ColonyServer),
    clients(ui->clientList, this)
{
    ui->setupUi(this);

    ui->statusBar->showMessage("Colony server initialized.", 5000);

    //Hook up the signal & slot for knowing when a client connects
    connect(&server, SIGNAL(newConnection()), this, SLOT(newConnection()));

    if(!server.listen(QHostAddress::Any, 7510)){
        qDebug() << "Error listening for connections!";
    }

    serverThread = new ServerThread(this);
    serverThread->start();

    CSVLoader loader;
    colonies = loader.readFile(this);

    ui->mapView->setScene(&scene);

    MapDraw map;
    map.draw(&colonies, &scene);
}

void ColonyServer::newConnection(){

    QTcpSocket* newSocket = server.nextPendingConnection();

    //Get the IP address of the client and add it to the list
    QString clientIP = newSocket->peerAddress().toString();

    ui->statusBar->showMessage("New connection from "+clientIP, 3000);

    //Hook up the slot/signal mechanism so that this class knows
    //if there's an error communicating over this socket
    connect(newSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketError(QAbstractSocket::SocketError)));
    //Hook up the slot/signal mechanism so that this class knows
    //when the device on the other end of this socket sends data
    connect(newSocket, SIGNAL(readyRead()), this, SLOT(dataReceived()));

    clients.addSocket(newSocket);

    QListWidgetItem *newListItem = new QListWidgetItem(clientIP, ui->clientList, QListWidgetItem::Type);
    ui->clientList->addItem(newListItem);
}

void ColonyServer::socketError(QAbstractSocket::SocketError error){
    QObject *sendingObject = sender();

    QTcpSocket *clientWithError = qobject_cast<QTcpSocket *>(sendingObject);
    if(clientWithError == NULL){
        qCritical() << "Something that wasn't a QTcpSocket sent a signal to the socketError slot!";
        return;
    }

    //Get the string representation of the error code
    QString errorText;
    QMetaObject meta = QAbstractSocket::staticMetaObject;
    for (int i=0; i < meta.enumeratorCount(); ++i) {
        QMetaEnum m = meta.enumerator(i);
        if (m.name() == QLatin1String("SocketError")) {
            errorText = QLatin1String(m.valueToKey(error));
            break;
        }
    }

    //Get a string representation of the client's IP address
    QString IPAddress = clientWithError->peerAddress().toString();

    //Remove this client from the data model
    clients.removeSocket(clientWithError);

    //Iterate through the list and remove the entries that match this client's IP address
    for(int i = 0, max = ui->clientList->count(); i < max; i++){
        QListWidgetItem *thisRow = ui->clientList->item(i);
        if(thisRow->text().compare(IPAddress) == 0){
            QListWidgetItem *itemRemoved = ui->clientList->takeItem(i);//Remove it from the list display
            delete itemRemoved; //Delete it from memory
        }
    }

    ui->statusBar->showMessage("Error communicating with " + clientWithError->peerAddress().toString() + ": "+errorText, 3000);
}

/*
  Preliminary format documentation:
  Client to server, requesting colonies: get-colonies\n
  Response: {colony number, x, y, isActive (true or false)};{the same for other colonies ... }\n

  Client to server, providing an updated colony: update-colony{colony number, x, y, isActive (true or false)}\n
  */
void ColonyServer::dataReceived(){
    QObject *sendingObject = sender();

    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sendingObject);
    if(socket == NULL){
        qCritical() << "Something that wasn't a QTcpSocket sent a signal to the DataReceived slot!";
        return;
    }

    QString line(socket->readLine());
    line = line.trimmed();//Remove newlines and such

    if(line.compare("get-colonies") == 0){//If colonies requested

        QString response;

        for(int i = 0, max = colonies.length(); i < max; i++){
            Colony *thisColony = colonies.at(i);
            response += '{'+QString::number(thisColony->getID())+
                    ','+QString::number(thisColony->getX())+
                    ','+QString::number(thisColony->getY())+
                    ','+ ( thisColony->isActive() ? "true" : "false" ) + '}';

            response += ';';//Add a semicolon. The last one will get removed later.
        }

        response.chop(1);//Remove the last character, that being a comma, from the end of the response
        response += "\n";//Add a newline signifying the end of output
        socket->write(response.toUtf8());
    }

    else if(line.startsWith("update-colony")){
        //Colony update requested

        line = line.trimmed();//Remove newlines
        //Remove the "update-colony" from the beginning
        line = line.remove(0, 13);

        QRegExp validateRegex("\\{[^,]+,[^,]+,[^,]+,[^,]+\\}");
        if(validateRegex.exactMatch(line)){
            //Line matches regular expression.

            line = line.remove(0, 1);//Remove the first {
            line.chop(1);//Remove the last }

            QRegExp splitRegex("[\\s]*,[\\s]*");

            QStringList parts = line.split(splitRegex);

            if(parts.size() == 4){

                int colonyNumber = parts.at(0).toInt();

                //Find the colony number in memory that this corresponds to the updated colony
                QListIterator<Colony *> colonyIterator(colonies);
                while(colonyIterator.hasNext()){
                    Colony *colony = colonyIterator.next();
                    if(colony->getID() == colonyNumber){
                        //Update this colony with the new information
                        double x = parts.at(1).toDouble();
                        double y = parts.at(2).toDouble();
                        bool active = QString::compare(parts.at(3), "true", Qt::CaseInsensitive) == 0;

                        colony->setX(x);
                        colony->setY(y);
                        colony->setActive(active);

                        qDebug() << "Updated colony:" << colony->toString();
                        socket->write("success\n");
                    }
                }



            }else{
                qWarning() << line << "was split into" << parts << "(not 4 parts)";
            }

        }else{
            qWarning() << line << "Didn't match the regular expression for a colony format.";
            socket->write("failure\n");
        }
    }
}

ColonyServer::~ColonyServer()
{
    delete ui;
    serverThread->quit();
    delete serverThread;
}
