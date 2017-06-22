/****************************************
Name: mytimer.h

Author: 林文镔

Date:2017-6

Description: 计时器，用于显示并更新玩家操作的倒计时。可根据指令重置计时器，倒计时结束时返回信息。

Copyright: 完全由作者编写
****************************************/
#ifndef MYTIMER_H
#define MYTIMER_H

#include <QWidget>
#include <QtWidgets>
#include <QTimer>
#include <QTime>
#include <QPalette>
#include <basicinfo.h>

class MyTimer : public QWidget
{
    Q_OBJECT

public:
    explicit MyTimer(QWidget *parent = 0);
    MyTimer(timerType type, QWidget *parent = 0);
     ~MyTimer();

public:
    void resetTimer(timerType type);//重设计时类型
    int getType();//获取计时器类型
    void stop();//停止计时

signals:
    timeOut();//时间到

private slots:
    void timerUpdate();//时间更新

private:
    timerType tType;//计时器类型
    int sec;//秒数
    QString timerName;//名称文本
    QString time;//秒数文本
    QLabel *timeShow;//名称标识

protected:
    QTimer* timer;
};

#endif // MYTIMER_H
