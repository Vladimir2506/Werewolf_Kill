/****************************************
Name: mainwindow.h

Author: 林文镔

Date:2017-6

Description:主界面，集合界面的所有部分

Copyright:完全由作者编写
****************************************/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <vector>
#include <iostream>
#include <QThread>
#include <QScrollBar>

#include "mytimer.h"
#include "playeravatar.h"
#include "Client.h"
#include "character.h"
#include <basicinfo.h>
#include <gameinfo.h>
#include <gamethread.h>

class GameThread;
class GameInfo;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:

    startGame();//游戏开始
    sendMsg();//返回发言消息
    sendVoting();//返回投票信息
    endStatement();//结束发言按钮
    opChoice();//返回技能操作信息
    timeUp();//时间到
    receive(QString qstr);//接受client信息

signals:

private:

    enIdentity identity;    //身份
    int id;   //编号
    MyTimer* mytimer;//计时器
    QLabel* progressLabel;//“游戏进程”标识
    QLabel* publicLabel;//“公共频道”标识
    QLabel* teamLabel;//“团队频道”标识
    QLabel* playerLabel;//“你的身份”标识
    QLabel* ipLabel;//“IP”标识
    QLineEdit* publicText;//“公共频道”发言框
    QLineEdit* teamText;//“团队频道”发言框
    QLineEdit* ipText;//“IP”输入框
    QPushButton* publicSend;//“公共频道”发送按钮
    QPushButton* teamSend;//“团队频道”发送按钮
    QListWidget* progressList;//“游戏进程”记录
    QListWidget* publicList;//“公共频道”发言记录
    QListWidget* teamList;//“团队频道”发言记录
    QLabel* idLabel;//“你的身份”标识
    QLabel* numLabel;//“你的编号”标识
    QPushButton* start;//“开始游戏”按钮
    QPushButton* endState;//“结束发言”按钮
    QPushButton* handOver;//移交警徽按钮
    QPushButton* tearUp;//撕除警徽按钮
    QPushButton* shot;//猎人发枪按钮
    QPushButton* notShot;//猎人放弃发枪按钮
    QPushButton* poison;//女巫毒药按钮
    QPushButton* anti;//女巫解药按钮
    QPushButton* giveUp;//女巫放弃用药按钮
    PlayerAvatar* player1;//玩家头像
    PlayerAvatar* player2;
    PlayerAvatar* player3;
    PlayerAvatar* player4;
    PlayerAvatar* player5;
    PlayerAvatar* player6;
    PlayerAvatar* player7;
    PlayerAvatar* player8;
    QFont font1;//字体
    QFont font2;
    GameInfo* gInfo;//玩家信息
    GameThread* gThread;//接收消息所用的线程
    CClient* client;//客户端

public:
    void addLine(int n,std::string str,msgType type,bool isNotice=false);//添加发言或消息，添加是否为系统提示的bool值显示不同效果
    void addLine(std::string str,msgType type=progressMsg);//重载addLine，发布游戏进程时无需添加发言者信息
    void addLine(QString qstr,msgType type=progressMsg);//为增强对中文显示的支持添加以QString为参数的重载方式
    void setButtons(enCommandList commandType, vector<bool> validTarget = {}, bool isPoisoned = true, bool isAntidote = true);//设置按键
    void die(int n);//设置编号为n的玩家死亡 采用代理模式通过MainWindow操作PlayeyAvatar
    void hideBadge(int n);//编号为n的玩家不为警长 代理模式
    void showBadge(int n);//显示编号为n的玩家为警长 代理模式
    void hideAll();//隐藏所有按钮，用于设置初始状态和死亡设置
    void stopState();//结束发言
    void setId(int n);//分配身份后设置编号
    void setIdentity(enIdentity enid);//分配身份后设置身份
    void setgInfo(GameInfo* info){gInfo = info;}//设置玩家信息
    void resetGame();//重置游戏
    void showIdentity(vector<int> vecIdentity);//游戏结束后显示玩家身份

private:
    Ui::MainWindow *ui;

    friend class GameInfo;//将GameInfo类设置为友元类，便于访问
};

#endif // MAINWINDOW_H
