#ifndef SERVERTHREAD_HPP
#define SERVERTHREAD_HPP

#include <QThread>
#include <QDebug>

class ServerThread : public QThread
{
    Q_OBJECT
public:
    explicit ServerThread(QObject *parent = 0);
    void exec();
signals:

public slots:

private:
};

#endif // SERVERTHREAD_HPP
