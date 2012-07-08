#include "clientdatamodel.hpp"

ClientDataModel::ClientDataModel(QListWidget *inList, QObject *parent) :
    QObject(parent),
    clients()
{
    list = inList;
}


void ClientDataModel::addSocket(QTcpSocket *socket){
    clients.append(socket);
}

void ClientDataModel::removeSocket(QTcpSocket *socket){
    clients.removeAll(socket);
}
