#ifndef CLIENTDATAMODEL_HPP
#define CLIENTDATAMODEL_HPP

#include <QAbstractListModel>
#include <QTcpSocket>
#include <QHostAddress>
#include <QListWidget>

class ClientDataModel : QObject
{
    Q_OBJECT
public:
    explicit ClientDataModel(QListWidget *inList, QObject *parent = 0);

    void addSocket(QTcpSocket *socket);

    void removeSocket(QTcpSocket *socket);

signals:

public slots:

protected:
    QList<QTcpSocket*> clients;

    // Reference to the UI's list view
    QListWidget *list;

};

#endif // CLIENTDATAMODEL_HPP
