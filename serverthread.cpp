#include "serverthread.hpp"

ServerThread::ServerThread(QObject *parent) :
    QThread(parent)
{
    timer = 0;
}

void ServerThread::run(){
    qDebug() << "Server thread starting";
    timer = startTimer(500);
}

//Called when something wants this thread to stop
void ServerThread::quit(){
    killTimer(timer);//Stop the timer
    QThread::quit();//Let the superclass know and do its own processing
}


void ServerThread::timerEvent(QTimerEvent *){

}
