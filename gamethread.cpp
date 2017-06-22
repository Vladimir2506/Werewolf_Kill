#include "gamethread.h"

GameThread::GameThread(QObject *parent) : QThread(parent)
{
}

GameThread::GameThread(CClient* cli, QObject *rec, QObject *parent): QThread(parent)
{
    client = cli;//设置客户端的Client对象
    receiver = rec;//设置接收指令的部件
}

void GameThread::run()
{
    connect(this,SIGNAL(send(QString)),receiver,SLOT(receive(QString)));
    char Command[MAX_SIZE];
    string strComm;
    do {
        if(client->RecvMsg(Command, MAX_SIZE)==0)//循环接收指令
        {
            string str(Command);
            if(!str.empty())
                strComm = str.substr(0, str.find("|"));
            QString qstr = str2qstr(str);
            emit send(qstr);//将指令发出
        }
        msleep(50);
    } while (strComm != "_R");//若为结束指令则退出循环
    client->Close();//关闭Client
    this->exec();
}

void GameThread::endThread()
{
    this->exec();
}
