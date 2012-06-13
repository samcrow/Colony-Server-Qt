#include "serverthread.hpp"

ServerThread::ServerThread(QObject *parent) :
    QThread(parent)
{
}

void ServerThread::exec(){
    while(!shouldStop){
        usleep(20 * 1000);
    }
    quit();
}
