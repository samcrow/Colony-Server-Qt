#ifndef SERVERTHREAD_HPP
#define SERVERTHREAD_HPP

#include <QThread>
#include <QDebug>

class ServerThread : public QThread
{
    Q_OBJECT
public:
    explicit ServerThread(QObject *parent = 0);
    void run();
signals:

public slots:
    void quit();
private slots:

private:
    int timer;
protected:
    void timerEvent(QTimerEvent *);
};

#endif // SERVERTHREAD_HPP
