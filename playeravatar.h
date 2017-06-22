/****************************************
Name: playeravatar.h

Author: 林文镔

Date:2017-6

Description: 玩家头像，包含编号标识，警徽标识，投票按钮和死亡标识

Copyright: 完全由作者编写
****************************************/
#ifndef PLAYERAVATAR_H
#define PLAYERAVATAR_H

#include <QWidget>
#include <QtWidgets>
#include <QPalette>
#include <basicinfo.h>

class PlayerAvatar : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerAvatar(QWidget *parent = 0);
    PlayerAvatar(int n,QWidget *parent = 0);
    ~PlayerAvatar();

public:
    void playerDie();//死亡
    void playerShowBadge();//显示警徽
    void playerHideBadge();//隐藏警徽
    void playerShowIdentity(int n);//显示身份

public:
    QPushButton* voting;//投票按钮
    QLabel* player;//头像标识
    QLabel* badge;//警徽标识
    QLabel* number;//编号标识
    QLabel* dead;//死亡标识
    int id;//编号

signals:

public slots:
};

#endif // PLAYERAVATAR_H
