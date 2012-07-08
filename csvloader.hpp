#ifndef CSVLOADER_HPP
#define CSVLOADER_HPP

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QList>
#include <QStringList>
#include <QSettings>
#include <QFileDialog>

#include "colony.hpp"

class CSVLoader : public QObject
{
    Q_OBJECT
public:
    explicit CSVLoader(QObject *parent = 0);


    /**
      Get the colonies from the file
      */
    QList<Colony *> readFile(QWidget * parent = 0);

signals:

public slots:

};

#endif // CSVLOADER_HPP
