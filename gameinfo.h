/****************************************
Name: gameinfo.h

Author: 岑哲鹏

Date:2017-

Description: the classes of characters in this
    game, and these classes include the functions
    or operations of corresponding character

Copyright: almost all by author, GameInfo::Parse()
    is copied from 夏卓凡 to keep the regulation of
    info exchange standard.
****************************************/


#ifndef GAMEINFO_H
#define GAMEINFO_H


#include "character.h"
#include "basicinfo.h"
#include "mainwindow.h"
#include <string>
#include "Client.h"
#include <vector>
#include <ctime>
#include <cstdlib>
#include <QtWidgets>
#include <QWidget>

using namespace std;


class MainWindow;


//class to store infomation of player
class PlayerInfo
{
private:
    std::string m_strPlayerName;    //the name of player, but now it is useless...

    TID m_ID;   //the ID of player, from 0 to 7 if there are 8 players

public:
    int m_nch;
    state m_stateSelf;
    std::string m_strIdentity;

    PlayerInfo(std::string);
    PlayerInfo() = default;

    int get_ID(){return m_ID;}

    //set the ID at the beginning
    void set_ID(int i){m_ID=i;}

    //return the name of player, also useless
    std::string GetName();

    //to define the identity of player according to the distribution of server
    void DefIdentity();

    cBaseCharacter* pBaseIdentity;

};



/*
 * class to store the all info in need, including state of other
 * players and a member of PlayerInfo which store the self info.
 * And it also include the function to handle the instruction of
 * server and send the feedback to server.
*/
class GameInfo
{
private:
    TID target;//the target of operation

    int Round;

    vector<state> playerstate; //to store the state of all players

    PlayerInfo PlayerSelf;  //a memeber to store the self info

    MainWindow* pmainwindow; //a point to mainwindow which conducts the operations on UI

public:
    GameInfo() :target(0), Round(0), playerstate(PlayerTotality){}

    void setpmainwindow(MainWindow* p){pmainwindow=p;}

    /*
     * Parse the instruction
     * the format of instruction: _XXX|YYYYYYY;
     * "_XXX" is the commmand of instruction
     * "YYYYYYY" is the parameter;
     * this function seperates the command and parameter
    */
    void Parse(const string & str, string &strComm, string &strPara);

    /*
     * handle the instrctions
     * the strComm can be converted to nComm,
     * according to nComm, the client handles the
     * parameter with different cases
    */
    void DoParametres
    (
        int nComm,	//Case of Command
        const string & str	//Parametre of Command
    );

    /*
     * Feedback the operation of player and other change
     * of parameter to the server.
     * the format of final response is also "_XXX|YYYYYYY"
     */
    void Feedback(enCommandList nResp, int target, string str="", eAction action = DoNothing);
};

#endif
