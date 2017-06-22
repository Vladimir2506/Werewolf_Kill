/****************************************
Name: gamethread.h

Author: 林文镔

Date:2017-6

Description: 用于实现客户端的多线程，循环接收服务器端发来的指令

Copyright: Run函数的循坏部分由岑哲鹏编写，其余部分由作者编写
****************************************/
#ifndef GAMETHREAD_H
#define GAMETHREAD_H

#include <QThread>
#include "Client.h"
#include "basicinfo.h"
#include "mainwindow.h"

class GameThread : public QThread//用于实现多线程，负责循环接收指令
{
    Q_OBJECT
public:
    explicit GameThread(QObject *parent = 0);
    GameThread(CClient* cli, QObject* rec, QObject *parent = 0);
    void run();//线程开始
    void endThread();//游戏结束时线程结束

private:
    CClient* client;
    QObject* receiver;

signals:
    send(QString str);

public slots:
};

#endif // GAMETHREAD_H
